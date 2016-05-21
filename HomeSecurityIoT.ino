#include "config.h"

boolean mqtt_connect()
{
  DEBUG_LOG(1, "Attempting MQTT connection ...");
  if (mqttClient.connect(mqttClientId)) {
    DEBUG_LOG(1, "  connected");
    // Once connected, publish an announcement ...
    publish_connected();
    publish_ip_address();
    // ... and subscribe to topics (should have list)
    mqttClient.subscribe("homesecurity/control/#");
  } else {
      DEBUG_LOG(1, "failed, rc = ");
      DEBUG_LOG(1, mqttClient.state());
  }
  return mqttClient.connected();
}

void callback(char* topic, uint8_t* payload, unsigned int payloadLength)
{
  // handle message arrived
  /* topic = part of the variable header:has topic name of the topic where the publish received
       NOTE: variable header does not contain the 2 bytes with the
            publish msg ID
      payload = pointer to the first item of the buffer array that
                contains the message tha was published
               EXAMPLE of payload: lights,1
      length = the length of the payload, until which index of payload
  */

  DEBUG_LOG(1, "Payload length is");
  DEBUG_LOG(1, payloadLength);

  // Copy the payload to the new buffer
  char* message = (char*)malloc((sizeof(char) * payloadLength) + 1); // get the size of the bytes and store in memory
  memcpy(message, payload, payloadLength * sizeof(char));        // copy the memory
  message[payloadLength * sizeof(char)] = '\0';                  // add terminating character

  DEBUG_LOG(1, "Message with topic");
  DEBUG_LOG(1, topic);
  DEBUG_LOG(1, "arrived with payload");
  DEBUG_LOG(1, message);

  byte topicIdx = 0;
  boolean controlTopicFound = false;

  // find if topic is matched
  for (byte i = 0; i < ARRAY_SIZE(CONTROL_TOPICS); i++) {
    progBuffer[0] = '\0';
    strcpy_P(progBuffer, (PGM_P)pgm_read_word(&(CONTROL_TOPICS[i])));
    if (strcmp(topic, progBuffer) == 0) {
      topicIdx = i;
      controlTopicFound = true;
      break;
    }
  }

  if (controlTopicFound) {
    DEBUG_LOG(1, "Control topic index");
    DEBUG_LOG(1, topicIdx);
    //switch to case statements
    if (topicIdx == 0) {  // topic is LED_CONTROL
    } else {  // unknown control topic has arrived - ignore!!
      DEBUG_LOG(1, "Unknown control topic arrived");
    }
  }

  // free memory assigned to message
  free(message);
}


/*--------------------------------------------------------------------------------------
  setup()
  Called by the Arduino framework once, before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup()
{
#if DEBUG_LEVEL > 0
  Serial.begin(BAUD_RATE);
#endif

#if USE_SDCARD
  // configure chip select pins for SD card and Ethernet
  pinMode(SDCARD_CS_PIN, OUTPUT);      // set SD card chip select as output:
  pinMode(ETHERNET_CS_PIN, OUTPUT);    // set Ethernet chip select as output:

  pinMode(ETHERNET_CS_PIN, HIGH);      // disable ethernet by pulling high its chip select:
  // Setup the SD card 
  DEBUG_LOG(1, "Calling SD.begin() ...");
  if (!SD.begin(SDCARD_CS_PIN)) {
    DEBUG_LOG(1, "SD.begin() failed.");
    DEBUG_LOG(1, "Using default settings");
  }
  DEBUG_LOG(1, "... succeeded.");

  // Read configurations from the SD card file.
  readEthernetConfiguration();

  readMqttConfiguration();
#endif

  // Configure Ethernet
  delay(NETWORK_STARTUP_DELAY); // allow some time for Ethernet processor to come out of reset on Arduino power up:
  Ethernet.begin(mac, ip);
  
  // set up for PIR sensor
  securitySensorShieldSetup();
}

/*--------------------------------------------------------------------------------------
  loop()
  Arduino main loop
  --------------------------------------------------------------------------------------*/
void loop()
{
  unsigned long now = millis();

#if 0
  if (!mqttClient.connected()) {
    mqttClientConnected = false;
    if (now - lastReconnectAttempt > RECONNECTION_ATTEMPT_INTERVAL) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (mqtt_connect()) {
        lastReconnectAttempt = 0;
        mqttClientConnected = true;
      }
    }
  } else {
    // Client connected
    mqttClient.loop();
  }
#endif

  if (now - sensorReadPreviousMillis >= SENSOR_READ_INTERVAL) {
    sensorReadPreviousMillis = now;
    // if not connected to mqttClient run different behaviour
    if (!mqttClientConnected) {
      no_network_behaviour();
    }
  }

}
