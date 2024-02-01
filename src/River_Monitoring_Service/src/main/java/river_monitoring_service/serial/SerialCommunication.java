package /* src.main.java. */river_monitoring_service.serial;

public class SerialCommunication {

	private boolean automatic;
	private int valveOpening;	

	public SerialCommunication(boolean automatic, int valveOpening) {
		super();
		this.automatic = automatic;
		this.valveOpening = valveOpening;
	}

	public boolean isAutomatic() {
		return automatic;
	}

	public void setAutomatic(boolean automatic) {
		this.automatic = automatic;
	}

	public int getValveOpening() {
		return valveOpening;
	}

	public void setValveOpening(int valveOpening) {
		this.valveOpening = valveOpening;
	}

	@Override
	public String toString() {
		return "SerialCommunication [automatic =  " + automatic + ", valveOpening = " + valveOpening + "]";
	}
}
