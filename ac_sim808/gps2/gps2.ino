// GSM-GPRS_GPS-BT_SHIELD SIM808 V2.2.9.1 DESIGNED BY UNV 2017.03 & Arduino UNO
// SIM808 pinnout (VCC)(TXD)(GND)(RXD)(GND)
// connect VCC+GND to external power 12V/1A or 5V/2A
// connect GND to ground on Arduino
// connect SIM808 RX to digital 11 on Arduino
// connect SIM808 TX to digital 10 on Arduino

#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

// set up a software serial port
SoftwareSerial mySerial = SoftwareSerial (rxPin, txPin);

// run once
void setup() 
{
  // initialize hardware serial communication, baud rate 9600
  Serial.begin(9600);
  // define pin modes for software serial port
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // initialize software serial communication, baud rate 9600
  mySerial.begin(9600);
}


//run continuously
void loop() 
{
  if (mySerial.available())
    Serial.write(mySerial.read());
     
  if (Serial.available())
  {
     while(Serial.available())
    {
       mySerial.write(Serial.read());
    }   
    mySerial.println();
  }  


  
}
