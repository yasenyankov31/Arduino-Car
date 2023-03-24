#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"
#include <Servo.h>


#define PHASE_PIN 2
#define SPPED_PIN A2
#define SERVO_PIN 6

RF24 radio(9,10); // NRF24L01 SPI pins. Pin 9 and 10 on the Nano

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 



struct Controller_Values {
  int x;
  int y;
  int b;
};
Controller_Values valStruct;
Servo servo;

void setup(void)
{
  servo.attach(SERVO_PIN);
  
  radio.begin(); // Start the NRF24L01
  
  radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive
  
  radio.startListening(); // Listen to see if information received
  
  pinMode(PHASE_PIN, OUTPUT); 
}

void loop(void)
{
  while (radio.available())
  {
    radio.read(&valStruct, sizeof(Controller_Values)); // Read information from the NRF24L01

    servo.write(valStruct.x);
    if (valStruct.y > 0) // Indicates switch is pressed
    {
      digitalWrite(PHASE_PIN, HIGH);
      analogWrite(SPPED_PIN,valStruct.y);
    }
    else
    {
       digitalWrite(PHASE_PIN, LOW);
       analogWrite(SPPED_PIN,-valStruct.y);
    }
    
   }
}