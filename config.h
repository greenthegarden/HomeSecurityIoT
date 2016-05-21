#ifndef HOMESECURITYIOT_CONFIG_H_
#define HOMESECURITYIOT_CONFIG_H_


#include "debug.h"

// Macros
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


const byte BUFFER_SIZE            = 32;
char progBuffer[BUFFER_SIZE];
char charBuffer[BUFFER_SIZE];

const int FLOAT_DECIMAL_PLACES    = 1;

const int BAUD_RATE               = 9600;


#define USE_SDCARD false

#if USE_SDCARD
#include "sdConfig.h"
#endif

#include "ethernetConfig.h"
#include "mqttConfig.h"

#include "oledShieldConfig.h"
#include "securityShieldConfig.h"

boolean mqttClientConnected = false;

void no_network_behaviour() {
  if(checkSensor(CONNECTED_SENSORS[0], SENSOR_OUTPUTS[0]) != NORMAL_STATE) {
    repeatTone();
  }
}


#endif   /* HOMESECURITYIOT_CONFIG_H_ */

