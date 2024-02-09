#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "./devices/led.h"
#include "./devices/sonar.h"
#include "functions.h"

#define GREEN_LED 38
#define RED_LED 39
#define MSG_BUFFER_SIZE 50
#define MAX_WIFI_CONNECT_ATTEMPTS 20  // Numero massimo di tentativi di connessione WiFi

char str[56];

/* Take global variables */
int frequency = 0;

/* wifi network info */
const char* ssid = "Redmi Note 8 Pro";
const char* password = "GiacomoFoschi";

/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com";

/* MQTT topic */
const char* topic1 = "frequency";
const char* topic2 = "waterLevel";

/*LED pointers*/
Led* redLed;
Led* greenLed;

/* MQTT client management */

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsgTime = 0;
char msg1[MSG_BUFFER_SIZE];

TaskHandle_t Task1;

void ledHandler(bool connectionStatus, Led* redLed, Led* greenLed) {
  if(connectionStatus) {
    greenLed->switchOn();
    redLed->switchOff();
  } else {
    greenLed->switchOff();
    redLed->switchOn();
  }
}

void setup_wifi() {
  Serial.println("Connecting to WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.waitForConnectResult() != WL_CONNECTED && attempts < MAX_WIFI_CONNECT_ATTEMPTS) {
    Serial.print(".");
    delay(500);
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    ledHandler(true, redLed, greenLed);
  } else {
    Serial.println("");
    Serial.println("Failed to connect to WiFi");
    ledHandler(false, redLed, greenLed);
  }
}

void handleWifiFailure() {
  Serial.println("Failed to connect to WiFi. Retrying in 5 seconds...");
  delay(5000);  // Attendi 5 secondi prima di ritentare la connessione
  setup_wifi();  // Ritenta la connessione WiFi
}

void callbackFrequency(char* topic, byte* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length );
  String payloadStr = "";
  for (int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }

  if (payloadStr.length() > 0 && payloadStr.toInt() != 0) {
    frequency = payloadStr.toInt();
    Serial.println(String("Received frequency: ") + frequency);
  } else {
    Serial.println("Invalid frequency value received");
  }
}

void reconnect() {
  int attempts = 0;
  while (!client.connected() && attempts < MAX_WIFI_CONNECT_ATTEMPTS) {
    Serial.print("Attempting MQTT connection...");
    ledHandler(false, redLed, greenLed);

    String clientId = String("esp-") + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      ledHandler(true, redLed, greenLed);
      client.subscribe(topic1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      ledHandler(false, redLed, greenLed);
      delay(5000);
    }

    attempts++;
  }
}

void setup() {
  if(!Serial) {
    Serial.begin(115200);
  }
  
  greenLed = new Led(GREEN_LED);
  redLed = new Led(RED_LED);

  greenLed->switchOff();
  redLed->switchOff();

  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callbackFrequency);

  // Assign task to OS
  xTaskCreatePinnedToCore(functions::waterDetectionTask, "Task1", 10000, NULL, 1, &Task1, 0);
}

void loop() {
  // try to connect to the server
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  StaticJsonDocument<56> waterLevelJson;

  if (now - lastMsgTime > (frequency)) {
    lastMsgTime = now;

    int waterLevel = functions::getWaterLevel();

    /* creating a msg in the buffer */
    snprintf(msg1, MSG_BUFFER_SIZE, "Water Level: %d", waterLevel);

    Serial.println(String("Publishing message: ") + msg1);

    waterLevelJson["WaterLevel"] = waterLevel;

    serializeJson(waterLevelJson, msg1);

    /* publishing the msg */
    client.publish(topic2, msg1);
  }
  
  // Handle WiFi failure independently in the loop
  if (WiFi.status() != WL_CONNECTED) {
    handleWifiFailure();
  }
}
