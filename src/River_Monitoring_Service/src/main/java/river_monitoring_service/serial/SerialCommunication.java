package /* src.main.java. */river_monitoring_service.serial;

public class SerialCommunication {

	private boolean automatic;
	private String valveOpening;
	private boolean dashboard;	

	public SerialCommunication(boolean automatic, String valveOpening, boolean dashboard) {
		super();
		this.automatic = automatic;
		this.valveOpening = valveOpening;
		this.dashboard = dashboard;
	}

	public boolean isAutomatic() {
		return automatic;
	}

	public void setAutomatic(boolean automatic) {
		this.automatic = automatic;
	}

	public boolean isDashboard() {
		return dashboard;
	}

	public void setDashboard(boolean dashboard) {
		this.dashboard = dashboard;
	}

	public String getValveOpening() {
		return valveOpening;
	}

	public void setValveOpening(String valveOpening) {
		this.valveOpening = valveOpening;
	}

	@Override
	public String toString() {
		return "SerialCommunication [automatic =  " + automatic + ", valveOpening = " + valveOpening + " , dashboard = " + dashboard + "]";
	}
}
