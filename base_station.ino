#include <SPI.h>
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
//#include "dataStructures.h"
#include "helper_rx.h"
#include "WifiConfiguration.h"
int P2_0=17,P2_1=18,P2_2=19,P1_0=29;
Enrf24 radio(P2_0, P2_1, P2_2);

WiFiClient client;

const uint8_t rxaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
char inbuf[33];

void setup() {
 Serial.begin(9600);
 initWifi();
 
 SPI.begin();
 SPI.setDataMode(SPI_MODE0);
 SPI.setBitOrder(MSBFIRST);
 
 radio.begin();  // Defaults 1Mbps, channel 0, max TX power
 //dump_radio_status_to_serialport(radio.radioState());
 radio.setRXaddress((void*)rxaddr);

 
 radio.enableRX();  // Start listening
 Serial.println("listening..");

}

node_Data document;
unsigned long lastTimestamp = 0;

int dataCount = 0;

void loop() {
  
  //dump_radio_status_to_serialport(radio.radioState());  // Should show Receive Mode
  while (client.available()) {
    char c = client.read();
    Serial.write(c);   
  }
  
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
      Serial.println("***********");
    //TODO : send the json to server    
     makePostRequest(string);
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
  }
  

    
    document.timestamp = 0;
   }  
}

void makeGetRequest(char *url){
  char request[50];
  sprintf(request,"GET %s HTTP/1.1",url);
   if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println(request);
    client.println("Host: apm-test.herokuapp.com");
    client.println("Connection: close");
    client.println();
  }
}

void makePostRequest(char * string){

  if (client.connect(server, 80)){
    Serial.println("connected to server for POST request");
    client.println("POST /dev HTTP/1.1");
    client.println("Host: apm-test.herokuapp.com");
    client.println("User-Agent: Energia/1.0"); 
    client.println("Content-Type: application/json");
    client.print("Content-Length:");
    client.println(strlen(string));
    client.println("Connection: close");
    client.println();
    client.println(string);
  }
}




