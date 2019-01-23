#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "mqttConfig.h"
#include "wifi_helper.h"

// Change this for each device you create
const char *device_host_name = "esp8266-motion-1";

// Change the motion sensor topic as required for your configuration.
// Note that for HASS discovery to work, the structure is expected to be
// <discovery_prefix>/<component>/[<node_id>/]<object_id>
// I'm not using node_id, and the code below will append either "config" 
// (for discovery) or "state" as required.
// See https://www.home-assistant.io/docs/mqtt/discovery/ for more info.
const char *mqtt_topic_template = "esp8266/binary_sensor/DEVICE_HOST_NAME/";

// DEBUGGING: Uncomment to prevent deep sleep at the end of loop() and
// instead just delay for 5s. Useful for debugging or when you need to keep it
// awake. Do not leave this defined or your battery will die in days.
// #define DO_NOT_SLEEP

// This is the number of milliseconds between "on" state and "off" state.
// For simplicity, we do not wait for the PIR to register inactive.
#define INACTIVE_DELAY 2000

PubSubClient client;
MqttConfig config("/config.json");
WifiHelper wifiHelper;
WiFiClient wifiClient;

// Forward declarations
void ensure_mqtt_connected();
void sendHassDiscoveryMessage();

void setup()
{
  Serial.begin(115200);
  // delay(2000); // Make it easier to monitor from the start. Remove when done debugging.
  Serial.println();

  Serial.println("setup() starting");

  config.read();
  wifiHelper.setup_wifi(config);

  Serial.println("Opening MQTT connection...");
  if (!client.connected())
    config.connectMqtt(client, wifiClient);

  sendHassDiscoveryMessage();

  Serial.println("INFO: setup() complete; Wifi and MQTT connected");
}

void loop()
{
  Serial.println("loop(): current config:");
  config.dumpAll(Serial);
  Serial.println();

  String mqttTopic = mqtt_topic_template;
  mqttTopic.replace("DEVICE_HOST_NAME", device_host_name);
  mqttTopic.concat("state");

  // Send on
  Serial.println("- Sending active message");
  client.publish(mqttTopic.c_str(), "ON");
  client.loop();

  // Wait a bit
  delay(INACTIVE_DELAY);

  // Send off
  Serial.println("- Sending inactive message");
  client.publish(mqttTopic.c_str(), "OFF");
  client.loop();

  delay(100);
  Serial.println("Sleeping...");

#ifndef DO_NOT_SLEEP
  ESP.deepSleep(0);
#else
  delay(5000);
#endif
}

void sendHassDiscoveryMessage()
{
  Serial.println("- Sending HASS discovery message");

  String mqttTopic = mqtt_topic_template;
  mqttTopic.replace("DEVICE_HOST_NAME", device_host_name);
  mqttTopic.concat("config");

  String message = "{ \"name\": \"DEVICE_NAME\", \"device_class\": \"motion\" }";
  message.replace("DEVICE_NAME", device_host_name);
  client.publish(mqttTopic.c_str(), message.c_str());
  client.loop();
}

// NOTE: 
// If we want to subscribe to MQTT messages for commands or settings, this is the callback
// void callback(char* topic, byte* payload, unsigned int length) {
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("] ");
//   for (int i = 0; i < length; i++) {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();
//   // Switch on the LED if an 1 was received as first character
//   if ((char)payload[0] == '1') {
//     // digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//     // but actually the LED is on; this is because
//     // it is active low on the ESP-01)
//   } else {
//     // digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//   }
// }