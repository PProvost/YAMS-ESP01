[![Build Status](https://travis-ci.org/PProvost/YAMS-ESP01.svg?branch=master)](https://travis-ci.org/PProvost/YAMS-ESP01)

# YAMS-ESP01
Yet Another Motion Sensor - Uses an ESP01 and a cheap PIR motion sensor, sends activation events via MQTT,
optimized for very low power use.

## BOM

* ESP8266-01 Module
* HC-SR501 PIR Motion Detector
* MCP1700-3302E TO92 Voltage Regulator
* Resistors:
  - 220 ohm (x1)
  - 3.3K ohm (x1)
* Capacitors:
  - 1uF ceramic (x2)
  - 100nF ceramic (x1)
* Various pin headers, JST and molex connectors as you see fit
* Battery caddy (aim for > 4V but stay within the limits of the MCP1700-3302E)


## Implementation Notes:

* If you have a Puya-based ESP01 module, you may need to apply this patch to get SPIFFS to write correctly:
  https://github.com/letscontrolit/ESPEasy/blob/mega/patches/puya_v3.patch#L8
* You can force the WifiManager to reset its settings by writing the SPIFFS filesystem with a file called
  `/config.json` with the following contents: `{ "reset_settings": true }`. This file is included in the
  /data directory in this repo.

## Building the circuit

Credits: This circuit used in this design is based on the work described in [Benny de Leeuw's article][1].

IMPORTANT!: This is a 3.3V circuit. The common HC-SR501 PIR sensor is 5V, so you either need to maintain two power
voltages or modify the PIR to run on 3.3V.

Please refer to the schematic PDF and the other files in the schematic/ folder. I'm working on a board you will be
able to order from OSHPark, but until I have confirmed it works, you might be better off building it by hand on 
perf or strip board.

Once the board is confirmed working, I will also design a 3D printed enclosure for it.

## Circuit Notes

* The circuit is designed to be powered off of one lithium ion (LiPo) battery, and uses a low
  QI voltage regulator to provide the 3V3 expected by the ESP8266. This requires some special
  attention with your PIR sensor. Most of the cheap ones you will find expect 5V. See below for
  more information about modding your PIR sensor for 3V3.

* Because the ESP01 requires GPIO00 and GPIO02 to be HIGH when powering up, they're not appropriate
  for use as GPIO inputs. To get around this, I reused RXD as a GPIO pin as described in [ESP8266-01 Pin Magic][2].
  This means you can't use serial commands to talk TO the device, but it can still send serial logging
  to the serial monitor.

* I wanted to reuse the VCC pin on the PIR sensor to make mounting easier, but also to power the PIR sensor
  with the same 3.3VDC the ESP takes. For some of my sensors, I made the following modifications successfully:
  - Removed the 3V3 voltage regulator
  - Connected the cathode (output) side of the diode to the VOUT pad where the regulator had been connected
  - Removed the 1k resistor between the controller IC and the signal pin and shorted the two pads.
  - NOTE:This permanently changes the sensor to only take 3.3V, do not power it with 5V after removing the regulator.
    If you don't want to remove the regulator from your sensor, you can still power it with 3.3V following the guide [Modifying Cheap PIR Sensors][3], but you may still need to remove the 1k resistor. I've used this approach too.

## Credits & References

1. [Stable ESP01 Motion Sensor][1]
2. [ESP01 Pin Magic][2]
3. [Modifying Cheap PIR Sensors][3]

## TODO:

* Provide a better HASS discovery message
* Enable [OTA updating](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html),
  particularly for updating the config.json file but also maybe the firmware.
* Better case design
* Button/switch/jumper to make it stay awake (can help with network debugging; see also the DO_NOT_SLEEP define
  in main.cpp)
* Optional front facing LED when motion detected
* Figure out a reset button so you can reset the configuration without flashing the SPIFFS filesystem

[1]: https://medium.com/@leeuwte/stable-esp01-motion-sensor-for-mqtt-2d81c0b1e317
[2]: http://www.forward.com.au/pfod/ESP8266/GPIOpins/ESP8266_01_pin_magic.html
[3]: https://randomnerdtutorials.com/modifying-cheap-pir-motion-sensor-to-work-at-3-3v/
