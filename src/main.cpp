#include <Arduino.h>
#include <ESP8266Wifi.h>
#include <PubSubClient.h>

// TODO: move these to ../ap_setting.h
const char* device_host_name = "esp8266-motion-1";
const char* ssid = "Provost-Mesh";
const char* password = "cra6ga12o4doph09";
const char* mqtt_server = "hassio.lan";
const char* mqtt_username = "mqtt_user";
const char* mqtt_password = "mqtt_pass";

//Static IP address configuration
IPAddress staticIP(192, 168, 135, 10); //ESP static ip
IPAddress gateway(192, 168, 135, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(192, 168, 135, 1);  //DNS

#define INACTIVE_DELAY  2000

// change the motions sensor topic as appropriate
const char* mqtt_topic_template = "network/DEVICE_HOST_NAME/motion/state";

WiFiClient wifiClient;
PubSubClient client(wifiClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.hostname(device_host_name);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      // ... and resubscribe
      // client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
//   pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  // client.setCallback(callback);

  Serial.println("Starting...");
  if (!client.connected()) {
    reconnect();
  }
}

void loop() {
  String mqttTopic = mqtt_topic_template;
  mqttTopic.replace("DEVICE_HOST_NAME", device_host_name);
  
  client.loop();
  Serial.println("- Sending active message");
  client.publish(mqttTopic.c_str(), "on");

  delay(INACTIVE_DELAY);
  
  Serial.println("- Sending inactive message");
  client.publish(mqttTopic.c_str(), "off");

  client.loop();
  delay(100);
  Serial.println("Sleeping...");

  ESP.deepSleep(0);

}