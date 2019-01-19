#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// NOTE: This file is NOT included in the github repo. You need to create it
// yourself to include your own network settings. (See the next set of const char*
// declarations for the required defines.)
#ifndef TRAVIS_CI
#include "../../ap_setting.h"
#else
#include "sample_ap_setting.h"
#endif

const char *device_host_name = "esp8266-motion-1";
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
const char *mqtt_server = MQTT_HOST;
const char *mqtt_username = MQTT_USER;
const char *mqtt_password = MQTT_PASSWORD;

//Static IP address configuration
IPAddress staticIP(192, 168, 135, 6); //ESP static ip - see static IP config in setup_wifi()
IPAddress gateway(192, 168, 135, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);    //Subnet mask
IPAddress dns(192, 168, 135, 1);       //DNS

#define INACTIVE_DELAY 2000 // milliseconds between "on" state and "off" state

// change the motions sensor topic as appropriate.
const char *mqtt_topic_template = "esp8266/binary_sensor/DEVICE_HOST_NAME/";

WiFiClient wifiClient;
PubSubClient client(wifiClient);
long lastMsg = 0;
char msg[50];
int value = 0;

uint8_t macAddressBytes[6];
char macAddressString[18];

void setup_wifi()
{
  WiFi.macAddress(macAddressBytes);
  for(int i=0; i<sizeof(macAddressBytes); ++i)
    sprintf(macAddressString, "%s%02x:", macAddressString, macAddressBytes[i]);
  Serial.print("MAC Address: ");
  Serial.println(macAddressString);

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.hostname(device_host_name);
  // Uncomment to use a static IP address  
  // WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("connected");
      Serial.println("- Sending HASS discovery message");

      String mqttTopic = mqtt_topic_template;
      mqttTopic.replace("DEVICE_HOST_NAME", device_host_name);
      mqttTopic.concat("config");

      String message = "{ \"name\": \"DEVICE_NAME\", \"device_class\": \"motion\" }";
      message.replace("DEVICE_NAME", device_host_name);
      client.publish(mqttTopic.c_str(), message.c_str());
      client.loop();

    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  //   pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  // client.setCallback(callback);

  Serial.println("Starting...");
  if (!client.connected())
  {
    reconnect();
  }
}

void loop()
{
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

  ESP.deepSleep(0);
}

// If we want to subscribe to notifications, this is the callback
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

