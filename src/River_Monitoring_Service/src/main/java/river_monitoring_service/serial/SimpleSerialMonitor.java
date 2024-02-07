package /* src.main.java. */river_monitoring_service.serial;

import com.fazecast.jSerialComm.*;

/**
 *
 */
public class SimpleSerialMonitor  {

	public static void main(String[] args) throws Exception {
		SerialPort[] ports = SerialPort.getCommPorts();
        String portName = null;

        for (SerialPort port : ports) {
            if (port.getDescriptivePortName().contains("Arduino")) {
                portName = port.getSystemPortName();
                break;
            }
        }

        if (portName == null) {
            System.out.println("Arduino port not found.");
            return;
        }
		System.out.println("Start monitoring serial port "+portName+" at 9600 boud rate");
		try {
			CommChannel monitor = new SerialCommChannel(portName, 9600);
			while(true) {
				if(monitor.isMsgAvailable()) {
					String msg = monitor.receiveMsg();
					System.out.print(msg);
				} else {
					System.out.print("No msg available");
				}

				Thread.sleep(1000);
			}
		} catch (InterruptedException ex) {
			ex.printStackTrace();
		}
	}
}