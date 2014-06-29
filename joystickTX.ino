/* JoyStick module transceiver code
By Nazmus
http://www.Easyprogramming.net
http://nazm.us
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   - 
   Analog Joystick module
   GND to Arduino GND
   VCC to Arduino +5V
   X Pot to Arduino A0
   Y Pot to Arduino A1

/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe


/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int joystick[6];  // 6 element array holding Joystick reading and 4 buttons

int upbut = 2;
int rightbut = 3;
int downbut = 4;
int leftbut = 5;
void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  
  //declare pinMode for all buttons and initial state
  pinMode(upbut,INPUT);
  digitalWrite(upbut,LOW);
  pinMode(rightbut,INPUT);
  digitalWrite(upbut,LOW);
   pinMode(downbut,INPUT);
  digitalWrite(downbut,LOW);
  pinMode(leftbut,INPUT);
  digitalWrite(leftbut,LOW);
  //end pinMode and digitalWrite
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  joystick[0] = analogRead(JOYSTICK_X);
  joystick[1] = analogRead(JOYSTICK_Y);
  joystick[2] = digitalRead(upbut);
  joystick[3] = digitalRead(rightbut);
  joystick[4] = digitalRead(downbut);
  joystick[5] = digitalRead(leftbut);
  
  radio.write( joystick, sizeof(joystick) );

    // Debugging code below
      Serial.print("X = ");
      
      Serial.print(analogRead(JOYSTICK_X));
      Serial.print(" Y = ");  
      
      Serial.print(analogRead(JOYSTICK_Y));
        Serial.print(" Y = ");  
      Serial.print(" Up = "); 
      Serial.print(digitalRead(upbut));
      Serial.print(" Right = "); 
      Serial.print(digitalRead(rightbut));
      Serial.print(" Down = "); 
      Serial.print(digitalRead(downbut));
      Serial.print(" Left = "); 
      Serial.println(digitalRead(leftbut));
      
      // Debugging code above  
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/

//NONE
//*********( THE END )***********
