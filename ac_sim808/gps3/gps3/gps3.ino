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
  
  Serial.println("Starting...");
  power_on();
    
  delay(3000);
   
  sendATcommand("AT+CGPSPWR=1", "OK", 2000);
  sendATcommand("AT+CGPSRST=0", "OK", 2000);
    
  // waits for fix GPS
  while( (sendATcommand("AT+CGPSSTATUS?", "2D Fix", 5000) || 
            sendATcommand("AT+CGPSSTATUS?", "3D Fix", 5000)) == 0 );
  
  
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

void power_on(){

    uint8_t answer=0;
    
    // checks if the module is started
    answer = sendATcommand("AT", "OK", 2000);
    if (answer == 0)
    {
        // power on pulse
//        digitalWrite(onModulePin,HIGH);
//        delay(3000);
//        digitalWrite(onModulePin,LOW);
    
        // waits for an answer from the module
        while(answer == 0){    
            // Send AT every two seconds and wait for the answer
            answer = sendATcommand("AT", "OK", 2000);    
        }
    }
    
}


int8_t sendATcommand(char* ATcommand, char* expected_answer1,
        unsigned int timeout)
{

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string
    
    delay(100);
    
    // Clean the input buffer
    while( Serial.available() > 0) Serial.read();    
    
    Serial.println(ATcommand);    // Send the AT command 


    x = 0;
    previous = millis();

    // this loop waits for the answer
    do{

        if(Serial.available() != 0){    
            response[x] = Serial.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer1) != NULL)    
            {
                answer = 1;
            }
        }
        // Waits for the asnwer with time out
    }while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}

