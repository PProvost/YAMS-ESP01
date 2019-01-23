#ifndef __MQTTCONFIG_H
#define __MQTTCONFIG_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define JSON_DOC_BUFFER_SIZE 256

class MqttConfig
{
  String _filepath;
  bool _resetSettings;
  String _mqttServer;
  String _mqttUsername;
  String _mqttPassword;

public:
  MqttConfig(const char *filepath) : _filepath(filepath), _resetSettings(false) {}

  bool get_resetSettings() { return _resetSettings; }

  String get_mqttServer() { return _mqttServer; }
  void set_mqttServer(String val) { _mqttServer = val; }

  String get_mqttUsername() { return _mqttUsername; }
  void set_mqttUsername(String val) { _mqttUsername = val; }

  String get_mqttPassword() { return _mqttPassword; }
  void set_mqttPassword(String val) { _mqttPassword = val; }

  bool read();
  bool save();

  bool connectMqtt(PubSubClient& client, WiFiClient& wifiClient);

  void dumpAll(Stream &stream);
};

#endif // __MQTTCONFIG_H