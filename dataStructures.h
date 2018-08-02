
typedef struct 
{
 byte header[1];
 byte message[10];
}packet;

typedef struct {
 byte red[2];
 byte green;
 byte blue;
} color_t;

struct rx_Bytes{
 char deviceID[4];   //4 byte
 unsigned long  timestamp; //4byte
 char fieldName[10]; //10 byte
 float fieldValue;

  rx_Bytes(){
  }
  
  rx_Bytes(char* inbuf){
  unsigned long point = (unsigned long) inbuf;

  memcpy(&deviceID, (void*) point, sizeof(deviceID));
  point += 4;
  memcpy(&timestamp, (void*) point, sizeof(timestamp));
  point += 4;
  memcpy(&fieldName, (void*) point, sizeof(fieldName));
  point += 10;
  memcpy(&fieldValue, (void*) point, sizeof(fieldValue));
  point += 4;
  

  
 
 
 };
 
};

const char fieldName[10][10] = {
 "____longt",
 "____lattd",
 "_____PM10",
 "____PM2.5",
 "______C02",
 "_____temp",
 "_humidity",
 "____ozone",
 "______JPT",
 "_____addr" 
 };

typedef struct{
 char deviceID[4];
 unsigned long  timestamp;  //4 byte
 char address[12];
 float data[10]; // always maintain the order as lon, lat, PM10, PM2_5, C02, temp, humidity, ozone, jpt;
}node_Data;

