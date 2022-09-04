#include <Arduino.h>
#include <FastLED.h>
#define DEBUG
// #undef DEBUG


#define COLOR_ORDER GRB

// number of leds in each strip
#define NUM_LEDS1 11
#define NUM_LEDS2 17
#define NUM_LEDS3 21
#define NUM_LEDS4 19
#define NUM_LEDS5 9
#define NUM_LEDS6 9
#define NUM_LEDS7 9
//TODO: this is legs 
#define NUM_LEDS8 7
#define NUM_LEDS9 7
#define NUM_LEDS10 7
#define NUM_LEDS11 7

#define TOTAL_LEDS 122

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
int l2r[13]; // left to right
int cp[NUM_SEGMENTS];

//array that contains the num of leds for each strip
int num_leds[NUM_SEGMENTS];
int l2r_num_leds[13]; // left to right

/**********START OF GLOBAL VARIABLES******************/
int BRIGHTNESS = 255; 
int SATURATION = 255;
uint8_t hue = 0; // starting hue
long randNum;
uint32_t colour[] = {CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::SkyBlue, CRGB::MediumPurple};
uint8_t chsvColour[] = {1, 39, 60, 120, 197, 255};
uint32_t rainbowColour;
int threshold = 25;

// Variables to control state
bool clap = false; // This is the signal frm the other team 
int state = 0;
unsigned long time_since_last_clap = 0;
int opposite_animation = -1; //-1 = false, 1 = true
#define NUM_ANIMATIONS 9 // The number of animations we have programmed   

int counter = 0; // TO BE REMOVED
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
// CASE 0
// flash changing rainbow colours for all bones collectively
void colorRainbowChange(){
  for(int k = 0; k < 6; k++){
    for(int i = 0; i < NUM_SEGMENTS; i++){
      for(int j = 0; j < num_leds[i]; j++){
        leds[i][j] = colour[k];
      }
    }      
    FastLED.show();
    delay(100);
  }
}

// CASE 1
// choose a random colour for all bones dim them overtime
void brightnessChange(){
  //set colour
  rainbowColour = chsvColour[random(6)];
  for(int i = 0; i < NUM_SEGMENTS; i++){
    for(int j = 0; j < num_leds[i]; j++){
      leds[i][j] = CHSV(rainbowColour, SATURATION, BRIGHTNESS);
    }
  }
  FastLED.show();
  delay(200); //waits for 2 second

  //starts fade effect by reducing brightness of the pixel
  for(int k = 255; k >= 0; k--){
    for(int i = 0; i < NUM_SEGMENTS; i++){
      for(int j = 0; j < num_leds[i]; j++){
        leds[i][j] = CHSV(rainbowColour, SATURATION, k);
      }
    } FastLED.show();
  }
  delay(200); //waits for a second
}

// CASE 2
// fill up by lighting one bone segment at a time, from left to right, in a random monocolour
void lightLeftRightBone() {
  rainbowColour = colour[random(6)];
  for (int k = 0; k < (NUM_SEGMENTS + 2); k++){
    if(k == 9){
      for (int i = 10; i < (10 + l2r_num_leds[k]); i++) {
        (leds[l2r[k]])[i] = rainbowColour;
        FastLED.show();
        delay(10);
      }
    }else if(k == 12){
      for (int i = 10; i < (10 + l2r_num_leds[k]); i++) {
        (leds[l2r[k]])[i] = rainbowColour;
        FastLED.show();
        delay(10);
      }
    }else{
      for (int j = 0; j < l2r_num_leds[k]; j++) {
        (leds[l2r[k]])[j] = rainbowColour;
        FastLED.show();
        delay(10);
      }
    }
    FastLED.show();
    delay(100);
  }
  delay(500);
}


