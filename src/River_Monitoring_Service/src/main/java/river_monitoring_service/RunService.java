package /* src.main.java. */river_monitoring_service;

import java.time.LocalDateTime;
import java.util.Optional;
import java.util.Timer;
import java.util.TimerTask;

import com.google.gson.Gson;
import com.fazecast.jSerialComm.SerialPort;

import /* src.main.java. */river_monitoring_service.http.DashboardMessage;
import /* src.main.java. */river_monitoring_service.http.RiverResource;
import /* src.main.java. */river_monitoring_service.mqtt.MQTTAgent;
import /* src.main.java. */river_monitoring_service.mqtt.MQTTWaterLevel;
import /* src.main.java. */river_monitoring_service.mqtt.MQTTFrequency;
import /* src.main.java. */river_monitoring_service.serial.CommChannel;
import /* src.main.java. */river_monitoring_service.serial.SerialCommChannel;
import /* src.main.java. */river_monitoring_service.serial.SerialCommunication;
import io.vertx.core.Vertx;

public class RunService {

	// Vars with synchronized method used in multiple threads
	private static boolean automatic = true;
    private static boolean dashboard = false;
	private static boolean isFrontendActive = false;
	private static SerialCommunication lastAutomaticMessage;

    public static void main(String[] args) {

        //deploy http service in order to exchange data with the dashboard
        Vertx vertxHttp = Vertx.vertx();
        RiverResource service = new RiverResource(3030);
        vertxHttp.deployVerticle(service);

        //deploy mqtt agent
        Vertx vertxMqtt = Vertx.vertx();
        MQTTAgent agent = new MQTTAgent();
        vertxMqtt.deployVerticle(agent);

        SerialPort[] ports = SerialPort.getCommPorts();
        String portName = null;

        for (SerialPort port : ports) {
            if (port.getDescriptivePortName().contains("Arduino")) {
                portName = port.getSystemPortName();
                break;
            }
        }

        if (portName == null) {
            System.out.println("Arduino port not found.");
            return;
        }

        Timer timer = new Timer();

        try {
            final CommChannel arduinoChannel = new SerialCommChannel(portName, 9600);

            // thread for sending msg to arduino
            final Thread sender = new Thread(() -> {
                while (true) {

                    Optional<MQTTWaterLevel> lastWaterLevel = RiverMonitoringSystemState.getInstance().getLastWaterLevelState();
                    Optional<DashboardMessage> dashboardMsg = RiverMonitoringSystemState.getInstance().getLastDashboardMessage();
                    /* TODO */
                    if (dashboardMsg.isPresent()) {
                    	setAutomatic(false);
                        setDashboard(true);
                    	lastAutomaticMessage = new SerialCommunication(false, "qui dentro va messo il numero di dashboardMsg convertito in stringa ", true);
                    	startTimer(timer);
                    	sendMessage(lastAutomaticMessage, arduinoChannel);
                    } else if (lastWaterLevel.isPresent()) {
                        setDashboard(false);
                        setAutomatic(true);
                        lastAutomaticMessage = new SerialCommunication(true, "stringa dello stato in base a waterlevel" , false);
                        startTimer(timer);
                        sendMessage(lastAutomaticMessage, arduinoChannel);
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
                            

                            //this if ignore "null" arduino packet
                            /* TODO */
                            var lightOn = new MQTTFrequency(gson.isLightOn());
                            if(!msg.contains("null")) {
	                            if(gson.isFrontendActive()) {
	                                setAutomatic(false);
	                                lastAutomaticMessage = gson;
	                            }
	                            lightOn.setMsgDate(LocalDateTime.now().toString());
	                            RiverMonitoringSystemState.getInstance().getFrequencyStateHistory().add(lightOn);
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
		    	isFrontendActive = false;
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

    public static synchronized boolean getDashboard() {
        return dashboard;
    }

    public static synchronized void setDashboard(boolean value) {
    	dashboard = value;
    }
}