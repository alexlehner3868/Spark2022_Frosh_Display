#include <FastLED.h>

#define NUM_LEDS 32

CRGB leds[NUM_LEDS];

// define variables used by the sequences
uint8_t hue = 0;                                       // starting hue


void setup() {
  // put your setup code here, to run once:
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
  
  
  // 1. colour change 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255);
  }
  EVERY_N_MILLISECONDS(100){
    hue++;
  }

  
  FastLED.show();
  
  
}
