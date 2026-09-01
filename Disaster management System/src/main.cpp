// #include <Arduino.h>
// #include <WiFi.h>
// #include <PubSubClient.h>
// #include "DHT.h"

// // WiFi
// const char* ssid = "Wokwi-GUEST";
// const char* password = "";

// // MQTT (LOCAL BROKER)
// //const char* mqtt_server = "host.docker.internal"; // try "127.0.0.1" if this fails
// const char* mqtt_server = "127.0.0.1";

// WiFiClient espClient;
// PubSubClient client(espClient);

// // Sensors
// #define DHTPIN 4
// #define DHTTYPE DHT22
// #define MQ2_PIN 34

// // Alert
// #define LED 26
// #define BUZZER 27

// DHT dht(DHTPIN, DHTTYPE);

// // Connect WiFi
// void setup_wifi() {
//   delay(10);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(300);
//     Serial.print(".");
//   }
//   Serial.println("\nWiFi connected");
// }

// // Connect MQTT
// void reconnect() {
//   while (!client.connected()) {
//     Serial.print("Connecting MQTT...");
//     if (client.connect(("ESP32Client_" + String(random(1000))).c_str())) {
//       Serial.println("connected");
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       delay(2000);
//     }
//   }
// }

// void setup() {
//   Serial.begin(115200);

//   pinMode(LED, OUTPUT);
//   pinMode(BUZZER, OUTPUT);

//   dht.begin();

//   setup_wifi();
//   client.setServer(mqtt_server, 1883);
// }

// void loop() {
//   if (!client.connected()) {
//     reconnect();
//   }
//   client.loop();

//   float temp = dht.readTemperature();
//   int gas = analogRead(MQ2_PIN);

//   if (isnan(temp)) temp = 0;

//   String status = "SAFE";

//   if (temp > 50 || gas > 400) {
//     status = "EMERGENCY";
//     digitalWrite(LED, HIGH);
//     digitalWrite(BUZZER, HIGH);
//   } else {
//     digitalWrite(LED, LOW);
//     digitalWrite(BUZZER, LOW);
//   }

//   // Create JSON payload
//   String payload = "{";
//   payload += "\"temp\":" + String(temp) + ",";
//   payload += "\"gas\":" + String(gas) + ",";
//   payload += "\"status\":\"" + status + "\"}";

//   client.publish("disaster/data", payload.c_str());

//   Serial.println(payload);

//   delay(2000);
// }


#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// 👉 CHANGE THIS if needed
const char* serverUrl = "http://172.25.89.6:3000/data";

// Sensors
#define DHTPIN 4
#define DHTTYPE DHT22
#define MQ2_PIN 34

// Alert
#define LED 26
#define BUZZER 27

DHT dht(DHTPIN, DHTTYPE);

// WiFi Setup
void setup_wifi() {
  Serial.print("Connecting WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
}


void sendData(float temp, int gas, String status) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"temp\":" + String(temp) + ",";
    json += "\"gas\":" + String(gas) + ",";
    json += "\"status\":\"" + status + "\"}";

    int httpResponseCode = http.POST(json);

    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  dht.begin();
  setup_wifi();
}

void loop() {
  float temp = dht.readTemperature();
  int gas = analogRead(MQ2_PIN);

  if (isnan(temp)) temp = 0;

  String status = "SAFE";

  if (temp > 60 || gas > 3000) {
    status = "EMERGENCY";
  } 
  else if (temp > 50 || gas > 2000) {
    status = "DANGER";
  } 
  else if (temp > 40 || gas > 1000) {
    status = "WARNING";
  } 
  else {
    status = "SAFE";
  }

  if (status == "EMERGENCY" || status == "DANGER") {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
  }

  Serial.println("Temp: " + String(temp) + " Gas: " + String(gas) + " Status: " + status);

  sendData(temp, gas, status);

  delay(2000);
}