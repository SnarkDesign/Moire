/*

  Moire 1.0


  -- a basic moire program to display a moire screen saver on the heltec OLED.
  
  -- Made for a heltec esp32 with a screen 128x 64 px as determined by DISPLAY_WIDTH, DISPLAY_HEIGHT

  -- 
*/


// This example just provide basic function test;
// For more informations, please vist www.heltec.cn or mail to support@heltec.cn

#include "Arduino.h"
#include "heltec.h"

  // line points 
  uint8_t ix, jy, px, qy;

  // deltas moves up or down
  // moves up each point independently 
  // 
 // up if 1 or down if 0
  uint8_t ixdelta, jydelta, pxdelta, qydelta;

  // line color swap - every other line is black or white
  // could be variable :)
  uint8_t lastcolor = 0;


// Adapted from Adafruit_SSD1306
void drawLines() {

 // if a point exceed display limits, reverse delta
 // ix
 if (ix >= DISPLAY_WIDTH && ixdelta > 0) {
   ixdelta = 0;
 }
 else if (ix < 1 && ixdelta<1) {
   ixdelta = 1;
 }
 if (ixdelta > 0) ix++; else ix--;

 // jy
 if (jy >= DISPLAY_HEIGHT && jydelta > 0) {
   jydelta = 0;
 }
 else if (jy < 1 && jydelta < 1) {
   jydelta = 1;
 }
 if (jydelta > 0) jy++; else jy--;

// px
 if (px >= DISPLAY_WIDTH && pxdelta > 0) {
   pxdelta = 0;
 }
 else if (px < 1 && pxdelta < 1) {
   pxdelta = 1;
 }
 if (pxdelta > 0) px++; else px--;
 
// qy
 if (qy >= DISPLAY_HEIGHT && qydelta > 0) {
   qydelta = 0;
 }
 else if (qy < 1 && qydelta < 1) {
   qydelta = 1;
 }
 if (qydelta > 0) qy++; else qy--;


// random change to prevent boringly similar patterns

srand(time(NULL));
uint8_t rdelta = rand();
if (rdelta == 0 ) rdelta++; 

if(ix % rdelta == 1) {
if (ixdelta > 0  && ix < DISPLAY_WIDTH && ix > 0) ix++; else ix--;
 //if (ixdelta > 0) ixdelta=0; else ixdelta=1;
}
if(jy % rdelta == 1) {
 if (jydelta > 0 && jy < DISPLAY_HEIGHT && jy > 0) jy++; else jy--;
//if (jydelta > 0) jydelta=0; else jydelta=1;
}
if(px % rdelta == 1) {
 if (pxdelta > 0 && px < DISPLAY_WIDTH && px > 0) px++; else px--;
//if (pxdelta > 0) pxdelta=0; else pxdelta=1;
}
if(qy % rdelta == 1) {
 if (qydelta > 0 && qy < DISPLAY_HEIGHT && qy > 0) qy++; else qy--;
}

// reverse deltas if equal 
// although the patterns can be enjoyable

if( ix == px ){

    if (ixdelta == pxdelta) {
      if (ixdelta == 0) ixdelta=1; else ixdelta=0;
    }
}
if( jy == qy ){

    if (jydelta == qydelta) {
      if (jydelta == 0) jydelta=1; else jydelta=0;
    }
}

/* debug 
Serial.print(ix);Serial.print(" ");
Serial.print(jy);Serial.print(" ");
Serial.print(px);Serial.print(" ");
Serial.print(qy);Serial.print(" ");
Serial.println(rdelta);
*/

// swap colors to create the zebra
if(lastcolor == 0){
 Heltec.display->setColor(WHITE);
 lastcolor = 1;
}
else{
 Heltec.display->setColor(BLACK);
 lastcolor = 0;

}

Heltec.display->drawLine(ix, jy, px, qy);
Heltec.display->display();

}




void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  
  Heltec.display->setContrast(255);

}

void loop() {

 drawLines();
 delay(10);
}