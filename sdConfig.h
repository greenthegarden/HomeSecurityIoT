#ifndef SENSORLIGHTIOTMODULE_SDCONFIG_H_
#define SENSORLIGHTIOTMODULE_SDCONFIG_H_


#include <SPI.h>
#include <SD.h>
#include <SDConfigFile.h>


const byte SDCARD_CS_PIN = 4;  // define SD Card chip select pin

//File configFile;

const char CONFIG_FILE[] = "SensorLightIoTModule.cfg";

//void readFile()
//{
//  File file;
//
//  file = SD.open(CONFIG_FILE);
//  if (file) {
//    // array for value data:
//    while (file.available()) {       // read the settings file:
//      byte i = 0;
//      boolean paramEnd = false;
//
//      while (!paramEnd) {        // while not at the end of the parameter keep reading:
//        chtr = file.read();
//        if (chtr != ':') {        // if the char from file is not a':' read it in:
//          name[i] = chtr;
//          i++;
//        } else {
//          paramEnd = true;                 // otherwise we have come to the end of our parmeter name:
//        }
//      }
//      byte j = 0;
//      boolean valueEnd = false;
//      value[0] = '\0';                               // reset our array pointer:
//      while (!valueEnd) {
//        chtr = file.read();
//        if (chtr != ',') {     // if the char from file is not a ',' read it in:
//          value[j] = chtr;
//          j++;
//        } else {
//          valueEnd = true;   // otherwise we have come to the end of our value:
//        }
//      }
//
//      if (!strcmp(name, "ip0")) {
//        ip[0] = atoi(value);          // assign value to ip0 first ip octet:
//      }
//      if (!strcmp(name, "ip1")) {
//        ip[1] = atoi(value);          // assign value to ip1 first ip octet:
//      }
//      if (!strcmp(name, "ip2")) {
//        ip[2] = atoi(value);          // assign value to ip2 first ip octet:
//      }
//      if (!strcmp(name, "ip3")) {
//        ip[3] = atoi(value);          // assign value to ip4 first ip octet:
//      }
//    }
//  }
//}


// file in form
// <ip address>
// <MQTT Broker ip address> (mqttServerAddr)
// <MQTT Client Id>         (mqttClientId)
// <MQTT Port>
// <DEBUG Level>            (DEBUG_LEVEL)

//void GetNetworkSettingsFromFile(char* fileName) 
//{  
//  byte b = 0;
//  String settings[5];
//  if (SD.exists(fileName) == false)
//  {
//    Serial.println("File not found");
//    return;
//  }
//  File myFile = SD.open(fileName, FILE_READ);
//  if (!myFile)
//  {
//    Serial.println("Cannot open file");
//    return;
//  }
//  myFile.seek(0);
//  while (myFile.available())
//  {
//    settings = myFile.readStringUntil('\n');
//    b++;
//  }  
//  myFile.close();
//  Serial.print("my MAC: ");
//  Serial.println(settings[0]);
//  Serial.print("my IP: ");
//  Serial.println(settings[1]);
//  Serial.print("my MASK: ");
//  Serial.println(settings[2]);
//  Serial.print("my GATEWAY: ");
//  Serial.println(settings[3]);
//  Serial.print("my DNS: ");
//  Serial.println(settings[4]);
//}


#endif   /* SENSORLIGHTIOTMODULE_PIRCONFIG_H_ */