// CASE 3
// light up bottom to top, by LEDs
void lightBottomTopLED() {
  rainbowColour = colour[random(6)];
  for (int i = num_leds[7] - 1; i >= 0; i--) { // light up legs
    (leds[7])[i] = rainbowColour;
    (leds[8])[i] = rainbowColour;
    (leds[9])[i] = rainbowColour;
    (leds[10])[i] = rainbowColour;
    FastLED.show();
    delay(30);
  }

  for (int i = 0; i < num_leds[4]; i++) {     // light up ribs
    (leds[4])[i] = rainbowColour;
    (leds[5])[i] = rainbowColour;
    (leds[6])[i] = rainbowColour;
    FastLED.show();
    delay(30);
  }

  for (int i = 0; i <= 11; i++) {             // light up spine, from ends going to center
    if (i <= 9){
      (leds[0])[i] = rainbowColour;
    }else{
      (leds[3])[28 - i] = rainbowColour;
//      (leds[3])[i - 10] = rainbowColour;
    }
    FastLED.show();
    delay(15);
  }

  int head_counter = 0;
  int tail_counter = num_leds[3] - 3;
//  int tail_counter = 2;
  
  for (int i = 0; i < num_leds[1]; i++) {
      (leds[1])[head_counter] = rainbowColour;
      FastLED.show();
      (leds[3])[tail_counter] = rainbowColour;
      FastLED.show();
      delay(15);
      head_counter++;
      tail_counter--;
//      tail_counter++;
  }

  for (int i = 0; i < 10; i++) {
    (leds[2])[i] = rainbowColour;
    (leds[2])[num_leds[2]-i-1] = rainbowColour;
    FastLED.show();
    delay(15);
  }
  
  (leds[2])[10] = rainbowColour;
  FastLED.show();
  delay(500);
}

// CASE 4
// rainbow wave 
void colourRainbowWave() {
  unsigned long start = millis();
  while(millis() - start < 1000){
    for (int j = 0; j < 255; j++) {
      for (int k = 0; k < NUM_SEGMENTS; k++){
        for (int i = 0; i < num_leds[k]; i++) {
          (leds[k])[i] = CHSV(i - (j * 4), SATURATION, BRIGHTNESS); 
        }
        FastLED.show();
      }
    }
  }
}


// CASE 5
// each bone has changing colour
void changingRainbowBone() {
  for (int j = 0; j < 255; j++) {
    for (int k = 0; k < NUM_SEGMENTS; k++){
      for (int i = 0; i < num_leds[k]; i++) {
        if (k == 0 ) {
          (leds[k])[i] = CRGB::MediumPurple;
        } else if (k == 1) {
          (leds[k])[i] = CRGB::Red;
        } else if (k == 2) {
          (leds[k])[i] = CRGB::Orange;
        } else if (k == 3) {
          (leds[k])[i] = CRGB::Yellow;
        } else if (k == 4 || k == 7 || k == 8) {
          (leds[k])[i] = CRGB::Green;
        } else if (k == 5) {
          (leds[k])[i] = CRGB::SkyBlue;
        } else if (k == 6 || k == 9 || k == 10) {
          (leds[k])[i] = CRGB::CadetBlue;
        } 
      }
      FastLED.show();
    }
  }
}



// CASE 6
//flickers random leds on/off 
// could be made more efficient
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
    if (millis() - start > 3000){

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
  delay(200);
}


// CASE 7
// bone segments light up one at a time, incremented by monocolour leds
void lightLeftRightLED() {
  rainbowColour = colour[random(6)];
  for (int k = 0; k < (NUM_SEGMENTS + 2); k++){
    if(k == 9){
      for (int i = 10; i < (10 + l2r_num_leds[k]); i++) {
        (leds[l2r[k]])[i] = rainbowColour;
        FastLED.show();
        delay(10);
      }
    }else if(k == 12){
      for (int i = 10; i < (10 + l2r_num_leds[k]); i++) {
        (leds[l2r[k]])[i] = rainbowColour;
        FastLED.show();
        delay(10);
      }
    }else{
      for (int j = 0; j < l2r_num_leds[k]; j++) {
        (leds[l2r[k]])[j] = rainbowColour;
        FastLED.show();
        delay(10);
      }
    }
  }
  delay(500);
}

