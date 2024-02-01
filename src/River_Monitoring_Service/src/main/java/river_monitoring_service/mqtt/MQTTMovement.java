package /* src.main.java. */river_monitoring_service.mqtt;

import java.time.LocalDateTime;

/**
 * Class that represents the MQTT movement message sent from the ESP.
 * */
public class MQTTMovement {

    private String dateTime;
    private boolean movement;

    public MQTTMovement(final boolean movement) {
        super();
        this.dateTime = LocalDateTime.now().toString();
        this.movement = movement;
    }

    public boolean getMovementState() {
        return movement;
    }

    public void setMovementState(final boolean movement) {
        this.movement = movement;
    }

    public String getDateTime() {
        return dateTime;
    }

    public void setDateTime(String dateTime) {
        this.dateTime = dateTime;
    }
}