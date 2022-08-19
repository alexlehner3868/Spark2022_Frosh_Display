#include <FastLED.h>

// #define NUM_LEDS 32

// CRGB leds[NUM_LEDS];

// Fixed definitions cannot change on the fly.
#define LED_DT 22
#define COLOR_ORDER GRB
#define BRIGHTNESS 255  
#define SATURATION 255

//number of leds in each strip
#define NUM_LEDS1 12
#define NUM_LEDS2 18
#define NUM_LEDS3 22
#define NUM_LEDS4 21
#define NUM_LEDS5 9
#define NUM_LEDS6 9
#define NUM_LEDS7 9
#define NUM_LEDS8 20
#define NUM_LEDS9 20
#define NUM_LEDS10 20
#define NUM_LEDS11 20

#define TOTAL_LEDS 137

#define NUM_SEGMENTS 11

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

//array that stores all the segments
struct CRGB* leds[NUM_SEGMENTS];

//array that contains the num of leds for each strip
int num_leds[NUM_SEGMENTS];

// Variables to control state
bool clap = false; // This is the signal frm the other team 
int state = 0;
unsigned long time_since_last_clap = 0;
int opposite_animation = -1; //-1 = false, 1 = true
#define NUM_ANIMATIONS 9 // The number of animations we have programmed   


/**********START OF GLOBAL VARIABLES******************/
uint8_t hue = 0; // starting hue
long randNum;
uint32_t colour[] = {CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::SkyBlue, CRGB::MediumPurple};
uint8_t chsvColour[] = {1, 39, 60, 120, 197, 291};
uint32_t rainbowColour;
/**********END OF GLOBAL VARIABLES******************/


/**********START OF ANIMATION FUNCTION PROTOTYPES******************/
void colorRainbowChange();
void gradualColorRainbowChange();
void brightnessChange();
void lightBottomTop();
void lightLeftRightBone();
void lightLeftRightLED();
void colourRainbowWave();
void colourRainbowBone();
/**********END OF ANIMATION FUNCTION PROTOTYPES******************/

/**********START OF ANIMATION FUNCTION IMPLEMENTATIONS******************/
// change color for all bones and LEDs with preselected RGB colors
void colorRainbowChange(){
  for(int k = 0; k < 6; k++){
    for(int i = 0; i < NUM_SEGMENTS; i++){
      for(int j = 0; j < num_leds[i]; j++){
        leds[i][j] = colour[k];
      }
    }      
    FastLED.show();
    delay(1000);
  }
}

// change color for all bones and LEDs smoothly
void gradualColorRainbowChange(){
  for(hue; hue < 255 ; hue++ ){
    for(int i = 0; i < NUM_SEGMENTS; i++){
      for(int j = 0; j < num_leds[i]; j++){
        leds[i][j] = CHSV(hue, 255, 255);
      }
    } 
    delay(50);
    FastLED.show();
  }
  hue = 0;
}

// dim for all bones and LEDs
void brightnessChange(){
  //set colour
  rainbowColour = random(chsvColour);
  for(int i = 0; i < NUM_SEGMENTS; i++){
    for(int j = 0; j < num_leds[i]; j++){
      leds[i][j] = CHSV(rainbowColour, SATURATION, BRIGHTNESS);
    }
  }
  FastLED.show();
  delay(2000); //waits for 2 second

  //starts fade effect by reducing brightness of the pixel
  for(int k = 255; k >= 0; k--){
    for(int i = 0; i < NUM_SEGMENTS; i++){
      for(int j = 0; j < num_leds[i]; j++){
        leds[i][j] = CHSV(rainbowColour, SATURATION, k);
      }
    } FastLED.show();
  }
  delay(1000); //waits for a second
}

