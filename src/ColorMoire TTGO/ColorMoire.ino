/*
  An example showing rainbow colours on a 160x128 TFT LCD screen
  and to show a basic example of font use.

  This example plots the text in a sprite then pushes the sprite to the
  TFT screen.
  
  Make sure all the display driver and pin comnenctions are correct by
  editting the User_Setup.h file in the TFT_eSPI library folder.

  Note that yield() or delay(0) must be called in long duration for/while
  loops to stop the ESP8266 watchdog triggering.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
*/

#define IWIDTH  240
#define IHEIGHT 128
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 128

#include <TFT_eSPI.h> // Graphics and font library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

TFT_eSprite img = TFT_eSprite(&tft);

 // line points 
  uint8_t ix, jy, px, qy;

  // deltas moves up or down
  // moves up each point independently 
  // 
  //if 1 or down if 0
  uint8_t ixdelta, jydelta, pxdelta, qydelta;

  // line color swap - every other line is black or white
  // could be variable :)
  uint8_t lastcolor = 0;


unsigned long targetTime = 0;
byte red = 31;
byte green = 0;
byte blue = 0;
byte state = 0;
unsigned int colour = red << 11;

void setup(void) {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  img.createSprite(IWIDTH, IHEIGHT);
  img.fillSprite(TFT_BLACK);

  targetTime = millis() + 1000;
}

void loop() {
    if (targetTime < millis()) {
      targetTime = millis() + 100;//10000;
      drawLines();
    //  delay(10);
    }
  /*

    // The standard ADAFruit font still works as before
    img.setTextColor(TFT_BLACK);
    img.setCursor (12, 5);
    img.print("Original ADAfruit font!");

    // The new larger fonts do not use the .setCursor call, coords are embedded
    img.setTextColor(TFT_BLACK, TFT_BLACK); // Do not plot the background colour

    // Overlay the black text on top of the rainbow plot (the advantage of not drawing the backgorund colour!)
    img.drawCentreString("Font size 2", 80, 14, 2); // Draw text centre at position 80, 12 using font 2

    //img.drawCentreString("Font size 2",81,12,2); // Draw text centre at position 80, 12 using font 2

    img.drawCentreString("Font size 4", 80, 30, 4); // Draw text centre at position 80, 24 using font 4

    img.drawCentreString("12.34", 80, 54, 6); // Draw text centre at position 80, 24 using font 6

    img.drawCentreString("12.34 is in font size 6", 80, 92, 2); // Draw text centre at position 80, 90 using font 2

    // Note the x position is the top left of the font!

    // draw a floating point number
    float pi = 3.14159; // Value to print
    int precision = 3;  // Number of digits after decimal point
    int xpos = 50;      // x position
    int ypos = 110;     // y position
    int font = 2;       // font number only 2,4,6,7 valid. Font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 0 : a p m
    xpos += img.drawFloat(pi, precision, xpos, ypos, font); // Draw rounded number and return new xpos delta for next print position
    img.drawString(" is pi", xpos, ypos, font); // Continue printing from new x position

    img.pushSprite(0, 0);
  }*/

}

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
 //Heltec.display->setColor(WHITE);
 lastcolor = 1;
}
else{
 //Heltec.display->setColor(BLACK);
 lastcolor = 0;

}


    // Colour changing state machine
    for (int i = 0; i < IWIDTH; i++) {
     // img.drawLine(i, 0, img.height(), colour);
      switch (state) {
        case 0:
          green += 2;
          if (green == 64) {
            green = 63;
            state = 1;
          }
          break;
        case 1:
          red--;
          if (red == 255) {
            red = 0;
            state = 2;
          }
          break;
        case 2:
          blue ++;
          if (blue == 32) {
            blue = 31;
            state = 3;
          }
          break;
        case 3:
          green -= 2;
          if (green == 255) {
            green = 0;
            state = 4;
          }
          break;
        case 4:
          red ++;
          if (red == 32) {
            red = 31;
            state = 5;
          }
          break;
        case 5:
          blue --;
          if (blue == 255) {
            blue = 0;
            state = 0;
          }
          break;
      }
      colour = red << 11 | green << 5 | blue;
    }
    Serial.println(colour);
//Heltec.display->drawLine(ix, jy, px, qy);
img.drawLine(ix, jy, px, qy, colour);
//Heltec.display->display();

    img.pushSprite(0, 0);


}


