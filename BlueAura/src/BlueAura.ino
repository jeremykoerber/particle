/* ======================= includes ================================= */

#include "Particle.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define NUM_LEDS 50
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(NUM_LEDS, PIXEL_PIN, PIXEL_TYPE);
int x;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  FadeInOut(0xff, 0x00, 0x00); // red
  x = 0;
  Particle.subscribe("BlueAura", lightHandler, MY_DEVICES);
}

void lightHandler(const char *event, const char *data)
{
  Serial.println("event received");
  std::string Event (event);
  std::string Rainbow ("BlueAura-Rainbow");
  std::string RainbowCycle ("BlueAura-RainbowCycle");
  //std::string RainbowChase ("BlueAura-RainbowChase");
  std::string LightOff ("BlueAura-LightOff");
  std::string Red ("BlueAura-Red");
  std::string White ("BlueAura-White");
  std::string Blue ("BlueAura-Blue");
  uint16_t i;
  if (Event == Rainbow)
  {
    x = 1;
    for(i=0; i<10; i++) {
      rainbow(20);
    }
  }
  else if (Event == RainbowCycle)
  {
    x = 1;
    for(i=0; i<10; i++) {
      rainbowCycle(20);
    }
  }
  //else if (Event == RainbowChase)
  //{
  //  for(i=0; i<10; i++) {
  //    theaterChaseRainbow(20);
  //  }
  //}
  else if (Event == LightOff)
  {
    setAll(0x00, 0x00, 0x00); // off
    x = 2;
  }
  else if (Event == Red)
  {
    x = 1;
    setAll(0xff, 0x00, 0x00); // red
  }
  else if (Event == White)
  {
    x = 1;
    setAll(0xff, 0xff, 0xff); // white
  }
  else if (Event == Blue)
  {
    x = 1;
    setAll(0x00, 0x00, 0xff); // blue
  }
}

void loop() {
  if (Particle.connected()) {
    if (x == 0) {
      FadeInOut(0x00, 0xff, 0x00); // green
      FadeIn(0x00, 0x00, 0xff); // blue
      x = 1;
    }
    else if (x == 2) {
      setAll(0x00, 0x00, 0x00); // off
    }
    //setAll(0x00, 0x00, 0xff); // blue
  }
  else {
    x = 0;
    setAll(0x7f, 0x00, 0x00); // dim red
  }
  delay(1000);
}

void showStrip() {
  strip.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void FadeInOut(byte red, byte green, byte blue){
  float r, g, b;
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
}

void FadeIn(byte red, byte green, byte blue){
  float r, g, b;
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(10);
  }
}

void FadeOut(byte red, byte green, byte blue){
  float r, g, b;
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(10);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout, then wait (ms)
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) { // 1 cycle of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
