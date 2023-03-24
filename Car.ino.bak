#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"


#define  SwitchPin 2
#define  InputX A4
#define  InputY A3

 
RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


struct Controller_Values {
  int x;
  int y;
  int b;
};
Controller_Values valStruct;
void setup()
{

  pinMode(SwitchPin, INPUT_PULLUP); 
  digitalWrite(SwitchPin,HIGH); 
  
  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop()
{

  valStruct.x=map(analogRead(InputX), 0, 1023, 180, 100);
  valStruct.y=map(analogRead(InputY), 0, 1023, -255, 255);
  valStruct.b=digitalRead(SwitchPin);
  
  radio.write(&valStruct, sizeof(Controller_Values));

}