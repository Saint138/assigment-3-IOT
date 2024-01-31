package src.main.java.river_monitoring_service.http;

/**
 * Class that represents the message sent through the dashboard.
 * */
public class DashboardMessage {

    private final boolean light;
    private final int angle;

    public DashboardMessage(final boolean light, final int angle) {
        this.light = light;
        this.angle = angle;
    }

	public boolean isLight() {
        return light;
    }

    public int getAngle() {
        return angle;
    }

    @Override
    public String toString() {
    	return "DashboardMessage [light=" + light + ", angle=" + angle + "]";
    }
}