/*
 * Project 3d-beast-light
 * Description: Neopixel controller for 3D Beast controlled by Octoprint events via IFTTT
 * Author: Jeremy Koerber
 * Date: 3-7-
 */

/* ======================= includes ================================= */

#include "Particle.h"
#include "neopixel.h"

/* ======================= prototypes =============================== */

void colorAll(uint32_t c, uint8_t wait);
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
uint32_t Wheel(byte WheelPos);

/* ======================= extra-examples.cpp ======================== */

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define NUM_LEDS 39
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(NUM_LEDS, PIXEL_PIN, PIXEL_TYPE);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Particle.subscribe("OctoPrint", lightHandler, MY_DEVICES);
}

void lightHandler(const char *event, const char *data)
{
  Serial.println("event received");
  std::string Event (event);
  std::string PrintDone ("OctoPrint-PrintDone");
  std::string LightOn ("OctoPrint-LightOn");
  std::string LightOff ("OctoPrint-LightOff");
  std::string Startup ("OctoPrint-Startup");
  std::string Shutdown ("OctoPrint-Shutdown");
  std::string Connecting ("OctoPrint-Connecting");
  std::string Connected ("OctoPrint-Connected");
  std::string Disconnecting ("OctoPrint-Disconnecting");
  std::string Disconnected ("OctoPrint-Disconnected");
  std::string Error ("OctoPrint-Error");
  std::string PrintStarted ("OctoPrint-PrintStarted");
  std::string PrintFailed ("OctoPrint-PrintFailed");
  std::string PrintCancelling ("OctoPrint-PrintCancelling");
  std::string PrintCancelled ("OctoPrint-PrintCancelled");
  std::string PrintPaused ("OctoPrint-PrintPaused");
  std::string PrintResumed ("OctoPrint-PrintResumed");
  std::string Home ("OctoPrint-Home");
  std::string Waiting ("OctoPrint-Waiting");
  std::string Cooling ("OctoPrint-Cooling");
  std::string Alert ("OctoPrint-Alert");
  std::string EStop ("OctoPrint-EStop");
  std::string ToolChange ("OctoPrint-ToolChange");
  uint16_t i;
  if (Event == PrintDone)
  {
    for(i=0; i<10; i++) {
        rainbowCycle(20);
    }
    colorAll(strip.Color(0, 0, 0), 50);
    strip.show();
  }
  else if (Event == LightOn)
  {
    colorAll(strip.Color(255, 255, 255), 50);
    strip.show();
  }
  else if (Event == LightOff)
  {
    colorAll(strip.Color(0, 0, 0), 50);
    strip.show();
  }
  else if (Event == Startup)
  {
    colorAll(strip.Color(0, 0, 255), 50);
    strip.show();
  }
  else if (Event == Shutdown)
  {
    colorAll(strip.Color(255, 127, 0), 50);
    strip.show();
  }
  else if (Event == Connecting)
  {
    theaterChase(0xff,0xff,0xff,50);
  }
  else if (Event == Connected)
  {
    colorAll(strip.Color(0, 0, 63), 50);
    strip.show();
    delay(1000);
    colorAll(strip.Color(255, 255, 255), 50);
    strip.show();
  }
  else if (Event == Disconnecting)
  {
    colorWipe(strip.Color(127, 127, 0), 50);
    strip.show();
    colorWipe(strip.Color(127, 63, 0), 50);
    strip.show();
    colorWipe(strip.Color(127, 127, 0), 50);
    strip.show();
    colorWipe(strip.Color(127, 63, 0), 50);
    strip.show();
    colorAll(strip.Color(0, 0, 0), 50);
    strip.show();
  }
  else if (Event == Disconnected)
  {
    colorAll(strip.Color(63, 63, 0), 50);
    strip.show();
  }
  else if (Event == Error)
  {
    colorClose(strip.Color(255, 0, 0), 25);
    strip.show();
    colorClose(strip.Color(0, 0, 0), 25);
    strip.show();
    colorClose(strip.Color(255, 0, 0), 25);
    strip.show();
    colorClose(strip.Color(0, 0, 0), 25);
    strip.show();
    colorClose(strip.Color(255, 0, 0), 25);
    strip.show();
    colorClose(strip.Color(0, 0, 0), 25);
    strip.show();
    colorAll(strip.Color(255, 0, 0), 50);
    strip.show();
  }
  else if (Event == PrintStarted)
  {
    colorAll(strip.Color(255, 255, 255), 50);
    strip.show();
  }
  else if (Event == PrintFailed)
  {
    colorWipe(strip.Color(255, 0, 0), 10);
    strip.show();
    colorWipe(strip.Color(0, 0, 0), 10);
    strip.show();
    delay (1000);
    colorWipe(strip.Color(255, 0, 0), 10);
    strip.show();
    colorWipe(strip.Color(0, 0, 0), 10);
    strip.show();
    delay (1000);
    colorWipe(strip.Color(255, 0, 0), 10);
    strip.show();
    colorWipe(strip.Color(0, 0, 0), 10);
    strip.show();
    delay (1000);
    colorAll(strip.Color(255, 0, 0), 50);
    strip.show();
  }
  else if (Event == PrintCancelling)
  {
    FadeInOut(0xff, 0xff, 0x00, 0);
    FadeInOut(0xff, 0xff, 0x00, 0);
    colorAll(strip.Color(255, 255, 0), 50);
    strip.show();
  }
  else if (Event == PrintCancelled)
  {
    colorAll(strip.Color(255, 255, 0), 50);
    strip.show();
  }
  else if (Event == PrintPaused)
  {
    colorClose(strip.Color(0, 255, 0), 50);
    colorClose(strip.Color(0, 0, 255), 50);
    colorClose(strip.Color(0, 255, 0), 50);
    colorClose(strip.Color(0, 0, 255), 50);
    colorClose(strip.Color(0, 255, 0), 50);
    colorClose(strip.Color(0, 0, 255), 50);
    colorClose(strip.Color(0, 255, 0), 50);
    colorClose(strip.Color(0, 0, 255), 50);
    colorClose(strip.Color(0, 255, 0), 50);
    colorClose(strip.Color(0, 0, 255), 50);
    colorClose(strip.Color(0, 255, 0), 50);
    colorClose(strip.Color(0, 0, 255), 50);
  }
  else if (Event == PrintResumed)
  {
    colorWipe(strip.Color(0, 255, 0), 50);
    colorAll(strip.Color(255, 255, 255), 50);
    strip.show();
  }
  else if (Event == Home)
  {
    colorClose(strip.Color(255, 127, 0), 10);
    colorClose(strip.Color(0, 0, 0), 10);
    colorClose(strip.Color(255, 127, 0), 10);
    colorClose(strip.Color(0, 0, 0), 10);
    colorClose(strip.Color(255, 127, 0), 10);
    delay(3000);
    colorAll(strip.Color(255, 255, 255), 50);
    strip.show();
  }
  else if (Event == Waiting)
  {
    for(i=0; i<5; i++) {
      colorClose(strip.Color(0, 0, 255), 100);
      colorWipe(strip.Color(0, 0, 0), 100);
    }
  }
  else if (Event == Cooling)
  {
    FadeInOut(0x00, 0x00, 0xff, 25);
  }
  else if (Event == Alert)
  {
    for(i=0; i<3; i++) {
      colorCross(strip.Color(255, 0, 0), strip.Color(255, 127, 0), 100);
    }
  }
  else if (Event == EStop)
  {
    FadeInOut(0x0ff, 0x00, 0x00, 0);
    FadeInOut(0x0ff, 0x00, 0x00, 0);
    FadeInOut(0x0ff, 0x00, 0x00, 0);
    colorAll(strip.Color(255, 0, 0), 50);
    strip.show();
  }
  else if (Event == ToolChange)
  {
    colorCross(strip.Color(0, 255, 0), strip.Color(255, 0, 255), 50);
  }
}