// CASE 8
// light up all segments, have one led in different colour travel around
void travelingLED(){
  int display_colour = colour[5];   // purple
  int traveler_colour = colour[2];  // yellow
  for(int i = 0; i < NUM_SEGMENTS; i++){      // initialize general led display colour
    for(int j = 0; j < num_leds[i]; j++){
      leds[i][j] = display_colour;
    }
  }
  FastLED.show();

  for(int i = 0; i < NUM_SEGMENTS; i++){          // set single led colour change in order of path
    for(int j = 0; j < num_leds[cp[i]]; j++){
      if (cp[i] == 5 || cp[i] == 7 || cp[i] == 9){    // travel against led strip orientation
        (leds[cp[i]])[(num_leds[cp[i]]) - j - 1] = traveler_colour;
        FastLED.show();
        delay(10);
        (leds[cp[i]])[(num_leds[cp[i]]) - j - 1] = display_colour;
        FastLED.show();
      }
      else {                                          // forward traveling to led strip orientation
        (leds[cp[i]])[j] = traveler_colour; 
        FastLED.show();
        delay(10);
        (leds[cp[i]])[j] = display_colour;
        FastLED.show();
      }
    }
  }
}

//////////////// ARCHIVED CASES ////////////////////////////////////
// light up left to right, by LEDs
// currently giving out randomized leds lighting up patterns
//void lightLeftRightLED() {
//  rainbowColour = colour[random(6)];
//  for (int k = 0; k < NUM_SEGMENTS; k++){
//    for (int i = num_leds[k] - 1; i >= 0; i--) {
//      (leds[k])[i] = rainbowColour;
//      FastLED.show();
//    }
//  }
//}


// each bone different rainbow colour left to right
void colourRainbowBone() {
  for (int j = 0; j < 255; j++) {
    for (int k = 0; k < NUM_SEGMENTS; k++){
      for (int i = 0; i < num_leds[k]; i++) {
        if (k == 0 ) {
          (leds[k])[i] = CRGB::MediumPurple;
        } else if (k == 1) {
          (leds[k])[i] = CRGB::Red;
        } else if (k == 2) {
          (leds[k])[i] = CRGB::Orange;
        } else if (k == 3) {
          (leds[k])[i] = CRGB::Yellow;
        } else if (k == 4 || k == 7 || k == 8) {
          (leds[k])[i] = CRGB::Green;
        } else if (k == 5) {
          (leds[k])[i] = CRGB::SkyBlue;
        } else if (k == 6 || k == 9 || k == 10) {
          (leds[k])[i] = CRGB::CadetBlue;
        } 
      }
      FastLED.show();
    }
  }
}


// Flashes bones on randomly
void flash_bones(){
  unsigned long start = millis();
  while(millis() - start < 2000){
    CRGB random_color = colour[random(6)];
    int random_bone = random(NUM_SEGMENTS);
    for(int i = 0; i < num_leds[random_bone]; i++){
      (leds[random_bone])[i] = random_color;
      FastLED.show();
    }
    delay(100);
    for(int i = 0; i < num_leds[random_bone]; i++){
      (leds[random_bone])[i] = CRGB::Black;
    }

  }
}


// change color for all bones and LEDs smoothly
void gradualColorRainbowChange(){ 
  for(hue; hue < BRIGHTNESS ; hue++ ){
    for(int i = 0; i < NUM_SEGMENTS; i++){
      for(int j = 0; j < num_leds[i]; j++){
        leds[i][j] = CHSV(hue, 255, BRIGHTNESS);
      }
    } 
    // delay(5);
    FastLED.show();
  }
  hue = 0;
}

//TODO FIX THIS
// light up bottom to top, by LEDs
void lightBottomTop(){
  rainbowColour = colour[random(6)];
  // legs lights up
  int i = 4;
  int j;
  for(j = num_leds[i]; j >= 0; j--){
    while(i < NUM_SEGMENTS){
      leds[i][j] = rainbowColour; 
      FastLED.show();
      i++;
    }
  }
  // head lights up
  i = 0;
  for(j = num_leds[i] - 1; j>= 0; j--){
      leds[i][j] = rainbowColour;
      FastLED.show();
  }
  // spine lights up 
  for(i = 2; i < 5; i++){
    for(j = num_leds[i] - 1; j >= 0; j--){
      leds[i][j] = rainbowColour;
      FastLED.show();
    }
  }
}

/**********END OF ANIMATION FUNCTION IMPLEMENTATIONS******************/


