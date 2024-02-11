package river_monitoring_service.mqtt;

/**
 * Class that represents the MQTT light message sent from the ESP.
 * */
public class MQTTFrequency {

	private int frequency;

	public MQTTFrequency(final int frequency) {
		super();
		this.frequency = frequency;
	}

	public int getFrequency() {
		return frequency;
	}

	public void setFrequency(int frequency) {
		this.frequency = frequency;
	}

	@Override
	public String toString() {
		return "MQTTMsg [frequency=" + this.frequency + "]";
	}
}