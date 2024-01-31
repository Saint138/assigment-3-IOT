package src.main.java.river_monitoring_service;

import java.time.LocalDateTime;
import java.util.Optional;
import java.util.Timer;
import java.util.TimerTask;

import com.google.gson.Gson;

import src.main.java.river_monitoring_service.http.DashboardMessage;
import src.main.java.river_monitoring_service.http.RoomResource;
import src.main.java.river_monitoring_service.mqtt.MQTTAgent;
import src.main.java.river_monitoring_service.mqtt.MQTTMovement;
import src.main.java.river_monitoring_service.mqtt.MQTTLight;
import src.main.java.river_monitoring_service.serial.CommChannel;
import src.main.java.river_monitoring_service.serial.SerialCommChannel;
import src.main.java.river_monitoring_service.serial.SerialCommunication;
import io.vertx.core.Vertx;

public class RunService {

	// Vars with synchronized method used in multiple threads
	private static boolean automatic = true;
	private static boolean isBtActive = false;
	private static SerialCommunication lastAutomaticMessage;

    public static void main(String[] args) {

        //deploy http service in order to exchange data with the dashboard
        Vertx vertxHttp = Vertx.vertx();
        RoomResource service = new RoomResource(3030);
        vertxHttp.deployVerticle(service);

        //deploy mqtt agent
        Vertx vertxMqtt = Vertx.vertx();
        MQTTAgent agent = new MQTTAgent();
        vertxMqtt.deployVerticle(agent);

        final String portName = "COM3";
        System.out.println("Start monitoring serial port " + portName + " at 9600 boud rate");

        Timer timer = new Timer();

        try {
            final CommChannel arduinoChannel = new SerialCommChannel(portName, 9600);

            // thread for sending msg to arduino
            final Thread sender = new Thread(() -> {
                while (true) {

                    Optional<MQTTLight> lastDay = RoomState.getInstance().getLastDay();
                    Optional<MQTTMovement> movement = RoomState.getInstance().getLastMovementState();
                    Optional<DashboardMessage> dashboardMsg = RoomState.getInstance().getLastDashboardMessage();

                    if (dashboardMsg.isPresent()) {
                    	setAutomatic(false);
                    	lastAutomaticMessage = new SerialCommunication(false, false,
                    			dashboardMsg.get().isLight(), dashboardMsg.get().getAngle(), false, false);

                    	startTimer(timer);
                    	sendMessage(lastAutomaticMessage, arduinoChannel);
                    } else if(!getAutomatic()) {
                    	sendMessage(lastAutomaticMessage, arduinoChannel);
                    } else if (lastDay.isPresent() && movement.isPresent()) {
                    	sendMessage(new SerialCommunication(lastDay.get().getDay(), movement.get().getMovementState(),
                    			false, 0, true, false), arduinoChannel);
                    } else {
                        try {
                            Thread.sleep(1000);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }
            });

            // thread for receiving msg from arduino and store it
            final Thread receiver = new Thread(() -> {
                while (true) {
                    try {
                        if (arduinoChannel.isMsgAvailable()) {
                            String msg;
                            msg = arduinoChannel.receiveMsg();
                            var gson = new Gson().fromJson(msg, SerialCommunication.class);

                            System.out.println("New Arduino Msg available: " + msg);
                            var lightOn = new MQTTLight(gson.isLightOn());

                            //this if ignore "null" arduino packet
                            if(!msg.contains("null")) {
	                            if(gson.isBtCommand()) {
	                                setAutomatic(false);
	                                lastAutomaticMessage = gson;
	                            }
	                            if(!isBtActive && gson.isBtCommand()) {
	                            	startTimer(timer);
	                            	isBtActive = true;
	                            }
	                            lightOn.setMsgDate(LocalDateTime.now().toString());
	                            RoomState.getInstance().getLightStateHistory().add(lightOn);
                            }
                        }
                        Thread.sleep(1000);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            });

            receiver.start();
            sender.start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * it schedule a timer to limit manual command,
     * it returns automatic after 10 seconds
     * @param timer
     */
    private static void startTimer(final Timer timer) {
    	timer.schedule(new TimerTask() {
		    @Override
		    public void run() {
		    	isBtActive = false;
			    setAutomatic(true);
		    }
		}, 10000);
	}

	private static void sendMessage(final SerialCommunication packet, final CommChannel channel) {
        try {
            channel.sendMsg(new Gson().toJson(packet));
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static synchronized boolean getAutomatic() {
        return automatic;
    }

    public static synchronized void setAutomatic(boolean value) {
    	automatic = value;
    }
}