void loop() {
}

// Set all pixels in the strip to a solid color, then wait (ms)
void colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color, wait (ms) after each one
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color starting from both ends, wait (ms) after each one
void colorClose(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<=strip.numPixels()/2; i++) {
    strip.setPixelColor(i, c);
    uint16_t j = strip.numPixels() - 1 - i;
    strip.setPixelColor(j, c);
    strip.show();
    delay(wait);
  }
}

void colorCross(uint32_t c, uint32_t c2, uint8_t wait) {
  for(uint16_t i=0; i<=strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    uint16_t j = strip.numPixels() - 1 - i;
    strip.setPixelColor(j, c2);
    strip.show();
    delay(wait);
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

void RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    // Fade IN
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      strip.show();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      strip.show();
      delay(3);
    }
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

void FadeInOut(byte red, byte green, byte blue, uint8_t wait){
  float r, g, b;
  
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(wait);
  }  
  
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(wait);
  }
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {

  for (int j=0; j<10; j++) {  //do 10 cycles of chasing

    for (int q=0; q < 3; q++) {

      for (int i=0; i < NUM_LEDS; i=i+3) {

        setPixel(i+q, red, green, blue);    //turn every third pixel on

      }

      showStrip();

     

      delay(SpeedDelay);

     

      for (int i=0; i < NUM_LEDS; i=i+3) {

        setPixel(i+q, 0,0,0);        //turn every third pixel off

      }

    }

  }

}