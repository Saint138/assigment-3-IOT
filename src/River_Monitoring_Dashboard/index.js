// dashboard.js

const BASE_PATH = /* "http://localhost:8080" */ "http://localhost/assigment-3-IOT/src/River_Monitoring_Dashboard/";

// Function to update the water level graph
function updateGraph() {
  // Use a charting library or your own logic to update the graph
  console.log("Updating graph...");
}

// Function to update the system state
function updateSystemState(newState) {
  const systemStateElement = document.getElementById("system-state");
  systemStateElement.textContent = newState;
}

// Function to handle valve control
function handleValveControl() {
  const valveLevelElement = document.getElementById("valve-level");
  const valveLevel = valveLevelElement.value;
  console.log(`Valve level set to: ${valveLevel}%`);
  // You can send the valve level to the server or perform other actions

  // Example: Sending data to the server using fetch
  const formData = new FormData();
  formData.append("valveLevel", valveLevel);

  fetch(BASE_PATH + "/api/updateValve", {
    method: "post",
    body: formData,
  });

  // Disable the button temporarily
  const controlButton = document.getElementById("control-button");
  controlButton.disabled = true;

  // Set a timeout to re-enable the button after 10 seconds
  setTimeout(() => {
    controlButton.disabled = false;
  }, 10000);
}

// Event listener for the control button
const controlButton = document.getElementById("control-button");
controlButton.addEventListener("click", handleValveControl);

// Simulate periodic updates (replace with real-time data fetching)
setInterval(() => {
  // Update the graph (replace with real-time data fetching and rendering)
  updateGraph();

  // Simulate system state changes
  const systemStates = [
    "NORMAL",
    "ALARM-TOO-LOW",
    "PRE-ALARM-TOO-HIGH",
    "ALARM-TOO-HIGH",
    "ALARM-TOO-HIGH-CRITIC",
  ];
  const randomState =
    systemStates[Math.floor(Math.random() * systemStates.length)];
  updateSystemState(randomState);
}, 5000); // Update every 5 seconds (adjust as needed)
