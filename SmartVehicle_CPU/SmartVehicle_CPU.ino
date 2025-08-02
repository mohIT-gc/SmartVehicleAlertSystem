#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "Lokienest"; 
const char* password = "Adharsh@91967"; 
String oledline[9];
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* subscribe_topic = "02a9c4da-80b8-4571-bb96-24ca990ac744/vehicle/proximity";
/*
Influx Account Credentials:
Username: mgalichi@gmu.edu
Password: Moheeth@91967
*/
const char* influxdb_host = "https://us-east-1-1.aws.cloud2.influxdata.com";
const int influxdb_port = 8086;
const char* influxdb_token = "NqkNe3S1XBM6q4JE5VMcJSsVGy-uPNvYDo4rSlwiMwW1KzE_RkFtK1a4G-SIlZiX17zJdPzTNYKvB9ISqdef3w==";
const char* influxdb_org = "7a9fd6adec8bbd83";
const char* influxdb_bucket = "MQTT-Mgalichi";
InfluxDBClient influxclient(influxdb_host, influxdb_org, influxdb_bucket, influxdb_token, InfluxDbCloud2CACert);
Point sensor("vehicle_proximity");
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_SSD1306 myOled(128, 64, &Wire, -1);

void callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<150> jsonDocument; 
  DeserializationError error = deserializeJson(jsonDocument, payload);

  if (error) {
    Serial.print("JSON Deserialization failed: ");
    Serial.println(error.c_str());
    return;
  }

  float distance = jsonDocument["distance"];
  const char* timestamp = jsonDocument["timestamp"];

  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Timestamp: ");
  Serial.println(timestamp);

  if(distance < 15) {
    int jj; for (jj=2; jj<=8; jj++){ oledline[jj]="DANGER"; }
  }
  else {
    int jj; for (jj=2; jj<=8; jj++){ oledline[jj]="SAFE"; }
  }
  if(distance <= 100){
  sensor.clearFields();
  sensor.addField("distance", distance);
  sensor.addField("Time", timestamp);
  if (!influxclient.writePoint(sensor)) { 
      Serial.print("InfluxDB write failed: ");
      Serial.println(influxclient.getLastErrorMessage());
    }
    else{
      Serial.println("Data saved to InfluxDB");
    }
  }
  displayTextOLED(oledline);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32C2Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(subscribe_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void displayTextOLED(String oledline[9])
{
  int jj;  
  myOled.clearDisplay();
  myOled.setTextSize(1);
  myOled.setTextColor(SSD1306_WHITE);
  myOled.setCursor(0, 0);

  for (jj=1; jj<=8; jj++) { 
    myOled.println(oledline[jj]);
    }
  
  myOled.display(); 
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Wire.begin(4, 5);
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if(!myOled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
  };
  oledline[1] = "Vehicle Proximity";  
  int jj; for (jj=2; jj<=8; jj++){ oledline[jj]=""; }
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  displayTextOLED(oledline);
  if (influxclient.validateConnection()) {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(influxclient.getServerUrl());
    } else {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(influxclient.getLastErrorMessage());
    }

  sensor.addTag("device", "esp32c3");
  sensor.addTag("SSID", WiFi.SSID());
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  client.setCallback(callback);

  delay(1000);
}