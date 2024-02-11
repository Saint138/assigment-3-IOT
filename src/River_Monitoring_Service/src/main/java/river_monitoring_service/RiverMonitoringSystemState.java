package /* src.main.java. */river_monitoring_service;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Queue;

import /* src.main.java. */river_monitoring_service.http.DashboardMessage;
import /* src.main.java. */river_monitoring_service.mqtt.MQTTWaterLevel;
import /* src.main.java. */river_monitoring_service.mqtt.MQTTFrequency;

/**
 * Class to keep ESP messages history (movement and day), dashboard messages (to be send to Arduino)
 * and Arduino light history.
 * */
public class RiverMonitoringSystemState {

	private static RiverMonitoringSystemState instance = null;

	private List<MQTTFrequency> frequencyHistory;
	private List<MQTTWaterLevel> waterLevelHistory;
	private Queue<DashboardMessage> dashboardMessages;

	private RiverMonitoringSystemState() {
		this.frequencyHistory = new ArrayList<>();
		this.waterLevelHistory = new ArrayList<>();
		this.dashboardMessages = new ArrayDeque<>();
	}

	public static RiverMonitoringSystemState getInstance() {
		if (instance == null) {
			instance = new RiverMonitoringSystemState();
		}
		return instance;
	}

	public synchronized void addDashboardMessage(final DashboardMessage msg) {
		this.dashboardMessages.add(msg);
	}

	public synchronized Optional<DashboardMessage> getLastDashboardMessage() {
		return Optional.ofNullable(this.dashboardMessages.poll());
	}

	public synchronized List<MQTTWaterLevel> getWaterLevelHistory() {
		return waterLevelHistory;
	}

	public synchronized Optional<MQTTWaterLevel> getLastWaterLevel() {
		if(waterLevelHistory.size() == 0) {
			return Optional.empty();
		}
		return Optional.of(waterLevelHistory.get(waterLevelHistory.size() - 1));
	}

	public synchronized Optional<MQTTFrequency> getLastFrequency() {
		if(frequencyHistory.size() == 0) {
			return Optional.empty();
		}
		return Optional.of(frequencyHistory.get(frequencyHistory.size() - 1));
	}

	public synchronized void addFrequency(final MQTTFrequency frequency) {
		this.frequencyHistory.add(frequency);
	}
}