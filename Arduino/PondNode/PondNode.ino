#include <XBee.h>
#include <SoftwareSerial.h>

// create the XBee object
XBee xbee = XBee();

uint8_t payload[5] = { 0, 0, 0, 0, 0};

// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x403dcf79);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int statusLed = 13;
int errorLed = 13;

int tempPin = 0; 
float tempv;
float quant_err = 5.0 / 1024.0;


typedef union FloatBytesUnion{

  float f;
  byte bytes[4];

};

void setup() {

  xbee.begin(9600);
}

void loop() {   
  
  FloatBytesUnion temp;
  
  /******Calculating Values**********/
  
  /**** Temperature *****/
  //Voltage 
  tempv = get_Voltage(tempPin); 
  //Temperature
  temp.f = get_Temp(tempv);
  
  // convert temperature and light into a byte array and copy it into the payload array
  
  payload[0] = 0x50;
  payload[1] = temp.bytes[0];
  payload[2] = temp.bytes[1];
  payload[3] = temp.bytes[2];
  payload[4] = temp.bytes[3];

  xbee.send(zbTx);

  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(500)) {
    // got a response!

    // should be a znet tx status            	
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
    }
  } else if (xbee.getResponse().isError()) {
    //nss.print("Error reading packet.  Error code: ");  
    //nss.println(xbee.getResponse().getErrorCode());

  delay(1000);
}
}

float get_Voltage(int PIN){
  
  int reading = analogRead(PIN);
  reading = analogRead(PIN);
  return (reading * 5.0) / 1024.0;

};

float get_Temp(float tempv){
  
  return (tempv - 0.5) * 100.0;
  
};

float get_Temp_err(){
  return quant_err * 100.0 + 1.0;
};