const int microphonePin = A0;
void setup()
{
  FastLED.setBrightness(BRIGHTNESS);

  LEDS.addLeds<WS2812B, 2, COLOR_ORDER>(leds1, NUM_LEDS1);  // Body
  LEDS.addLeds<WS2812B, 3, COLOR_ORDER>(leds2, NUM_LEDS2);
  LEDS.addLeds<WS2812B, 4, COLOR_ORDER>(leds3, NUM_LEDS3);
  LEDS.addLeds<WS2812B, 5, COLOR_ORDER>(leds4, NUM_LEDS4);
  LEDS.addLeds<WS2812B, 6, COLOR_ORDER>(leds5, NUM_LEDS5);
  LEDS.addLeds<WS2812B, 7, COLOR_ORDER>(leds6, NUM_LEDS6);
  LEDS.addLeds<WS2812B, 8, COLOR_ORDER>(leds7, NUM_LEDS7);
  LEDS.addLeds<WS2812B, A1, COLOR_ORDER>(leds8, NUM_LEDS8);  // Feet
  LEDS.addLeds<WS2812B, A2, COLOR_ORDER>(leds9, NUM_LEDS9);
  LEDS.addLeds<WS2812B, A3, COLOR_ORDER>(leds10, NUM_LEDS10);
  LEDS.addLeds<WS2812B, A4, COLOR_ORDER>(leds11, NUM_LEDS11);

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

  //left to right mapping
  l2r[0] = 0;
  l2r[1] = 1;
  l2r[2] = 7;
  l2r[3] = 4;
  l2r[4] = 8;
  l2r[5] = 5;
  l2r[6] = 2;
  l2r[7] = 6;
  l2r[8] = 9;
  l2r[9] = 2;
  l2r[10] = 10;
  l2r[11] = 3;
  l2r[12] = 3;

  // l2r leds separating strip 2 into 2 sections
  l2r_num_leds[0] = NUM_LEDS1;
  l2r_num_leds[1] = NUM_LEDS2;
  l2r_num_leds[2] = NUM_LEDS8;
  l2r_num_leds[3] = NUM_LEDS5;
  l2r_num_leds[4] = NUM_LEDS9;
  l2r_num_leds[5] = NUM_LEDS6;
  l2r_num_leds[6] = 10;
  l2r_num_leds[7] = NUM_LEDS7;
  l2r_num_leds[8] = NUM_LEDS10;
  l2r_num_leds[9] = 11;
  l2r_num_leds[10] = NUM_LEDS11;
  l2r_num_leds[11] = 10;
  l2r_num_leds[12] = 9;

  // connected path mapping
  cp[0] = 0;    // forwards
  cp[1] = 1;    // f
  cp[2] = 2;    // f
  cp[3] = 3;    // f
  cp[4] = 7;    // f
  cp[5] = 8;    // backwards
  cp[6] = 9;    // f
  cp[7] = 10;    // b
  cp[8] = 4;    // f
  cp[9] = 5;    // b
  cp[10] = 6;    // f
  // generate a random number
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 1000; ++i)
  {

    int val = analogRead(microphonePin);

    mn = min(mn, val);
    mx = max(mx, val);
  }

  int delta = mx - mn;

#ifdef DEBUG
  Serial.print("Min=");
  Serial.print(mn);
  Serial.print(" Max=");
  Serial.print(mx);
  Serial.print(" Delta=");
  Serial.println(delta);
#endif // DEBUG

  if (delta > threshold)
  {
    // actuate 
    state = random(NUM_ANIMATIONS);
//    state = counter%7;
//    counter++;
    switch(state){
        case 0:
          colorRainbowChange();  
          break;
        case 1:
          brightnessChange();
          break;
        case 2:
          lightLeftRightBone();
          break;
        case 3:
          lightBottomTopLED();
          break;
        case 4:
          flash_bones();
          break;
        case 5:
          gradualColorRainbowChange();
          break;
        case 6:
          flicker(CRGB::White);
          break;
        case 7:
          lightLeftRightLED();
          break;
        case 8:
          travelingLED();
          break;
        default:
          break;
      }

      //reset to black
    for(int i = 0; i < NUM_SEGMENTS; i++){
      for(int j = 0; j < num_leds[i]; j++){
        leds[i][j] = CRGB::Black;
      }
    }      
    FastLED.show();
    delay(100);

  }
}
