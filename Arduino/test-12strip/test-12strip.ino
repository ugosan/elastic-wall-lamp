#include <Adafruit_NeoPixel.h>
#include <time.h>


#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            D6

#define NUMPIXELS      12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1;

int snake = 0;


int bubbleA[] = {0,1};
int bubbleB[] = {2,3};
int bubbleC[] = {4,5};
int bubbleD[] = {6,7};
int bubbleE[] = {8,9};
int bubbleF[] = {10,11};

int bubbleA_color[] = {13, 94, 173};
int bubbleB_color[] = {255, 37, 50};
int bubbleC_color[] = {253, 253, 0};
int bubbleD_color[] = {13, 94, 173};
int bubbleE_color[] = {0, 152, 5};
int bubbleF_color[] = {32, 252, 203};



void setup(void) {


  Serial.begin(115200);
  
  pixels.begin();
  pixels.setBrightness(205);
}

void loop(void) {
  //allWhite();

  
  //elasticStandard();

 
  /*
  for (int i = 0; i < 1000; i++) {
   
  
    setBubbleColor(bubbleA, sizeof(bubbleA)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 0, 10000)));
    setBubbleColor(bubbleB, sizeof(bubbleB)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 10000, 20000)));
    setBubbleColor(bubbleC, sizeof(bubbleC)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 20000, 30000)));
    setBubbleColor(bubbleD, sizeof(bubbleD)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 30000, 40000)));
    setBubbleColor(bubbleE, sizeof(bubbleE)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 40000, 50000)));
    setBubbleColor(bubbleF, sizeof(bubbleE)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 50000, 65000)));
    

  }
*/

  inhale_exhale_fire();
  
  
  /*

  
  delay(5000);

  rainbow(100);
  rainbow(90);
  rainbow(80);
  rainbow(70);
  rainbow(60); 
  rainbow(50);
  rainbow(40);  
  rainbow(5);
  

  */


}


void inhale_exhale_fire(){
 for (int i = 0; i < 1000; i++) {
  flame(i);
  pixels.show();
  delay(1);
 }
 for (int i = 1000; i > 0; i--) {
  flame(i);
  pixels.show();
  delay(1);
 }
  
}

void flame(int i){
  
   setBubbleColor(bubbleA, sizeof(bubbleA)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 5000, 0)));
   setBubbleColor(bubbleB, sizeof(bubbleB)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 2000, 3000)));
   setBubbleColor(bubbleC, sizeof(bubbleC)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 1000, 2000)));
   setBubbleColor(bubbleD, sizeof(bubbleD)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 0, 5000)));
   setBubbleColor(bubbleE, sizeof(bubbleE)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 4000, 6000)));
   setBubbleColor(bubbleF, sizeof(bubbleE)/sizeof(int), pixels.ColorHSV( map(i,0,1000, 6000, 10000)));
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}


void allWhite(){
  uint16_t i, j;
  for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, 255, 255, 255);
      pixels.show();
      delay(50);
  }
}

void elasticStandard() {

  setBubbleColor(bubbleA, sizeof(bubbleA)/sizeof(int), pixels.Color(255, 0, 0) );
  setBubbleColor(bubbleB, sizeof(bubbleB)/sizeof(int), pixels.Color(255, 0, 0) );
  pixels.show();
  delay(200);
  
    for (int i = 0; i < sizeof(bubbleB) / sizeof(int); i++) {
      pixels.setPixelColor(bubbleB[i], bubbleB_color[0], bubbleB_color[1], bubbleA_color[2]);
    }
    
    pixels.show();
    delay(200);
  
    for (int i = 0; i < sizeof(bubbleC) / sizeof(int); i++) {
       pixels.setPixelColor(bubbleC[i], bubbleC_color[0], bubbleC_color[1], bubbleC_color[2]);
    }
    
    pixels.show();
    delay(200);
    
    for (int i = 0; i < sizeof(bubbleD) / sizeof(int); i++) {
      pixels.setPixelColor(bubbleD[i], bubbleD_color[0], bubbleD_color[1], bubbleD_color[2]);
    }
    
    pixels.show();
    delay(200);
  
    for (int i = 0; i < sizeof(bubbleE) / sizeof(int); i++) {
      pixels.setPixelColor(bubbleE[i], bubbleE_color[0], bubbleE_color[1], bubbleE_color[2]); 
    }
    
    pixels.show();
    delay(200);
  
    for (int i = 0; i < sizeof(bubbleF) / sizeof(int); i++) {
      pixels.setPixelColor(bubbleF[i], bubbleF_color[0], bubbleF_color[1], bubbleF_color[2]);
    }
    
    pixels.show();
    delay(200);

 
}


void setBubbleColor(int bubble[], uint8_t size, uint32_t color) {
  for (int i = 0; i < size; i++) {
      pixels.setPixelColor(bubble[i], color);
   }
}
