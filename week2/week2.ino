#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs = CapacitiveSensor(0,2);
const int numPins = 3;
int ledPins[numPins] = {1, 4, 3};

void setup()                    
{
   cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example

   // set pin mode for LEDs
   for (int i = 0; i < numPins; i += 1) {
    pinMode(ledPins[i], OUTPUT);
   }
   
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total =  cs.capacitiveSensor(30);

    int numTurnOn = 0;
    if (1000 <= total && total < 10000) {
      numTurnOn = 1;
    } else if (10000 <= total && total < 100000) {
      numTurnOn = 2;
    } else if (100000 <= total) {
      numTurnOn = 3;
    }

    for (int i = 0; i < numPins; i += 1) {
      if (i < numTurnOn) {
        digitalWrite(ledPins[i], HIGH);
      } else {
        digitalWrite(ledPins[i], LOW);
      }
    }
    
    Serial.print(total);                  // print sensor output 1
    Serial.print("\t");
    Serial.println(numTurnOn);

    delay(10);                             // arbitrary delay to limit data to serial port 
}
