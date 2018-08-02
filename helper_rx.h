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


void (char* json, node_data document){
  
}

