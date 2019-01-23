[![Build Status](https://travis-ci.org/PProvost/YAMS-ESP01.svg?branch=master)](https://travis-ci.org/PProvost/YAMS-ESP01)

# YAMS-ESP01
Yet Another Motion Sensor - Uses an ESP01 and a cheap PIR motion sensor, sends activation events via MQTT,
optimized for very low power use.

Credits: This design is based on the work described in Benny de Leeuw's article 
[Stable ESP01 Motion Sensor](https://medium.com/@leeuwte/stable-esp01-motion-sensor-for-mqtt-2d81c0b1e317).

## Notes:

* If you have a Puya-based ESP01 module, you may need to apply this patch to get SPIFFS to write correctly:
  https://github.com/letscontrolit/ESPEasy/blob/mega/patches/puya_v3.patch#L8
* You can force the WifiManager to reset its settings by writing the SPIFFS filesystem with a file called
  `/config.json` with the following contents: `{ "reset_settings": true }`

## TODO:

* Provide a better HASS discovery message
* Enable [OTA updating](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html),
  particularly for updating the config.json file but also maybe the firmware.
* Better case design
* Button/switch/jumper to make it stay awake (can help with network debugging; see also the DO_NOT_SLEEP define
  in main.cpp)
* Optional front facing LED when motion detected
* Figure out a reset button so you can reset the configuration without flashing the SPIFFS filesystem