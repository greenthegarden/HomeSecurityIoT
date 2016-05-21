# Sensor Light IoT Module

Project is for a replacement 'smart' LED based sensor light module based around the [duinotech 595](http://www.jaycar.com.au/Kits%2C-Science-%26-Learning/Science-Lab-Equipment/Instruments/Arduino-Compatible-4-x-5050-RGB-LED-Module/p/XC4466) RGB led module and PIR Motion Sensor Module. The 'smarts' are provided via an MQTT interface which allows control over the operation of the module. Provision for a [DHT22](http://www.freetronics.com.au/collections/modules/products/humidity-and-temperature-sensor-module) temperature/humidity sensor is also included.

The following libraries are required to compile the code:
* MQTT (PubSubClient): https://github.com/knolleary/pubsubclient
* duinotech595: https://github.com/greenthegarden/duinotech595
* SDConfigFile: https://github.com/bneedhamia/sdconfigfile
* dht, included in: https://github.com/RobTillaart/Arduino

Also include in the repository are [python scripts](extras/python) used to test the MQTT interface and an [OpenHAB](http://openhab.org) [configuration](extras/openhab) which provides an example of how the module could be incorporated into a home automation environment.

The following images show the OpenHAB GUI

![OpenHAB main](docs/openhab-home.png)

![OpenHAB sensors](docs/openhab-temperatures.png)

![OpenHAB airboardstatus](docs/openhab-airboardstatus.png)
