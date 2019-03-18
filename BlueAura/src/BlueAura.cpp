/* ======================= includes ================================= */

#include "Particle.h"
#include "neopixel.h"

void setup();
void loop();
void showStrip();
void setPixel(int Pixel, byte red, byte green, byte blue);
void setAll(byte red, byte green, byte blue);
void FadeInOut(byte red, byte green, byte blue);
void FadeIn(byte red, byte green, byte blue);
void FadeOut(byte red, byte green, byte blue);
#line 6 "/Users/jeremykoerber/code/particle/BlueAura/src/BlueAura.ino"
SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define NUM_LEDS 68
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(NUM_LEDS, PIXEL_PIN, PIXEL_TYPE);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  FadeInOut(0xff, 0x00, 0x00); // red
  FadeIn(0x00, 0x00, 0xff); // blue
}

void loop() {
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
    delay(10);
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(10);
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