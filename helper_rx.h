
#include <ArduinoJson.h>
#include "dataStructures.h"

void dump_radio_status_to_serialport(uint8_t status)
{
 Serial.print("Enrf24 radio transceiver status: ");
 switch (status) {
   case ENRF24_STATE_NOTPRESENT:
     Serial.println("NO TRANSCEIVER PRESENT");
     break;

   case ENRF24_STATE_DEEPSLEEP:
     Serial.println("DEEP SLEEP <1uA power consumption");
     break;

   case ENRF24_STATE_IDLE:
     Serial.println("IDLE module powered up w/ oscillators running");
     break;

   case ENRF24_STATE_PTX:
     Serial.println("Actively Transmitting");
     break;

   case ENRF24_STATE_PRX:
     Serial.println("Receive Mode");
     break;

   default:
     Serial.println("UNKNOWN STATUS CODE");
 }
}


//void (char* json, node_data document){
//  
//}
char *createJSONMessage(node_Data document) {
  DynamicJsonBuffer  jsonBuffer(200);
  JsonObject& root = jsonBuffer.createObject();
  root["deviceID"] = document.deviceID;
  root["timestamp"] = document.timestamp;
  for(int i=0;i<6;i++){
    root[jsonfieldName[i]] = document.data[i];
  }
  String output;
  root.printTo(output);
  char* string;
   string = &output[0];
  
  return string;
  
}
