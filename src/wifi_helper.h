#ifndef __WIFI_HELPER_H
#define __WIFI_HELPER_H

#include <Arduino.h>
#include <mqttConfig.h>

#define MAX_FILEPATH_LEN 31  // per the ESP8266 SPIFFS docs
#define MAX_CONFIG_STR_LEN 32

class WifiHelper
{
    String _mqttServer;
    String _mqttUsername;
    String _mqttPassword;

public:
    WifiHelper();
    void setup_wifi(MqttConfig& config);
    void printWifiInfo(Stream &stream);

private:

};

#endif // __WIFI_HELPER_H