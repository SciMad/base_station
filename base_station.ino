#include <SPI.h>
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
//#include "dataStructures.h"
#include "helper_rx.h"

int P2_0=17,P2_1=18,P2_2=19,P1_0=29;
Enrf24 radio(P2_0, P2_1, P2_2);

const uint8_t rxaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
char inbuf[33];

void setup() {
 Serial.begin(9600);
 SPI.begin();
 SPI.setDataMode(SPI_MODE0);
 SPI.setBitOrder(MSBFIRST);
 
 radio.begin();  // Defaults 1Mbps, channel 0, max TX power
 //dump_radio_status_to_serialport(radio.radioState());
 radio.setRXaddress((void*)rxaddr);
 
 pinMode(P1_0, OUTPUT);
 digitalWrite(P1_0, LOW);
 
 radio.enableRX();  // Start listening
 Serial.println("listening..");
}

node_Data document;
unsigned long lastTimestamp = 0;

int dataCount = 0;

void loop() {
  
  //dump_radio_status_to_serialport(radio.radioState());  // Should show Receive Mode
  while (!radio.available(true));
  radio.read(inbuf);

  rx_Bytes message;
  message = (rx_Bytes) inbuf;
  
   if (dataCount == 0 && ((unsigned long) message.timestamp != lastTimestamp)){
     strcpy(document.deviceID,(char*) message.deviceID);
     document.timestamp = (unsigned long)message.timestamp;
     lastTimestamp = document.timestamp;
   }

   if (document.timestamp != 0){
   for(int i = 0; i<10;i++){
    if ((unsigned long) message.timestamp == document.timestamp){       //to collect all 10 data only if all 10 data have the same timestamp
      if(!strcmp(fieldName[i],(char*)message.fieldName)){
      document.data[i] = (float)message.fieldValue;
      dataCount++;
      }
    }else{
      dataCount = 0;
    }
   }
   }
   
   if(dataCount == 10){
    dataCount = 0;
   // Serial.println("======================");
    //Serial.println(document.deviceID);
   // Serial.println(document.timestamp);
    for(int i = 0; i<10;i++){
      Serial.println(document.data[i]);
    }
    //TODO: jsonize the document
    char* string = createJSONMessage(document);  
    Serial.println(string);
    //TODO : send the json to server   
    



    
    document.timestamp = 0;
   }

   

   

   
}



