#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>
#include <time.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "credentials.h"
#include "ledmatrix.h"

#define PIN            D6

#define NUMPIXELS      86

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
WiFiClientSecure httpsClient;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

int delayval = 1;
int columnScan = 0;
uint32_t columnColor = 0;

uint16_t currentHour = -1;
uint16_t turn_on_hour = -1;
uint16_t turn_off_hour = -1;
uint16_t brightness = 20;

bool mode_rainbow_enabled = true;
bool mode_fire_enabled = true;
bool mode_standard_enabled = true;


// Maps every pixel in the sequential strip to a "bubble" in the logo
int bubbleA[] = {50, 51, 52, 53, 54, 55, 56, 57, 58, 60, 61};
int bubbleB[] = {59, 62, 63, 64, 65, 66, 67, 68};
int bubbleC[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 70, 72};
int bubbleD[] = {29, 73, 74, 75, 76, 77, 78, 79, 80, 81};
int bubbleE[] = {82, 83, 84, 85};
int bubbleF[] = {0, 1, 2, 3, 4, 5, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 69, 71 };

// RGB colors for each bubble
int bubbleA_color[] = {13, 94, 173};
int bubbleB_color[] = {255, 37, 50};
int bubbleC_color[] = {253, 253, 0};
int bubbleD_color[] = {13, 94, 173};
int bubbleE_color[] = {0, 152, 5};
int bubbleF_color[] = {32, 252, 203};



void setup(void) {
  pixels.begin();

  pinMode(LED_BUILTIN, OUTPUT); //LED pin as output
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  httpsClient.setInsecure();
  fetchConfig();
  updateCurrentTime();

  //brightness in range 0 - 255
  pixels.setBrightness(brightness);
  allWhite();

}

void loop(void) {

  //columnScanMatrix(10);

  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  

  if (mode_standard_enabled) {
    elasticStandard();
    delay(15000);
  }

  String json = fetchConfig();
  applyConfig(json);
  updateCurrentTime();

  if (mode_rainbow_enabled) {
    rainbow(100);
    rainbow(90);
    rainbow(80);
    rainbow(70);
    rainbow(5);
    rainbow(5);
  }

  if (mode_fire_enabled) {
    inhale_exhale_fire();
  }



}



/**
    Input a value 0 to 255 to get a color value.
    The colours are a transition r - g - b - back to r.
    e.g.
    pixels.setPixelColor(0, Wheel(100));

    @return a 32bit integer
*/
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


void columnScanMatrix(uint8_t wait) {
  uint16_t x, y, i, j;

  for (y = 0; y < 44; y++) {
    for (x = 0; x < 44; x++) {

      if ( (ledMatrix[y][x] != -1) && (columnScan == x) ) {

        pixels.setPixelColor(ledMatrix[y][x], columnColor);

      } else {
        //pixels.setPixelColor(ledMatrix[x][y], 0);
      }

    }

    pixels.show();
    delay(wait);

  }

  columnScan++;
  columnColor = Wheel(160 + columnScan);
  if (columnScan == 43) {
    columnScan = 0;
  }


}


void allWhite() {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, 255, 255, 255);
    pixels.show();
    delay(20);
  }
}

void turnOff() {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
    delay(50);
  }
}

void elasticStandard() {

  setBubbleColor(bubbleA, sizeof(bubbleA) / sizeof(int), pixels.Color(bubbleA_color[0], bubbleA_color[1], bubbleA_color[2]));
  pixels.show();
  delay(200);

  setBubbleColor(bubbleB, sizeof(bubbleB) / sizeof(int), pixels.Color(bubbleB_color[0], bubbleB_color[1], bubbleB_color[2]));
  pixels.show();
  delay(200);

  setBubbleColor(bubbleC, sizeof(bubbleC) / sizeof(int), pixels.Color(bubbleC_color[0], bubbleC_color[1], bubbleC_color[2]));
  pixels.show();
  delay(200);

  setBubbleColor(bubbleD, sizeof(bubbleD) / sizeof(int), pixels.Color(bubbleD_color[0], bubbleD_color[1], bubbleD_color[2]));
  pixels.show();
  delay(200);

  setBubbleColor(bubbleE, sizeof(bubbleE) / sizeof(int), pixels.Color(bubbleE_color[0], bubbleE_color[1], bubbleE_color[2]));
  pixels.show();
  delay(200);

  setBubbleColor(bubbleF, sizeof(bubbleF) / sizeof(int), pixels.Color(bubbleF_color[0], bubbleF_color[1], bubbleF_color[2]));
  pixels.show();
  delay(200);

}




