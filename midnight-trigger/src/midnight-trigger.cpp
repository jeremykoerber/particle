/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "/Users/jeremykoerber/code/particle/midnight-trigger/src/midnight-trigger.ino"
/*
 * Project midnight-trigger
 * Description:
 * Author:
 * Date:
 */

#include "Particle.h"

void setup();
void loop();
#line 10 "/Users/jeremykoerber/code/particle/midnight-trigger/src/midnight-trigger.ino"
int last_day = Time.day(); // just initializing the variable so we can use it in the loop without resetting it every time the loop repeats
bool new_day = false; // a boolean we can flip to true if it's a new day

void setup() {
}


void loop() {
  int day = Time.day(); // an integer to tell us what day of the month it is currently
  if (day > last_day)
  {
    new_day = true; // it's a new dawn, it's a new day.
    last_day = Time.day(); // update last_day to today's date
  }
  if (new_day == true)
  {
    // do your stuff here that you want to run every time the day of month is incremented and then wait an hour
    delay(3600000); // 1 hour delay in ms
  }
}