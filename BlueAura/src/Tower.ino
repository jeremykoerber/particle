/* ======================= includes ================================= */

#include "Particle.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define NUM_LEDS 37
#define PIXEL_PIN D2
#define PIXEL_TYPE SK6812RGBW

Adafruit_NeoPixel strip(NUM_LEDS, PIXEL_PIN, PIXEL_TYPE);
int x;
int y;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Particle.subscribe("Tower", lightHandler, MY_DEVICES);
  x = 0;
  y = 0;
}

void lightHandler(const char *event, const char *data)
{
  Serial.println("event received");
  std::string Event (event);
  std::string ChangeMode ("Tower-ChangeMode");
  if (Event == ChangeMode)
  {
    x += 1;
  }
}

void loop() {
  if (x == 0) {
    rainbow(200);
    //Fire(25,90,40);
    //CylonBounce(0, 0xff, 0, 4, 80, 100);
    //TwinkleRandom(20, 300, false);
  }
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

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {    setAll(0,0,0);
  setPixel(i, red/10, green/10, blue/10);
  for(int j = 1; j <= EyeSize; j++) {
     setPixel(i+j, red, green, blue); 
    }    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
  showStrip();
   delay(SpeedDelay);
  }
  delay(ReturnDelay);
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {    setAll(0,0,0);
  setPixel(i, red/10, green/10, blue/10);
  for(int j = 1; j <= EyeSize; j++) {
     setPixel(i+j, red, green, blue); 
    }    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
  showStrip();
   delay(SpeedDelay);
  }  
 delay(ReturnDelay);
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(255, Pixel, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(255, Pixel, heatramp, 0);
  } else {                               // coolest
    setPixel(heatramp, Pixel, 0, 0);
  }
}