// light up bottom to top, by LEDs
void lightBottomTop(){
  rainbowColour = colour[random(6)];
  // legs lights up
  int i = 11;
  int j;
  for(j = num_leds[i] - 1; j >= 0; j--){
    while(i < NUM_SEGMENTS){
      leds[i][j] = rainbowColour; 
      FastLED.show();
      i++;
    }
    i = 10;
  }
  // head lights up
  i = 2;
  for(j = 0; j < num_leds[i]; j++){
    leds[i][j] = rainbowColour;
    FastLED.show();
  }
  i = 0;
  for(int j = num_leds[i] - 1; j>= 0; j--){
    while(i <= 1){
      leds[i][j] = rainbowColour;
      FastLED.show();
      i++;
    }
    i = 0;
  }
  // spine lights up 
  for(i = 3; i < 10; i++){
    for(j = num_leds[i] - 1; j >= 0; j--){
      leds[i][j] = rainbowColour;
      FastLED.show();
    }
  }
}

// light up left to right, by bone
void lightLeftRightBone() {
  rainbowColour = colour[random(6)];
  for (int k = 0; k < NUM_SEGMENTS; k++){
    for (int i = 0; i < num_leds[k]; i++) {
      (leds[k])[i] = rainbowColour;
    }
    delay(250);
    FastLED.show();
  }
}

// light up left to right, by LEDs
void lightLeftRightLED() {
  rainbowColour = colour[random(6)];
  for (int k = 0; k < NUM_SEGMENTS; k++){
    for (int i = num_leds[k] - 1; i >= 0; i--) {
      (leds[k])[i] = rainbowColour;
      FastLED.show();
    }
  }
}

// rainbow wave 
void colourRainbowWave() {
  for (int j = 0; j < 255; j++) {
    for (int k = 0; k < NUM_SEGMENTS; k++){
      for (int i = 0; i < num_leds[k]; i++) {
        (leds[k])[i] = CHSV(i - (j * 4), SATURATION, BRIGHTNESS); 
      }
      FastLED.show();
    }
  }
}

// each bone different rainbow colour left to right
void colourRainbowBone() {
  for (int j = 0; j < 255; j++) {
    for (int k = 0; k < NUM_SEGMENTS; k++){
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

// Flashes bones on randomly
void flash_bones(){
  unsigned long start = millis();
  while(millis() - start < 5000){
    random_color = colour[random(6)];
    int random_bone = random(14);
    for(int i = 0; i < num_leds[random_bone]; i++){
      (leds[random_bone])[i] = random_color;
      FastLED.show();
    }
    delay(300);
    for(int i = 0; i < num_leds[random_bone]; i++){
      (leds[random_bone])[i] = CRGB::Black;
    }

  }
}

//flickers random leds on/off 
void flicker(CRGB colour){

  unsigned long start = millis();
  unsigned long last = millis();
  int strip = random(NUM_SEGMENTS); //pick random strip
  int position = random(num_leds[strip]);                           
  leds[strip][position] = colour;
  
  while(true){

    //every x millis, flicker another led off/on
    if (millis() - last > 10){
      strip = random(NUM_SEGMENTS);
      position = random(num_leds[strip]);  // Pick an LED at random.
      leds[strip][position] = colour;  
      last = millis();
    }

    //after a while, make the entire thing coloured so that animation doesn't take too long
    if (millis() - start > 2000){

      for (int i = 0; i < NUM_SEGMENTS; i++){
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

  
  // generate a random number
  Serial.begin(9600);
  randomSeed(analogRead(0));
  //randNum = random(2);
}
 
void loop(){
  if(clap){
    time_since_last_clap = millis();
    state = random(NUM_ANIMATIONS);

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
        flicker(CRGB::White);
        break;
      case 8:
        flash_bones();
      case 9:
        gradualColorRainbowChange();
      default:
        break;
    };
    clap = false;
  }
  // Keep the lights on for 4 seconds before disabling (unless a clap happends first)
  if(time_since_last_clap - millis() > 4000){
    for (int i = 0; i < NUM_SEGMENTS; i++){
      for (int k = 0; k < num_leds[i]; k++){
        leds[i][k] = CRGB::Black;
      }
    }
  }
  FastLED.show();

}