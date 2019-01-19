[![Build Status](https://travis-ci.org/PProvost/YAMS-ESP01.svg?branch=master)](https://travis-ci.org/PProvost/YAMS-ESP01)

# YAMS-ESP01
Yet Another Motion Sensor - Uses an ESP01 and a cheap PIR motion sensor, sends activation events via MQTT,
optimized for very low power use.

Credits: This design is based on the work described in Benny de Leeuw's article 
[Stable ESP01 Motion Sensor](https://medium.com/@leeuwte/stable-esp01-motion-sensor-for-mqtt-2d81c0b1e317).

## TODO:

* Add [WiFiManager](https://github.com/tzapu/WiFiManager) for easier setup and provisioning
* Enable [OTA updating](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html)
* Better case design
* Button/switch/jumper to make it stay awake (network debugging)
* Optional front facing LED when motion detected