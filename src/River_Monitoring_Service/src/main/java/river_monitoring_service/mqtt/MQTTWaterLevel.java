package river_monitoring_service.mqtt;

import java.time.LocalDateTime;

/**
 * Class that represents the MQTT movement message sent from the ESP.
 * */
public class MQTTWaterLevel {

    private int waterLevel;

    public MQTTWaterLevel(final int waterLevel) {
        super();
        this.waterLevel = waterLevel;
    }

    public int getWaterLevel() {
        return waterLevel;
    }

    public void setWaterLevel(final int waterLevel) {
        this.waterLevel = waterLevel;
    }
}