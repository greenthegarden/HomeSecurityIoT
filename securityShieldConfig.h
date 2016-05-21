#ifndef HOMESECURITYIOT_SECURITYSHIELDCONFIG_H_
#define HOMESECURITYIOT_SECURITYSHIELDCONFIG_H_


// Macros
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

// Use analog inputs 0 through 3 for sensor connections A through D
const byte channelAInput = 0;
const byte channelBInput = 1;
const byte channelCInput = 2;
const byte channelDInput = 3;

// Use digital outputs 4 through 7 for status indicator LEDs A through D
const byte channelALed = 4;
const byte channelBLed = 5;
const byte channelCLed = 6;
const byte channelDLed = 7;


const byte CONNECTED_SENSORS[] = { channelAInput };
const byte SENSOR_OUTPUTS[] = { channelALed };

// sensor states
const byte WIRE_SHORTED = 0;
const byte NORMAL_STATE = 1;
const byte SENSOR_TRIGGERED = 2;
const byte TAMPERED = 3;

unsigned long sensorReadPreviousMillis       = 0UL;

const unsigned long SENSOR_READ_INTERVAL = 1000UL;           // interval at which to take measurement (milliseconds)

boolean previousSensorDetection          = false;


void securitySensorShieldSetup()
{
  for (byte idx = 0; idx < ARRAY_SIZE(CONNECTED_SENSORS); idx++) {
    pinMode(CONNECTED_SENSORS[idx], INPUT);
  }
  for (byte idx = 0; idx < ARRAY_SIZE(SENSOR_OUTPUTS); idx++) {
    pinMode(SENSOR_OUTPUTS[idx], OUTPUT);
    digitalWrite(SENSOR_OUTPUTS[idx], LOW);
  }
}


/**
 * Checks the state of a sensor and reports it to the connected host
 */
byte checkSensor(byte sensorInput, byte statusOutput)
{
  int sensorReading = analogRead(sensorInput);
  DEBUG_LOG(1, "Sensor reading: ");
  DEBUG_LOG(1, sensorReading);
  if( sensorReading < 400 ) {
    // Wire shorted. Possible tampering.
    DEBUG_LOG(1, "WIRE SHORTED");
    digitalWrite(statusOutput, HIGH); // Turn the associated status LED on
    return WIRE_SHORTED;
  } else if ( sensorReading >= 400 && sensorReading < 590 ) {
    // Normal state, sensor not triggered
    DEBUG_LOG(1, "NORMAL STATE");
    digitalWrite(statusOutput, LOW); // Turn the associated status LED off
    return NORMAL_STATE;
  } else if ( sensorReading >= 590 && sensorReading < 800 ) {
    // Sensor triggered.
    DEBUG_LOG(1, "SENSOR TRIGGERED");
    digitalWrite(statusOutput, HIGH); // Turn the associated status LED on
    return SENSOR_TRIGGERED;
  } else {
    // Open circuit. Cut or tamper triggered.
    DEBUG_LOG(1, "TAMPERED");
    digitalWrite(statusOutput, HIGH); // Turn the associated status LED on
    return TAMPERED; 
  }
}

//void publish_pir_status() {
//  progBuffer[0] = '\0';
//  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[7])));
//  if(previousPirDetection) {
//    DEBUG_LOG(1, "pir sensor detection");
//    mqttClient.publish(progBuffer, "1");
//  }
//  else {
//    DEBUG_LOG(1, "pir sensor NO detection");
//    mqttClient.publish(progBuffer, "0");
//  }
//}
//
//void read_pir_sensor() {
//  boolean currentPirDetection;
//  if(digitalRead(PIR_SENSOR_PIN) == HIGH)
//    currentPirDetection = true;
//  else
//    currentPirDetection = false;
//  if (currentPirDetection != previousPirDetection) {
//    previousPirDetection = currentPirDetection;
//    publish_pir_status();
//  }
//}


#endif   /* HOMESECURITYIOT_SECURITYSHIELDCONFIG_H_ */

