#include <Arduino.h>
#include <core_pins.h>
#include <kinetis.h>

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  GPIOC_PSOR = (1<<5); // set Pin 13 to on
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
}