void inhale_exhale_fire() {
  uint8_t range_max = 1000;
  uint8_t iterations = 10;

  for ( uint16_t t = 0; t < iterations; t++) {
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

void flame(int i, int range_max) {

  setBubbleColor(bubbleA, sizeof(bubbleA) / sizeof(int), pixels.ColorHSV( map(i, 0, range_max, 3000, 700)));
  setBubbleColor(bubbleB, sizeof(bubbleB) / sizeof(int), pixels.ColorHSV( map(i, 0, range_max, 3000, 6000)));
  setBubbleColor(bubbleC, sizeof(bubbleC) / sizeof(int), pixels.ColorHSV( map(i, 0, range_max, 5000, 1000)));
  setBubbleColor(bubbleD, sizeof(bubbleD) / sizeof(int), pixels.ColorHSV( map(i, 0, range_max, 700, 5000)));
  setBubbleColor(bubbleE, sizeof(bubbleE) / sizeof(int), pixels.ColorHSV( map(i, 0, range_max, 3500, 6000)));
  setBubbleColor(bubbleF, sizeof(bubbleF) / sizeof(int), pixels.ColorHSV( map(i, 0, range_max, 4000, 700)));
}


void setBubbleColor(int bubble[], uint8_t size, uint32_t color) {
  for (uint16_t i = 0; i < size; i++) {
    pixels.setPixelColor(bubble[i], color);
  }
}



void updateCurrentTime() {
  timeClient.update();
  currentHour = timeClient.getHours();
}


/**
    Fetches the config document from an Elasticsearch cluster defined by ELASTICSEARCH_HOST and
    ELASTICSEARCH_PORT, the document index and id are declared in the "ELASTICSEARCH_DOC" const.
    e.g. "/elastic-wall-lamp/_doc/1"

    @return the JSON document
*/
String fetchConfig() {
  Serial.print("HTTPS Connecting");
  int retry_counter = 0;
  while ((!httpsClient.connect(ELASTICSEARCH_HOST, ELASTICSEARCH_PORT)) && (retry_counter < 30)) {
    delay(100);
    Serial.print(".");
    retry_counter++;
  }
  if (retry_counter == 30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }

  httpsClient.print(String("GET ") + ELASTICSEARCH_DOC + " HTTP/1.1\r\n" +
                    "Host: " + ELASTICSEARCH_HOST + "\r\n" +
                    "Authorization: ApiKey " + ELASTICSEARCH_API_KEY_BASE64 + " \r\n" +
                    "Connection: close\r\n\r\n");

  Serial.println("request sent");

  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  Serial.println("= reply =");
  String json;
  while (httpsClient.available()) {
    json += httpsClient.readStringUntil('\n');
  }

  Serial.println(json);
  return json;
}


/**
    Parses the JSON fetched from fetchConfig in "input" and updates
    the local variables. The parser is automatically generated from
    https://arduinojson.org/v6/assistant/, just copy the generated
    code and replace where appropriate

    @param input - the JSON document from Elasticsearch
*/
void applyConfig(String input) {

  /* The code below is automatically generated from https://arduinojson.org/v6/assistant/  */
  /* ====================================================================================  */

  StaticJsonDocument<2048> doc;

  DeserializationError error = deserializeJson(doc, input);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  JsonObject source = doc["_source"];
  int source_turn_on_hour = source["turn_on_hour"]; // 14
  int source_turn_off_hour = source["turn_off_hour"]; // 22
  int source_brightness = source["brightness"]; // 100

  int source_mode_rainbow_enabled = source["mode_rainbow"]["enabled"]; // 1

  int source_mode_fire_enabled = source["mode_fire"]["enabled"]; // 1

  JsonObject source_mode_standard = source["mode_standard"];
  int source_mode_standard_enabled = source_mode_standard["enabled"]; // 1

  JsonArray source_mode_standard_bubbleA_color = source_mode_standard["bubbleA_color"];
  int source_mode_standard_bubbleA_color_0 = source_mode_standard_bubbleA_color[0]; // 13
  int source_mode_standard_bubbleA_color_1 = source_mode_standard_bubbleA_color[1]; // 94
  int source_mode_standard_bubbleA_color_2 = source_mode_standard_bubbleA_color[2]; // 173

  JsonArray source_mode_standard_bubbleB_color = source_mode_standard["bubbleB_color"];
  int source_mode_standard_bubbleB_color_0 = source_mode_standard_bubbleB_color[0]; // 255
  int source_mode_standard_bubbleB_color_1 = source_mode_standard_bubbleB_color[1]; // 37
  int source_mode_standard_bubbleB_color_2 = source_mode_standard_bubbleB_color[2]; // 50

  JsonArray source_mode_standard_bubbleC_color = source_mode_standard["bubbleC_color"];
  int source_mode_standard_bubbleC_color_0 = source_mode_standard_bubbleC_color[0]; // 253
  int source_mode_standard_bubbleC_color_1 = source_mode_standard_bubbleC_color[1]; // 253
  int source_mode_standard_bubbleC_color_2 = source_mode_standard_bubbleC_color[2]; // 0

  JsonArray source_mode_standard_bubbleD_color = source_mode_standard["bubbleD_color"];
  int source_mode_standard_bubbleD_color_0 = source_mode_standard_bubbleD_color[0]; // 13
  int source_mode_standard_bubbleD_color_1 = source_mode_standard_bubbleD_color[1]; // 94
  int source_mode_standard_bubbleD_color_2 = source_mode_standard_bubbleD_color[2]; // 173

  JsonArray source_mode_standard_bubbleE_color = source_mode_standard["bubbleE_color"];
  int source_mode_standard_bubbleE_color_0 = source_mode_standard_bubbleE_color[0]; // 0
  int source_mode_standard_bubbleE_color_1 = source_mode_standard_bubbleE_color[1]; // 152
  int source_mode_standard_bubbleE_color_2 = source_mode_standard_bubbleE_color[2]; // 5

  JsonArray source_mode_standard_bubbleF_color = source_mode_standard["bubbleF_color"];
  int source_mode_standard_bubbleF_color_0 = source_mode_standard_bubbleF_color[0]; // 32
  int source_mode_standard_bubbleF_color_1 = source_mode_standard_bubbleF_color[1]; // 252
  int source_mode_standard_bubbleF_color_2 = source_mode_standard_bubbleF_color[2]; // 203

  /* ====================================================================================  */
  /* The code above is automatically generated from https://arduinojson.org/v6/assistant/  */


  mode_rainbow_enabled = source_mode_rainbow_enabled;
  mode_standard_enabled = source_mode_standard_enabled;
  mode_fire_enabled = source_mode_fire_enabled;

  turn_on_hour =  source_turn_on_hour;
  turn_off_hour =  source_turn_off_hour;
  brightness = source_brightness;

  pixels.setBrightness(brightness);

  bubbleA_color[0] = source_mode_standard_bubbleA_color_0;
  bubbleA_color[1] = source_mode_standard_bubbleA_color_1;
  bubbleA_color[2] = source_mode_standard_bubbleA_color_2;

  bubbleB_color[0] = source_mode_standard_bubbleB_color_0;
  bubbleB_color[1] = source_mode_standard_bubbleB_color_1;
  bubbleB_color[2] = source_mode_standard_bubbleB_color_2;

  bubbleC_color[0] = source_mode_standard_bubbleC_color_0;
  bubbleC_color[1] = source_mode_standard_bubbleC_color_1;
  bubbleC_color[2] = source_mode_standard_bubbleC_color_2;

  bubbleD_color[0] = source_mode_standard_bubbleD_color_0;
  bubbleD_color[1] = source_mode_standard_bubbleD_color_1;
  bubbleD_color[2] = source_mode_standard_bubbleD_color_2;

  bubbleE_color[0] = source_mode_standard_bubbleE_color_0;
  bubbleE_color[1] = source_mode_standard_bubbleE_color_1;
  bubbleE_color[2] = source_mode_standard_bubbleE_color_2;

  bubbleF_color[0] = source_mode_standard_bubbleF_color_0;
  bubbleF_color[1] = source_mode_standard_bubbleF_color_1;
  bubbleF_color[2] = source_mode_standard_bubbleF_color_2;

}

void flashBuiltInLed(int times) {
  for ( uint16_t t = 0; t < times; t++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
