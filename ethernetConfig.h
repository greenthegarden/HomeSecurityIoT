#ifndef SENSORLIGHTIOTMODULE_ETHERNETCONFIG_H_
#define SENSORLIGHTIOTMODULE_ETHERNETCONFIG_H_


// Ethernet libraries
#include <SPI.h>
#include <Ethernet.h>


const unsigned long NETWORK_STARTUP_DELAY = 5000UL;

const byte          ETHERNET_CS_PIN       = 10;


byte mac[]                                = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

IPAddress ip(192, 168, 1, 90);

EthernetClient ethernetClient;


#if USE_SDCARD
boolean readEthernetConfiguration() {
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
    
    if (cfg.nameIs("ipAddrStr")) { // ipAddr string (char *)
      // Dynamically allocate a copy of the string.
      char* str = cfg.copyValue();
      DEBUG_LOG(1, "Read ipAddrStr: ");
      DEBUG_LOG(1, str);
      ip.fromString(str);
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


#endif   /* SENSORLIGHTIOTMODULE_ETHERNETCONFIG_H_ */

