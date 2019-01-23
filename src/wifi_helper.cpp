#include "wifi_helper.h"

#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <FS.h>

#include <ArduinoJson.h>
#include <WiFiManager.h>

bool _shouldSaveConfig;

//callback notifying us of the need to save config
void saveConfigCallback()
{
    Serial.println("void saveConfigCallback()");
    _shouldSaveConfig = true;
}

WifiHelper::WifiHelper()
{
}

void WifiHelper::setup_wifi(MqttConfig& config)
{
    WiFi.mode(WIFI_STA);

    WiFiManager wifiManager;
    wifiManager.setDebugOutput(false);

    WiFiManagerParameter custom_mqtt_server("mqtt_server", "mqtt server", config.get_mqttServer().c_str(), 32);
    WiFiManagerParameter custom_mqtt_username("mqtt_username", "mqtt username", config.get_mqttUsername().c_str(), 32);
    WiFiManagerParameter custom_mqtt_password("mqtt_password", "mqtt password", config.get_mqttPassword().c_str(), 32);

    wifiManager.setSaveConfigCallback(saveConfigCallback);

    wifiManager.addParameter(&custom_mqtt_server);
    wifiManager.addParameter(&custom_mqtt_username);
    wifiManager.addParameter(&custom_mqtt_password);

    wifiManager.setMinimumSignalQuality(20);

    if (config.get_resetSettings())
    {
        Serial.println("Resetting wifi");
        wifiManager.resetSettings();
    }
    else
    {
        Serial.println("Reset command not found. Using existing configuration.");
        config.dumpAll(Serial);
    }

    // Timeout until configuration portal gets turned off
    // useful to make it all retry or go to sleep
    wifiManager.setTimeout(5*60);    // seconds

    // Connect if configured, otherwise start the config captive portal
    if (!wifiManager.autoConnect())
    {
        Serial.println("  WARNING: failed to connect and hit timeout. Shutting down.");
        delay(3000);
        // Captive portal didn't resolve, so we will deep sleep
        // You need to power cycle to get it to try again
        ESP.deepSleep(0);
    }

    Serial.print("Captive portal done, WiFi.getMode() = ");
    Serial.println(WiFi.getMode());

    //if you get here you have connected to the WiFi
    Serial.println("  WiFi connected successfully");

    // Save updated parameters
    if (_shouldSaveConfig)
    {
        config.set_mqttServer(custom_mqtt_server.getValue());
        config.set_mqttUsername(custom_mqtt_username.getValue());
        config.set_mqttPassword(custom_mqtt_password.getValue());
        config.save();
    }

    printWifiInfo(Serial);
    Serial.println("END WifiHelper::setup_wifi()");
}

void WifiHelper::printWifiInfo(Stream &stream)
{
    stream.println("-----------------------");

    stream.print("IP Address: ");
    stream.println(WiFi.localIP());

    stream.print("MAC Address: ");
    stream.println(WiFi.macAddress());

    stream.println("-----------------------");
}