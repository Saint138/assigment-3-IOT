package /* src.main.java. */river_monitoring_service.http;

/**
 * Class that represents the message sent through the dashboard.
 * */
public class DashboardMessage {

    private final int valveOpening;

    public DashboardMessage(final int valveOpening) {
        this.valveOpening = valveOpening;
    }

    public int getValveOpening() {
        return valveOpening;
    }

    @Override
    public String toString() {
    	return String.valueOf(valveOpening);
    }
}