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

//number of leds in each strip
#define NUM_LEDS1 5
#define NUM_LEDS2 5
#define NUM_LEDS3 7
#define NUM_LEDS4 5
#define NUM_LEDS5 8
#define NUM_LEDS6 9
#define NUM_LEDS7 12
#define NUM_LEDS8 10
#define NUM_LEDS9 10
#define NUM_LEDS10 12
#define NUM_LEDS11 12
#define NUM_LEDS12 14
#define NUM_LEDS13 14
#define NUM_LEDS14 14

#define TOTAL_LEDS 137

//creating CRGB led arrays
struct CRGB leds1[NUM_LEDS1];
struct CRGB leds2[NUM_LEDS2]; 
struct CRGB leds3[NUM_LEDS3];
struct CRGB leds4[NUM_LEDS4]; 
struct CRGB leds5[NUM_LEDS5]; 
struct CRGB leds6[NUM_LEDS6]; 
struct CRGB leds7[NUM_LEDS7];
struct CRGB leds8[NUM_LEDS8];
struct CRGB leds9[NUM_LEDS9]; 
struct CRGB leds10[NUM_LEDS10];
struct CRGB leds11[NUM_LEDS11]; 
struct CRGB leds12[NUM_LEDS12]; 
struct CRGB leds13[NUM_LEDS13]; 
struct CRGB leds14[NUM_LEDS14]; 

//array that stores all the segments
struct CRGB* leds[14];

//array that contains the num of leds for each strip
int num_leds[14];

void setup() {
  // put your setup code here, to run once:

  //connecting the led arrays to the strips + their digital pin
  LEDS.addLeds<WS2812B, 10, COLOR_ORDER>(leds1, NUM_LEDS1);  // Use this for WS2801 or APA102
  LEDS.addLeds<WS2812B, 11, COLOR_ORDER>(leds2, NUM_LEDS2);
  LEDS.addLeds<WS2812B, 12, COLOR_ORDER>(leds3, NUM_LEDS3);
  LEDS.addLeds<WS2812B, 13, COLOR_ORDER>(leds4, NUM_LEDS4);
  LEDS.addLeds<WS2812B, 14, COLOR_ORDER>(leds5, NUM_LEDS5);
  LEDS.addLeds<WS2812B, 15, COLOR_ORDER>(leds6, NUM_LEDS6);
  LEDS.addLeds<WS2812B, 16, COLOR_ORDER>(leds7, NUM_LEDS7);
  LEDS.addLeds<WS2812B, 17, COLOR_ORDER>(leds8, NUM_LEDS8);  // Use this for WS2801 or APA102
  LEDS.addLeds<WS2812B, 18, COLOR_ORDER>(leds9, NUM_LEDS9);
  LEDS.addLeds<WS2812B, 19, COLOR_ORDER>(leds10, NUM_LEDS10);
  LEDS.addLeds<WS2812B, 20, COLOR_ORDER>(leds11, NUM_LEDS11);
  LEDS.addLeds<WS2812B, 21, COLOR_ORDER>(leds12, NUM_LEDS12);
  LEDS.addLeds<WS2812B, 22, COLOR_ORDER>(leds13, NUM_LEDS13);
  LEDS.addLeds<WS2812B, 23, COLOR_ORDER>(leds14, NUM_LEDS14);  

  //setting up segment array
  leds[0] = leds1;
  leds[1] = leds2;
  leds[2] = leds3;
  leds[3] = leds4;
  leds[4] = leds5;
  leds[5] = leds6;
  leds[6] = leds7;  
  leds[7] = leds8;
  leds[8] = leds9;
  leds[9] = leds10;
  leds[10] =leds11;
  leds[11] = leds12;
  leds[12] = leds13;
  leds[13] = leds14;

  //setting up num of leds per strip array
  num_leds[0] = NUM_LEDS1;
  num_leds[1] = NUM_LEDS2;
  num_leds[2] = NUM_LEDS3;
  num_leds[3] = NUM_LEDS4;
  num_leds[4] = NUM_LEDS5;
  num_leds[5] = NUM_LEDS6;
  num_leds[6] = NUM_LEDS7;  
  num_leds[7] = NUM_LEDS8;
  num_leds[8] = NUM_LEDS9;
  num_leds[9] = NUM_LEDS10;
  num_leds[10] = NUM_LEDS11;
  num_leds[11] = NUM_LEDS12;
  num_leds[12] = NUM_LEDS13;
  num_leds[13] = NUM_LEDS14;

  
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
bool opposite_animation = false;
unsigned long time_since_last_clap = 0;
#define NUM_ANIMATIONS 3 // The number of animations we have programmed   

void loop(){
  if(clap){
    time_since_last_clap = millis();
    state = random(NUM_ANIMATIONS);
      // hard code the opposite states in 
    if(opposite_animation){
      // Flicker on -> flicker off
      if(state == 0){
        state =1;
      }
    }
    clap = false;
  }
 
    switch(state){
      case 0:
        //flicker on
        opposite_animation = true; 
        break;
      case 1: 
        //flicker off
        opposite_animation = false
      default:
        break;
    };
  

  // Turn off LEDS if its been 10 minutes 
  if(millis() - time_since_last_clap > 600000){
    // DISABLE ALL LIGHTS 
    // Loop through all sementes
      //Loop through all LEDS in segments 
        //Turn off
  }

}
