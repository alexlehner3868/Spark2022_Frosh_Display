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
 
/* void loop() {
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
 */
bool clap = false; // This is the signal frm the other team 
int state = 0;
bool currently_animating = false;
bool opposite_animation = false;
unsigned long time_since_last_clap = 0;
#define NUM_ANIMATIONS 3 // The number of animations we have programmed   

void loop(){
  if(clap){
    time_since_last_clap = millis();
    state = random(NUM_ANIMATIONS);
    clap = false;
    currently_animating = true;
  }
  if(currently_animating && opposite_animation){
    switch(state){
      case 0:
        //flicker off
        break;
      default:
        break;
    }
    currently_animating = false;
    opposite_animation = false;
  }

  if(currently_animating){
   switch(state){
    case 0 :
      //flicker on 
      opposite_animation = true;
      break; 
    default :
      break;
   }
   currently_animating = false;
  }
  
  // Turn off LEDS if its been 10 minutes 
  if(millis() - time_since_last_clap > 600000){
    // DISABLE ALL LIGHTS 
    // Loop through all sementes
      //Loop through all LEDS in segments 
        //Turn off
  }

}