// GSM-GPRS_GPS-BT_SHIELD SIM808 V2.2.9.1 DESIGNED BY UNV 2017.03 & Arduino UNO
// SIM808 pinnout (VCC)(TXD)(GND)(RXD)(GND)
// connect VCC+GND to external power 12V/1A or 5V/2A
// connect GND to ground on Arduino
// connect SIM808 RX to digital 11 on Arduino
// connect SIM808 TX to digital 10 on Arduino

#include <SoftwareSerial.h>

#define DEBUG true
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
  
  Serial.println("Starting...");
      
  delay(3000);
   
   
}


//run continuously
void loop() 
{
   power_on();
     
  while(1)
  {
    sendATcommand("AT+CGPSINF=0",1000,DEBUG);
    delay(1000);
  }  


  
}

void power_on()
{

    sendATcommand("AT+CGPSPWR=1", 1000, DEBUG);
    sendATcommand("AT+CGPSRST=0", 2000, DEBUG);
    
    // waits for fix GPS
//    while( (sendATcommand("AT+CGPSSTATUS?", "2D Fix", 5000) || 
//            sendATcommand("AT+CGPSSTATUS?", "3D Fix", 5000)) == 0 );
    
}


String sendATcommand(String ATcommand, const int timeout, boolean debug)
{

    String answer = "";
    mySerial.println(ATcommand);
    long int time = millis();
    while((time+timeout)>millis())
    {
      while(mySerial.available())
      {
        char c = mySerial.read();
        answer+=c;
      }  
    }
    if(debug)
    {
      Serial.println(answer);
    
    }    
    
    return answer;
}

