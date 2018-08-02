
#include <aJSON.h>
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

  aJsonObject* root = aJson.createObject();
  aJson.addItemToObject(root, "deviceID", aJson.createItem(
  document.deviceID));
  aJsonObject* fmt = aJson.createObject();
    aJson.addNumberToObject(root, "TimeStamp", (double)document.timestamp);
    aJson.addItemToObject(root, "location", fmt);
    //aJson.addStringToObject(fmt, "name", "bhaktapur");
    aJson.addNumberToObject(fmt, "longitude", document.data[0]);
    aJson.addNumberToObject(fmt, "Latitude", document.data[1]);

    for(int i= 2;i<10;i++){
      aJson.addNumberToObject(root, jsonfieldName[i],document.data[i]);
    }
   char* string = aJson.print(root);
    return string;
}
