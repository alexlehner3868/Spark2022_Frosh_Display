#include <FastLED.h>

#define NUM_LEDS 32

CRGB leds[NUM_LEDS];

// define variables used by the sequences
uint8_t hue = 0;                                       // starting hue
long randNum;

// Fixed definitions cannot change on the fly.
#define LED_DT 22
#define COLOR_ORDER GRB
#define BRIGHTNESS 255  
#define SATURATION 255

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
  
  // generate a random number
  Serial.begin(9600);
  randomSeed(analogRead(0));
  //randNum = random(2);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  randNum = random(3);
  if (randNum == 0) {
    // 0. colour change 
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(hue, 255, 255);
    }
    EVERY_N_MILLISECONDS(100){
      hue++;
    }
  } else if (randNum == 1){
    // 1. colour wave
    for (int j = 0; j < 255; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); 
      }
      FastLED.show();
      delay(25); // how fast the colours move
    }
  }else if(randNum == 2){
    // 2. Flashing Leds
    for(int i = 0; i < NUM_LEDS; i++){
      leds[i] = CRGB::LimeGreen;
      FastLED.show();
    }
    delay(1000);
    for(int i = 0; i < NUM_LEDS; i++){
      leds[0] = CRGB::Black;
      FastLED.show();
    }
  }
  FastLED.show();
}


