package /* src.main.java. */river_monitoring_service.mqtt;

import java.util.Map;

import com.google.gson.Gson;

import river_monitoring_service.config;
import /* src.main.java. */river_monitoring_service.RiverMonitoringSystemState;
import /* src.main.java. */river_monitoring_service.RunService;
import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;

/**
 * Class for the MQTT Agent
 * */
public class MQTTAgent extends AbstractVerticle {

    private MQTTWaterLevel waterLevel;

    public MQTTAgent() {
    }

    @Override
    public void start() {
        MqttClient client = MqttClient.create(vertx);
        Gson msgToEsp = new Gson();

        client.connect(1883, "broker.mqtt-dashboard.com", c -> {
            if(c.succeeded()) {

                log("connected");

                log("subscribing...");

                //If there is a new message from ESP, save waterLevel data into RiverState histories.
                client.publishHandler(s -> {
                    System.out.println("There are new message in topic: " + s.topicName());

                    
                    if (s.topicName().equals(Topics.WATERLEVEL.getName())) {
                        if (s.payload().toString().contains("{")) {
                            waterLevel = msgToEsp.fromJson(s.payload().toString(), MQTTWaterLevel.class);
                            RiverMonitoringSystemState.getInstance().addWaterLevel(waterLevel);

                        }
                    } 

                    if(RunService.getAutomatic()) {
                        
                        MQTTFrequency frequency;
                        if(waterLevel.getWaterLevel() <= config.WL2) {
                            frequency = new MQTTFrequency(config.F2);
                        } else if(waterLevel.getWaterLevel() > config.WL2) {
                            frequency = new MQTTFrequency(config.F1);
                        } else {
                            throw new IllegalArgumentException("Invalid water level value");
                        }
                        String jsonFrequency = msgToEsp.toJson(frequency);
                        Buffer buffer = Buffer.buffer(jsonFrequency);
                        RiverMonitoringSystemState.getInstance().addFrequency(frequency);
                        client.publish(Topics.FREQUENCY.getName(), buffer, MqttQoS.AT_LEAST_ONCE, false, false);
                        
                    }

                    System.out.println("Content of the message: " + s.payload().toString());
                    System.out.println("QoS: " + s.qosLevel());
                }).subscribe(Map.of(Topics.WATERLEVEL.getName(), 2, Topics.FREQUENCY.getName(), 2));
            } else if(c.failed()){
                log("Failed to connect to the broker: " + c.cause());
            }
        });
    }

    private void log(String msg) {
        System.out.println("[MQTT AGENT] " + msg);
    }

    private enum Topics {
        WATERLEVEL("waterLevel"), FREQUENCY("frequency");

        private String name;

        private Topics(final String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }
    }

}