package river_monitoring_service.mqtt;

import java.time.LocalDateTime;

/**
 * Class that represents the MQTT movement message sent from the ESP.
 * */
public class MQTTWaterLevel {

    private String dateTime;
    private int waterLevel;

    public MQTTWaterLevel(final int waterLevel) {
        super();
        this.dateTime = LocalDateTime.now().toString();
        this.waterLevel = waterLevel;
    }

    public int getWaterLevelState() {
        return waterLevel;
    }

    public void setWaterLevelState(final int waterLevel) {
        this.waterLevel = waterLevel;
    }

    public String getDateTime() {
        return dateTime;
    }

    public void setDateTime(String dateTime) {
        this.dateTime = dateTime;
    }
}