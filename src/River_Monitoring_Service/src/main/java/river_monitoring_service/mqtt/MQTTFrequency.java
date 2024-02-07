package river_monitoring_service.mqtt;

import java.time.LocalDateTime;

/**
 * Class that represents the MQTT light message sent from the ESP.
 * */
public class MQTTFrequency {

	private String dateTime;
	private int frequency;

	public MQTTFrequency(final int frequency) {
		super();
		this.dateTime = LocalDateTime.now().toString();
		this.frequency = frequency;
	}

	public String getMsgDate() {
		return this.dateTime;
	}

	public int getFrequency() {
		return frequency;
	}

	public void setMsgDate(final String dateTime) {
		this.dateTime = dateTime;
	}

	public void setFrequency(int frequency) {
		this.frequency = frequency;
	}

	@Override
	public String toString() {
		return "MQTTMsg [msgDate=" + this.dateTime + ", frequency=" + this.frequency + "]";
	}
}