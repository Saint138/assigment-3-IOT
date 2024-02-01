package /* src.main.java. */river_monitoring_service.http;

/**
 * Class that represents the message sent through the dashboard.
 * */
public class DashboardMessage {

    private final boolean clicked;
    private final int valveOpening;

    public DashboardMessage(final boolean clicked, final int valveOpening) {
        this.clicked = clicked;
        this.valveOpening = valveOpening;
    }

	public boolean isClicked() {
        return clicked;
    }

    public int getValveOpening() {
        return valveOpening;
    }

    @Override
    public String toString() {
    	return "DashboardMessage [clicked=" + clicked + ", valveOpening=" + valveOpening + "]";
    }
}