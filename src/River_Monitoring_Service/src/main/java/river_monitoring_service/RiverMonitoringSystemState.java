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
	private List<MQTTFrequency> frequencyStateHistory;
	private List<MQTTWaterLevel> waterLevelStateHistory;
	private Queue<DashboardMessage> dashboardMessages;

	private RiverMonitoringSystemState() {
		this.frequencyHistory = new ArrayList<>();
		this.waterLevelStateHistory = new ArrayList<>();
		this.dashboardMessages = new ArrayDeque<>();
		this.frequencyStateHistory = new ArrayList<>();
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

	public synchronized List<MQTTFrequency> getFrequencyStateHistory() {
		return this.frequencyStateHistory;
	}

	public synchronized Optional<MQTTFrequency> getLastFrequencyState() {
	    if(this.frequencyStateHistory.size() == 0) {
	        return Optional.empty();
	    }
	    return Optional.of(this.frequencyStateHistory.get(this.frequencyStateHistory.size() - 1));
	}

	public synchronized List<MQTTWaterLevel> getWaterLevelStateHistory() {
		return waterLevelStateHistory;
	}

	public synchronized Optional<MQTTWaterLevel> getLastWaterLevelState() {
           if(waterLevelStateHistory.size() == 0) {
               return Optional.empty();
           }
           return Optional.of(waterLevelStateHistory.get(waterLevelStateHistory.size() - 1));
	}

	public synchronized Optional<MQTTFrequency> getLastFrequency() {
            if(frequencyHistory.size() == 0) {
                return Optional.empty();
            }
            return Optional.of(frequencyHistory.get(frequencyHistory.size() - 1));
        }

        public synchronized List<MQTTFrequency> getFrequencyHistory() {
                return this.frequencyHistory;
        }
}