#include <PubSubClient.h>
#include <stdio.h>
#include <WiFiNINA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <MQTT.h>
#include "my_library.h"

// WiFi credentials
const char gNumber[15] = "Gxxxx0752";
const char* ssid = "Lokienest";
const char* password = "Adharsh@91967";
int status = WL_IDLE_STATUS;
WiFiClient wifiClient;
int myRand;
unsigned long wifiEpoch = 0;

// MQTT Broker Details
char mqttClienName[17] = "mgc-sv-iot-final";
const char* mqttTopic = "02a9c4da-80b8-4571-bb96-24ca990ac744/vehicle/proximity";

MQTTClient mqttClient;
PubSubClient brokerclient(wifiClient);

const int trigPinRight = 4;
const int echoPinRight = 7;
long duration;
float distance;
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
char lcdBuffer[64];

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  myRand = random(0, 9999);
  brokerclient.setServer(mqtt_server, mqtt_port);
  connectMQTT();
}

void connectMQTT() {
  Serial.print("Connecting to MQTT broker...");
  while (!brokerclient.connect("mgc-sv-iot-final")) { 
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected to MQTT broker");
}

void loop() {
  if (!brokerclient.connected()) {
    connectMQTT();
  }
  brokerclient.loop();

  float rightDistance = measureDistance(trigPinRight, echoPinRight);
  Serial.print("distance: ");
  Serial.println(distance);

  wifiEpoch = WiFi.getTime();
  convCurrentTimeET(wifiEpoch, lcdBuffer); 
  
  StaticJsonDocument<150> doc;
  doc["distance"] = rightDistance;
  doc["timestamp"] = String(lcdBuffer);
  char jsonBuffer[150];
  serializeJson(doc, jsonBuffer);


   brokerclient.publish(mqttTopic, jsonBuffer);
   Serial.println("Published to MQTT: " + String(jsonBuffer));

  //mqttClient.loop();
  delay(1000);
}

float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  Serial.println(duration);
  
  distance = duration * 0.034 / 2; // Speed of sound in cm/µs
  return distance;
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectMqtt(char *mqttClienName) 
{
  Serial.println("connectMqtt: Checking WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); delay(1000);
  }
  Serial.println("connectMqtt: WiFi Ok...");
 
  Serial.println("connectMqtt: Checking MQTT...");
  while (!mqttClient.connect(mqttClienName)) {
    Serial.print("."); delay(1000);
  }
  Serial.println("connectMqtt: MQTT Ok...");
}
