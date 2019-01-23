#include "mqttConfig.h"

#include <ArduinoJson.h>
#include <FS.h>

bool _spiffsMounted;

bool MqttConfig::connectMqtt(PubSubClient &client, WiFiClient &wifiClient)
{
    // For some reason PubSubClient and WiFiManager don't behave nicely together
    // but after some digging, I discovered that doing my own DNS lookup of the
    // mqtt_server solves it. Clearly WiFiManager is somehow screwing up the internal
    // wifi settings.
    // See my comment here for updates: https://github.com/tzapu/WiFiManager/issues/724#issuecomment-456617855
    IPAddress ipAddr;
    if (WiFi.hostByName(get_mqttServer().c_str(), ipAddr) != 1)
    {
        Serial.println("ERROR: Unable to resolve host name!");
        return false;
    }
    else
        Serial.printf("INFO: Host name resolved successfuly - %s\n", ipAddr.toString().c_str());

    // Loop until we're reconnected
    // Will only try 20 times before giving up
    int counter = 0;
    while (!client.connected() && (counter++ < 20))
    {
        Serial.println("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);

        Serial.printf("  server: %s\n", get_mqttServer().c_str());
        Serial.printf("  username: %s\n", get_mqttUsername().c_str());
        Serial.printf("  password: %s\n", get_mqttPassword().c_str());

        // Attempt to connect
        client.setClient(wifiClient);
        client.setServer(ipAddr, 1883);
        if (client.connect(clientId.c_str(), get_mqttUsername().c_str(), get_mqttPassword().c_str()))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("  failed, rc=");
            Serial.print(client.state());
            Serial.println("  try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }

    return client.connected();
}

bool MqttConfig::read()
{
    if (!_spiffsMounted)
    {
        if (!SPIFFS.begin())
        {
            Serial.println("ERROR: failed to mount SPIFFS");
            return false;
        }
        else
            _spiffsMounted = true;
    }

    if (!SPIFFS.exists(_filepath))
    {
        Serial.printf("ERROR: file %s does not exist\n", _filepath.c_str());
        return false;
    }

    File f = SPIFFS.open(_filepath, "r");

    StaticJsonBuffer<JSON_DOC_BUFFER_SIZE> jsonBuffer;
    JsonObject &root = jsonBuffer.parse(f);

    Serial.printf("MqttConfig::read() loaded the following JSON from %s\n", _filepath.c_str());
    root.printTo(Serial);
    Serial.println();

    if (root.containsKey("reset_settings"))
        _resetSettings = true;

    _mqttServer = root["mqtt_server"].as<String>();
    _mqttUsername = root["mqtt_username"].as<String>();
    _mqttPassword = root["mqtt_password"].as<String>();

    return true;
}

bool MqttConfig::save()
{
    if (!_spiffsMounted)
    {
        if (!SPIFFS.begin())
        {
            Serial.println("ERROR: failed to mount SPIFFS");
            return false;
        }
        else
            _spiffsMounted = true;
    }

    if (!SPIFFS.exists(_filepath))
    {
        Serial.printf("WARNING: (warning) file %s does not exist and will be created\n", _filepath.c_str());
    }

    Serial.println("Writing JSON:");
    StaticJsonBuffer<JSON_DOC_BUFFER_SIZE> jsonBuffer;

    JsonObject &root = jsonBuffer.createObject();
    // Note: We do not write the reset key
    root["mqtt_server"] = _mqttServer;
    root["mqtt_username"] = _mqttUsername;
    root["mqtt_password"] = _mqttPassword;

    File f = SPIFFS.open(_filepath, "w");
    root.printTo(f);
    f.flush();
    f.close();

    return true;
}

void MqttConfig::dumpAll(Stream &stream)
{
    stream.println("MqttConfig:");
    stream.printf(" - _resetSettings: %s\n", (_resetSettings ? "true" : "false"));
    stream.printf(" - _mqttServer: %s\n", _mqttServer.c_str());
    stream.printf(" - _mqttUsername: %s\n", _mqttUsername.c_str());
    stream.printf(" - _mqttPassword: %s\n", _mqttPassword.c_str());
}
