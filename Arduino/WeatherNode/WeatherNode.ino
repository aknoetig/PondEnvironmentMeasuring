#include <XBee.h>
#include <SoftwareSerial.h>

// create the XBee object
XBee xbee = XBee();

uint8_t payload[9] = {0 , 0 , 0 , 0 , 0, 0, 0, 0, 0};

// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x403dcf79);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int statusLed = 13;
int errorLed = 13;

int tempPin = 0; 
float tempv;

int photocellPin = 1;     
float lightv;
float lightr;
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
  FloatBytesUnion light;
  
  /******Calculating Values**********/
  
  /**** Temperature *****/
  //Voltage 
  tempv = get_Voltage(tempPin); 
  //Temperature
  temp.f = get_Temp(tempv);
  
  /**** Light *****/
  //Voltage
  lightv = get_Voltage(photocellPin); 
  // Light
  lightr = get_Lightr(lightv);
  light.f = get_Light(lightv);
  
  // convert temperature and light into a byte array and copy it into the payload array
  
  payload[0] = 0x57;
  payload[1] = temp.bytes[0];
  payload[2] = temp.bytes[1];
  payload[3] = temp.bytes[2];
  payload[4] = temp.bytes[3];
  
  payload[5] = light.bytes[0];
  payload[6] = light.bytes[1];
  payload[7] = light.bytes[2];
  payload[8] = light.bytes[3];

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

float get_Light(float lightv){
  
  if( lightv == 0.0 ){
    return -1.0;
  }
  
  float lightr = get_Lightr(lightv);  
      //Lux
  return 10.0 * pow( 14000.0 / lightr, 1 / 0.7 );
  
};

float get_Lightr(float lightv){
  return ( ( 5.0 - lightv ) / lightv ) * 10000.0;
};


float get_Temp_err(){
  return quant_err * 100.0 + 1.0;
};

float get_Light_err(float lightv, float lightr, float light){
  //Measurement Error for volatge supply 
  // estimated with 1% = 50mV  
  float delta_lightr = 10000.0 / lightv * 0.005 + 5.0 * 10000.0 * quant_err / (lightv*lightv) + 5.0 * 500.0 / lightv; 
  float delta_light_rel = 30.0 / 49.0 + 10.0 / 7.0 * delta_lightr / lightr + abs(log(lightr / 14000.0)) * 0.1 / (0.7 * 0.7) ;
  return delta_light_rel * light;
};

