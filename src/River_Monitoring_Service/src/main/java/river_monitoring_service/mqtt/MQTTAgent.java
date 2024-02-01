package /* src.main.java. */river_monitoring_service.mqtt;

import java.time.LocalDateTime;
import java.util.Map;

import com.google.gson.Gson;

import /* src.main.java. */river_monitoring_service.RiverMonitoringSystemState;
import io.vertx.core.AbstractVerticle;
import io.vertx.mqtt.MqttClient;

/**
 * Class for the MQTT Agent
 * */
public class MQTTAgent extends AbstractVerticle {

    public MQTTAgent() {
    }

    @Override
    public void start() {
        MqttClient client = MqttClient.create(vertx);
        Gson msgToEsp = new Gson();

        client.connect(1883, "broker.mqtt-dashboard.com", c -> {

            log("connected");

            log("subscribing...");

            //If there is a new message from ESP, save movement and light data into RoomState histories.
            client.publishHandler(s -> {
                System.out.println("There are new message in topic: " + s.topicName());

                if (s.topicName().equals(Topics.LIGHT.getName())) {
                    if (s.payload().toString().contains("{")) {
                        MQTTLight light = msgToEsp.fromJson(s.payload().toString(), MQTTLight.class);
                        light.setMsgDate(LocalDateTime.now().toString());
                        RiverMonitoringSystemState.getInstance().getDayHistory().add(light);
                    }
                } else {
                    if (s.payload().toString().contains("{")) {
                        MQTTMovement movement = msgToEsp.fromJson(s.payload().toString(), MQTTMovement.class);
                        movement.setDateTime(LocalDateTime.now().toString());
                        RiverMonitoringSystemState.getInstance().getMovementStateHistory().add(movement);
                    }
                }

                System.out.println("Content(as string) of the message: " + s.payload().toString());
                System.out.println("QoS: " + s.qosLevel());

            }).subscribe(Map.of(Topics.MOVEMENT.getName(), 2, Topics.LIGHT.getName(), 2));
        });
    }

    private void log(String msg) {
        System.out.println("[MQTT AGENT] " + msg);
    }

    private enum Topics {
        MOVEMENT("movement"), LIGHT("light");

        private String name;

        private Topics(final String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }
    }

}