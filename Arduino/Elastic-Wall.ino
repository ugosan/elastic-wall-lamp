#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include <time.h>

#include "page.h"

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            D6

#define NUMPIXELS      85

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1;

const char* ssid = "";
const char* password = "";

ESP8266WebServer server(80);

int snake = 0;


int bubbleA[] = {50, 51, 52, 53, 54, 55, 56, 57, 58, 60, 61};
int bubbleB[] = {59, 62, 63, 64, 65, 66, 67, 68};
int bubbleC[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 70, 72};
int bubbleD[] = {29, 73, 74, 75, 76, 77, 78, 79, 80, 81};
int bubbleE[] = {82, 83, 84, 85};
int bubbleF[] = {0, 1, 2, 3, 4, 5, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 69, 71 };

int bubbleA_color[] = {13, 94, 173};
int bubbleB_color[] = {255, 37, 50};
int bubbleC_color[] = {253, 253, 0};
int bubbleD_color[] = {13, 94, 173};
int bubbleE_color[] = {0, 152, 5};
int bubbleF_color[] = {32, 252, 203};



void setup(void) {

  Serial.begin(115200);
  
  pixels.begin();

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //if (MDNS.begin("elasticlamp.local")) {
  //  Serial.println("MDNS responder started");
  //}

  server.on("/", handleRequest);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  //brightness in range 0 - 255
  pixels.setBrightness(205);
  allWhite();
}

void loop(void) {
  
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
  }
  server.handleClient();
  
  inhale_exhale_fire();
  
  elasticStandard();

  server.handleClient();

  
  delay(5000);

  rainbow(100);
  rainbow(90);
  rainbow(80);
  rainbow(70); 
  rainbow(5);
  rainbow(5);

  for( uint16_t t = 0; t<10; t++){
    rainbow(1);
  }
  
 



}


void handleRequest() {

  server.send(200, "text/html", MAIN_page);

  if (server.method() == HTTP_POST) {
    String bubble = server.arg("bubble");
    int r = server.arg("r").toInt();
    int g = server.arg("g").toInt();
    int b = server.arg("b").toInt();

    if(bubble == "A"){
      bubbleA_color[0] = r;
      bubbleA_color[1] = g;
      bubbleA_color[2] = b;
    }else if (bubble == "B"){
      bubbleB_color[0] = r;
      bubbleB_color[1] = g;
      bubbleB_color[2] = b;
    }else if (bubble == "C"){
      bubbleC_color[0] = r;
      bubbleC_color[1] = g;
      bubbleC_color[2] = b;
    }else if (bubble == "D"){
      bubbleD_color[0] = r;
      bubbleD_color[1] = g;
      bubbleD_color[2] = b;
    }else if (bubble == "E"){
      bubbleE_color[0] = r;
      bubbleE_color[1] = g;
      bubbleE_color[2] = b;
    }else if (bubble == "F"){
      bubbleF_color[0] = r;
      bubbleF_color[1] = g;
      bubbleF_color[2] = b;
    }

  }


}

void handleNotFound() {
  server.send(404, "text/plain", "404 Not Found");
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
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, 255, 255, 255);
      pixels.show();
      delay(20);
  }
}

void elasticStandard() {

    setBubbleColor(bubbleA, sizeof(bubbleA)/sizeof(int), pixels.Color(bubbleA_color[0], bubbleA_color[1], bubbleA_color[2]));
    pixels.show();
    delay(200);

    setBubbleColor(bubbleB, sizeof(bubbleB)/sizeof(int), pixels.Color(bubbleB_color[0], bubbleB_color[1], bubbleB_color[2]));
    pixels.show();
    delay(200);

    setBubbleColor(bubbleC, sizeof(bubbleC)/sizeof(int), pixels.Color(bubbleC_color[0], bubbleC_color[1], bubbleC_color[2]));
    pixels.show();
    delay(200);

    setBubbleColor(bubbleD, sizeof(bubbleD)/sizeof(int), pixels.Color(bubbleD_color[0], bubbleD_color[1], bubbleD_color[2]));
    pixels.show();
    delay(200);

    setBubbleColor(bubbleE, sizeof(bubbleE)/sizeof(int), pixels.Color(bubbleE_color[0], bubbleE_color[1], bubbleE_color[2]));
    pixels.show();
    delay(200);

    setBubbleColor(bubbleF, sizeof(bubbleF)/sizeof(int), pixels.Color(bubbleF_color[0], bubbleF_color[1], bubbleF_color[2]));
    pixels.show();
    delay(200);   
 
}




void inhale_exhale_fire(){
  uint8_t range_max = 1000;
  uint8_t iterations = 10;
  
  for( uint16_t t = 0; t < iterations; t++){
    for (uint16_t i = 0; i < range_max; i++) {
      flame(i, range_max);
      pixels.show();
      delay(2);
     }
     for (uint16_t i = range_max; i > 0; i--) {
      flame(i, range_max);
      pixels.show();
      delay(2);
    }
  }
 
}

void flame(int i, int range_max){
   
   setBubbleColor(bubbleA, sizeof(bubbleA)/sizeof(int), pixels.ColorHSV( map(i,0,range_max, 3000, 700)));
   setBubbleColor(bubbleB, sizeof(bubbleB)/sizeof(int), pixels.ColorHSV( map(i,0,range_max, 3000, 6000)));
   setBubbleColor(bubbleC, sizeof(bubbleC)/sizeof(int), pixels.ColorHSV( map(i,0,range_max, 5000, 1000)));
   setBubbleColor(bubbleD, sizeof(bubbleD)/sizeof(int), pixels.ColorHSV( map(i,0,range_max, 700, 5000)));
   setBubbleColor(bubbleE, sizeof(bubbleE)/sizeof(int), pixels.ColorHSV( map(i,0,range_max, 3500, 6000)));
   setBubbleColor(bubbleF, sizeof(bubbleF)/sizeof(int), pixels.ColorHSV( map(i,0,range_max, 4000, 700)));
}


void setBubbleColor(int bubble[], uint8_t size, uint32_t color) {
  for (uint16_t i = 0; i < size; i++) {
      pixels.setPixelColor(bubble[i], color);
   }
}
