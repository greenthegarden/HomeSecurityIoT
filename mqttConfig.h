#ifndef HOMESECURITYIOT_MQTTCONFIG_H_
#define HOMESECURITYIOT_MQTTCONFIG_H_


#include <PubSubClient.h>


// MQTT parameters
IPAddress mqttServerAddr(192, 168, 1, 55);        // Pi eth0 interface                      
char* mqttClientId                                = "homesecurity";
int mqttPort                                      = 1883;
//#define MQTT_MAX_PACKET_SIZE                      168
//#define MQTT_KEEPALIVE                            300

unsigned long lastReconnectAttempt                = 0UL;
const unsigned long RECONNECTION_ATTEMPT_INTERVAL = 30UL * 1000UL;  // attempt to reconnect every 30 seconds

//const char COMMAND_SEPARATOR        = ':';

char message[BUFFER_SIZE];


// Status topics

const char CONNECTED_STATUS[]   PROGMEM = "homesecurity/status/connected";
const char IP_ADDR_STATUS[]     PROGMEM = "homesecurity/status/ip_addr";
const char UPTIME_STATUS[]      PROGMEM = "homesecurity/status/uptime";
const char MEMORY_STATUS[]      PROGMEM = "homesecurity/status/memory";
const char TIME_STATUS[]        PROGMEM = "homesecurity/status/time";
const char LED_STATUS[]         PROGMEM = "homesecurity/status/sensor";

PGM_P const STATUS_TOPICS[]     PROGMEM = { CONNECTED_STATUS,    // idx = 0
                                            IP_ADDR_STATUS,      // idx = 1
                                            UPTIME_STATUS,       // idx = 2
                                            MEMORY_STATUS,       // idx = 3
                                            TIME_STATUS,         // idx = 4
                                            LED_STATUS,       // idx = 5
                                           };


// Control topics

const char SENSOR_CONTROL[]     PROGMEM = "homesecurity/control/led";

PGM_P const CONTROL_TOPICS[]    PROGMEM = { SENSOR_CONTROL,      // idx = 0
                                          };

#if USE_SDCARD
boolean readMqttConfiguration() {
  /*
   * Length of the longest line expected in the config file.
   * The larger this number, the more memory is used
   * to read the file.
   * You probably won't need to change this number.
   */
  const uint8_t CONFIG_LINE_LENGTH = 32;
  
  // The open configuration file.
  SDConfigFile cfg;
  
  // Open the configuration file.
  if (!cfg.begin(CONFIG_FILE, CONFIG_LINE_LENGTH)) {
    DEBUG_LOG(1, "Failed to open configuration file: ");
    DEBUG_LOG(1, CONFIG_FILE);
    return false;
  }
  
  // Read each setting from the file.
  while (cfg.readNextSetting()) {
    
    // Put a nameIs() block here for each setting you have.
    
    if (cfg.nameIs("mqttBrokerIP")) {
      // Dynamically allocate a copy of the string.
      char* str = cfg.copyValue();
      mqttServerAddr.fromString(str);
      DEBUG_LOG(1, "Read mqttBrokerIP: ");
      DEBUG_LOG(1, str);
    } else if (cfg.nameIs("mqttClientId")) { // mqttClientId string (char *)
      // Dynamically allocate a copy of the string.
      mqttClientId = cfg.copyValue();
      DEBUG_LOG(1, "Read mqttClientId: ");
      DEBUG_LOG(1, mqttClientId);
    } else if (cfg.nameIs("mqttPort")) { // mqttPort integer
      mqttPort = cfg.getIntValue();
      DEBUG_LOG(1, "Read mqttPort: ");
      DEBUG_LOG(1, mqttPort);
    } else {
      // report unrecognized names.
      DEBUG_LOG(1, "Unknown name in config: ");
      DEBUG_LOG(1, cfg.getName());
    }
  }
  
  // clean up
  cfg.end();
}
#endif

// callback function definition
void callback(char* topic, uint8_t* payload, unsigned int length);

PubSubClient   mqttClient(mqttServerAddr, mqttPort, callback, ethernetClient);

void publish_connected()
{
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[0])));
  mqttClient.publish(progBuffer, "");
}

void publish_ip_address()
{
  const byte IP_ADDRESS_BUFFER_SIZE = 16; // "255.255.255.255\0"
  static char ipString[IP_ADDRESS_BUFFER_SIZE] = "";
  IPAddress ip = Ethernet.localIP();
  sprintf(ipString, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[1])));
  mqttClient.publish(progBuffer, ipString);
}

void publish_uptime()
{
  progBuffer[0] = '\0';
  strcpy_P(progBuffer, (char*)pgm_read_word(&(STATUS_TOPICS[2])));
  charBuffer[0] = '\0';
  ltoa(millis(), charBuffer, 10);
  mqttClient.publish(progBuffer, charBuffer);
}


#endif   /* HOMESECURITYIOT_MQTTCONFIG_H_ */
