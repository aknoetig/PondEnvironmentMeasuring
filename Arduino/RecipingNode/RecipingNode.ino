#include <SoftwareSerial.h>
#include <XBee.h>

SoftwareSerial mySerial(10, 11);

XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();


typedef union FloatBytesUnion{
  
  float f;
  byte bytes[4];
  
};

void setup() {
  xbee.begin(9600);
  
  mySerial.begin(9600);
  
}

void loop() {
  
  xbee.readPacket();
  
  if(xbee.getResponse().isAvailable())
  {
    // Got something
    if(xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
    {
      xbee.getResponse().getZBRxResponse(rx);

      processPayload(rx.getData(), rx.getDataLength());     
    }
  }
}

void processPayload(uint8_t payload[], int size)
{
  mySerial.print("Received Payload: ");
  mySerial.print(size);
  mySerial.println(" Byte");
  
  if(payload[0] == 'P')
  {
    processPondResponse(payload);
  }
  
  if(payload[0] == 'W')
  {
    processWeatherResponse(payload);
  }
    
}

void processPondResponse(uint8_t payload[])
{
  FloatBytesUnion temp;
  
  temp.bytes[0] = payload[1];
  temp.bytes[1] = payload[2];
  temp.bytes[2] = payload[3];
  temp.bytes[3] = payload[4];
  
  mySerial.print("Pond Node Response: ");
  mySerial.print(temp.f);
  mySerial.println(" Degree Celsius");
  
  
}

void processWeatherResponse(uint8_t payload[])
{
  FloatBytesUnion temp;
  FloatBytesUnion light;
  
  
  temp.bytes[0] = payload[1];
  temp.bytes[1] = payload[2];
  temp.bytes[2] = payload[3];
  temp.bytes[3] = payload[4];
  
  
  light.bytes[0] = payload[5];
  light.bytes[1] = payload[6];
  light.bytes[2] = payload[7];
  light.bytes[3] = payload[8];
  
  mySerial.print("Weather Node Response: ");
  mySerial.print(temp.f);
  mySerial.print(" Degree Celsius, ");
  mySerial.print(light.f);
  mySerial.println(" Lux");
}
