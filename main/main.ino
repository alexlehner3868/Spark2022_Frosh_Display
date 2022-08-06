#include <FastLED.h>

// #define NUM_LEDS 32

// CRGB leds[NUM_LEDS];



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

/**********START OF GLOBAL VARIABLES******************/
uint8_t hue = 0; // starting hue
long randNum;
/**********END OF GLOBAL VARIABLES******************/


/**********START OF ANIMATION FUNCTION PROTOTYPES******************/
void colorRainbowChange();
void brightnessChange();
void lightBottomTop();
void lightLeftRightBone();
void lightLeftRightLED();
void colourRainbowWave();
void colourRainbowBone();
/**********END OF ANIMATION FUNCTION PROTOTYPES******************/


/**********START OF ANIMATION FUNCTION IMPLEMENTATIONS******************/
// change color for all bones and LEDs
void colorRainbowChange(){
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < num_leds[i]; j++){
      leds[i][j] = CHSV(hue, 255, 255);
    }
  }
  EVERY_N_MILLISECONDS(100){
    hue++;
  }
  FastLED.show();
}

// dim and light brightness for all bones and LEDs
// need to fix/change completely
void brightnessChange(){
  // set color
    for(int i = 0; i < 14; i++){
    for(int j = 0; j < num_leds[i]; j++){
      leds[i][j] = CRGB::LimeGreen;
    }
  }
  FastLED.show();
  delay(1000);
  //  fade all LEDs down by 100 in brightness each time this is called
  EVERY_N_MILLISECONDS(100){
    fadeToBlackBy(leds1, NUM_LEDS1, 100);
    fadeToBlackBy(leds2, NUM_LEDS2, 100);
    fadeToBlackBy(leds3, NUM_LEDS3, 100);
    fadeToBlackBy(leds4, NUM_LEDS4, 100);
    fadeToBlackBy(leds5, NUM_LEDS5, 100);
    fadeToBlackBy(leds6, NUM_LEDS6, 100);
    fadeToBlackBy(leds7, NUM_LEDS7, 100);
    fadeToBlackBy(leds8, NUM_LEDS8, 100);
    fadeToBlackBy(leds9, NUM_LEDS9, 100);
    fadeToBlackBy(leds10, NUM_LEDS10, 100);
    fadeToBlackBy(leds11, NUM_LEDS11, 100);
    fadeToBlackBy(leds12, NUM_LEDS12, 100);
    fadeToBlackBy(leds13, NUM_LEDS13, 100);
    fadeToBlackBy(leds14, NUM_LEDS14, 100);
  }
  FastLED.show();
  delay(1000);
}

// light up bottom to top, by LEDs
void lightBottomTop(){
  // legs lights up
  int i = 11;
  int j;
  for(j = num_leds[i] - 1; j >= 0; j--){
    while(i < 14){
      leds[i][j] = CRGB::LimeGreen; 
      FastLED.show();
      i++;
    }
    i = 10;
  }
  // head lights up
  i = 2;
  for(j = 0; j < num_leds[i]; j++){
    leds[i][j] = CRGB::LimeGreen;
    FastLED.show();
  }
  i = 0;
  for(int j = num_leds[i] - 1; j>= 0; j--){
    while(i <= 1){
      leds[i][j] = CRGB::LimeGreen;
      FastLED.show();
      i++;
    }
    i = 0;
  }
  // spine lights up 
  for(i = 3; i < 10; i++){
    for(j = num_leds[i] - 1; j >= 0; j--){
      leds[i][j] = CRGB::LimeGreen;
      FastLED.show();
    }
  }
}

// light up left to right, by bone
void lightLeftRightBone() {
  for (int k = 0; k < 14; k++){
    for (int i = 0; i < num_leds[k]; i++) {
      (leds[k])[i] = CRGB::LimeGreen;
    }
    delay(250);
    FastLED.show();
  }
}

// light up left to right, by LEDs
void lightLeftRightLED() {
  for (int k = 0; k < 14; k++){
    for (int i = num_leds[k] - 1; i >= 0; i--) {
      (leds[k])[i] = CRGB::LimeGreen;
      FastLED.show();
    }
  }
}

// rainbow wave 
void colourRainbowWave() {
  for (int j = 0; j < 255; j++) {
    for (int k = 0; k < 14; k++){
      for (int i = 0; i < num_leds[k]; i++) {
        (leds[k])[i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); 
      }
      FastLED.show();
    }
  }
}

// each bone different rainbow colour left to right
void colourRainbowBone() {
  for (int j = 0; j < 255; j++) {
    for (int k = 0; k < 14; k++){
      for (int i = 0; i < num_leds[k]; i++) {
        if (k == 0 || k == 2) {
          (leds[k])[i] = CRGB::MediumPurple;
        } else if (k == 1 || k == 3) {
          (leds[k])[i] = CRGB::Purple;
        } else if (k == 4) {
          (leds[k])[i] = CRGB::Red;
        } else if (k == 5 || k == 10 || k == 11) {
          (leds[k])[i] = CRGB::Orange;
        } else if (k == 6 || k == 12) {
          (leds[k])[i] = CRGB::Yellow;
        } else if (k == 7 || k == 13) {
          (leds[k])[i] = CRGB::GreenYellow;
        } else if (k == 8) {
          (leds[k])[i] = CRGB::CadetBlue;
        } else if (k == 9) {
          (leds[k])[i] = CRGB::SkyBlue;
        }
      }
      FastLED.show();
    }
  }
}

//flickers random leds on/off 
void flicker(CRGB colour){

  unsigned long start = millis();
  unsigned long last = millis();
  int strip = random(14); //pick random strip
  int position = random(num_leds[strip]);                           
  leds[strip][position] = colour;
  
  while(true){

    //every x millis, flicker another led off/on
    if (millis() - last > 10){
      strip = random(14);
      position = random(num_leds[strip]);  // Pick an LED at random.
      leds[strip][position] = colour;  
      last = millis();
    }

    //after a while, make the entire thing coloured so that animation doesn't take too long
    if (millis() - start > 2000){

      for (int i = 0; i < 14; i++){
        for (int k = 0; k < num_leds[i]; k++){
          leds[i][k] = colour;
        }
      }
      FastLED.show();  
      break;
    }
     FastLED.show();  
  }
}

/**********END OF ANIMATION FUNCTION IMPLEMENTATIONS******************/


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
  
  // 0. colour change 
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255);
  }
  EVERY_N_MILLISECONDS(100){
    hue++;
  }
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
  
  FastLED.show();
}
 */
bool clap = false; // This is the signal frm the other team 
int state = 0;
unsigned long time_since_last_clap = 0;
int opposite_animation = -1; //-1 = false, 1 = true
#define NUM_ANIMATIONS 8 // The number of animations we have programmed   

void loop(){
  if(clap){
    time_since_last_clap = millis();
    state = random(NUM_ANIMATIONS);

    clap = false;
  }
 
    switch(state){
      case 0:
        colorRainbowChange();  
        break;
      case 1:
        brightnessChange();
        break;
      case 2:
        lightBottomTop();
        break;
      case 3:
        lightLeftRightBone();
        break;
      case 4:
        lightLeftRightLED();
        break;
      case 5:
        colourRainbowWave();
        break;
      case 6:
        colourRainbowBone();
        break;
      case 7:
        if (opposite_animation == 1)
          flicker(CRGB::Black);
        else
          flicker(CRGB::White);
        opposite_animation *= -1;
        break;
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
