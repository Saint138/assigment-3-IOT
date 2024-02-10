package /* src.main.java. */river_monitoring_service;

import java.util.Optional;
import com.fazecast.jSerialComm.SerialPort;

import /* src.main.java. */river_monitoring_service.http.DashboardMessage;
import /* src.main.java. */river_monitoring_service.http.RiverResource;
import /* src.main.java. */river_monitoring_service.mqtt.MQTTAgent;
import /* src.main.java. */river_monitoring_service.mqtt.MQTTWaterLevel;
import /* src.main.java. */river_monitoring_service.serial.CommChannel;
import /* src.main.java. */river_monitoring_service.serial.SerialCommChannel;
import /* src.main.java. */river_monitoring_service.serial.SerialCommunication;
import io.vertx.core.Vertx;

public class RunService {

	// Vars with synchronized method used in multiple threads
	private static boolean automatic = true;
    private static String currentState = "NORMAL";
    private static boolean dashboard = false;
	private static SerialCommunication arduinoMsg;

    public static void main(String[] args) {

        //deploy http service in order to exchange data with the dashboard
        Vertx vertxHttp = Vertx.vertx();
        RiverResource service = new RiverResource(1883);
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

        try {
            final CommChannel arduinoChannel = new SerialCommChannel(portName, 9600);

            // thread for sending msg to arduino
            final Thread sender = new Thread(() -> {
                while (true) {

                    Optional<MQTTWaterLevel> lastWaterLevel = RiverMonitoringSystemState.getInstance().getLastWaterLevel();
                    Optional<DashboardMessage> dashboardMsg = RiverMonitoringSystemState.getInstance().getLastDashboardMessage();

                    if (dashboardMsg.isPresent()) {
                        System.out.println("New Dashboard Msg available: " + dashboardMsg.get().toString());
                    	setAutomatic(false);
                        setDashboard(true);
                    	arduinoMsg = new SerialCommunication(false, dashboardMsg.toString(), true);
                    	sendMessage(arduinoMsg, arduinoChannel);
                    } else if (lastWaterLevel.isPresent()) {
                        System.out.println("New WaterLevel Msg available: " + lastWaterLevel.get().toString());
                        setDashboard(false);
                        setAutomatic(true);
                        arduinoMsg = new SerialCommunication(true, getRiverState(lastWaterLevel.get().getWaterLevel()) , false);
                        sendMessage(arduinoMsg, arduinoChannel);
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

                            System.out.println("New Arduino Msg available: " + msg);

                            //this if ignore "null" arduino packet
                            if(!msg.contains("null")) {
	                            if(msg.contains("DASHBOARD: false")) {
	                                setDashboard(false);
                                    setAutomatic(false);
	                            }
                                if(msg.contains("AUTOMATIC: true")) {
                                    setAutomatic(true);
                                } else {
                                    setAutomatic(false);
                                }
                                if(msg.contains("STATE: ")) {
                                    String stateStr = msg.substring(msg.indexOf("STATE: ") + 7);
                                    stateStr = stateStr.trim(); // Prende la stringa dopo "STATE: "
                                    currentState = stateStr;
                                }
                            }
                        }
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

	private static void sendMessage(final SerialCommunication packet, final CommChannel channel) {
        try {
            channel.sendMsg(packet.toString());
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static String getRiverState(int waterLevel) {
        if (waterLevel < config.WL4) {
            return "ALLARM-TOO-HIGH-CRITIC";
        } else if (waterLevel < config.WL3) {
            return "ALLARM-TOO-HIGH";
        } else if (waterLevel < config.WL2) {
            return "PRE-ALLARM-TOO-HIGH";
        } else if (waterLevel <= config.WL1) {
            return "NORMAL";
        } else if (waterLevel > config.WL1) {
            return "ALLARM-TOO-LOW";
        } else {
            return "ERROR on RunService";
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

    public static synchronized String getCurrentState() {
        return currentState;
    }
}