#include <Adafruit_NeoPixel.h>

#define s1PIN 6
#define s2PIN 10
#define s3PIN 11
//#define s4PIN 9
#define s5PIN 5

#define pin1 3
#define pin2 4

// Parameter 1 = number of pixels in strip1
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(15, s1PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(15, s2PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(15, s3PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel //strip4 = Adafruit_NeoPixel(15, s4PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(15, s5PIN, NEO_GRB + NEO_KHZ800);


const uint8_t del = 50; // Standard delay time

void setup() {

  // Start the pins from the robot as input (they are unpredictable otherwise)
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);

  strip1.begin();
  strip2.begin();
  strip3.begin();
  ////strip4////strip4.begin();
  strip5.begin();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.show();
  strip3.show();
  ////strip4.show();
  strip5.show();
}

void loop() {
  // switch on codes from robot
  // 0: not ready to catch
  // 1: ready to catch
  // 2: idle
  // 3: #SWAG
  switch (getValue()) {
    case 0:
      catchLight(false);
      break;
    case 1:
      catchLight(true);
      break;
    case 2:
      idle();
      break;
    case 3:
      swag();
      break;
  }
}

// #SWAG
void swag() {
  // Hopefully pretty
  rainbow(2);
  rainbowCycle(5);
}

// catching related patterns, takes a bool if we are ready to catch
void catchLight(boolean c) {
  if (c) {
    colorWipe(strip1.Color(0,   255,   0), del*2); // Green
  }
  else {
    theaterChase(strip1.Color(  127,   0, 0), del*2); // Red
  }
}

// idle
void idle() {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(6+i, strip1.Color(255,140,0));
    strip1.setPixelColor(6-i, strip1.Color(255,140,0));
    strip2.setPixelColor(i, strip1.Color(255,140,0));
    strip3.setPixelColor(i, strip1.Color(255,140,0));
    ////strip4.setPixelColor(i, strip1.Color(255,140,0));
    strip5.setPixelColor(i, strip1.Color(255,140,0));
    strip1.show();
    strip2.show();
    strip3.show();
    ////strip4.show();
    strip5.show();
    delay(del);
  }
  for(uint16_t i=strip1.numPixels(); i>0; i--) {
    strip1.setPixelColor(6-i, strip1.Color(0,0,0));
    strip1.setPixelColor(6+i, strip1.Color(0,0,0));
    strip2.setPixelColor(i, strip1.Color(0,0,0));
    strip3.setPixelColor(i, strip1.Color(0,0,0));
    ////strip4.setPixelColor(i, strip1.Color(0,0,0));
    strip5.setPixelColor(i, strip1.Color(0,0,0));
    strip1.show();
    strip2.show();
    strip3.show();
    ////strip4.show();
    strip5.show();
    delay(del);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint8_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(6+i, c);
    strip1.setPixelColor(6-i, c);
    strip2.setPixelColor(i, c);
    strip3.setPixelColor(i, c);
    ////strip4.setPixelColor(i, c);
    strip5.setPixelColor(i, c);
    strip1.show();
    strip2.show();
    strip3.show();
    //strip4.show();
    strip5.show();
    delay(del/3);
  }
  for(uint8_t i=strip1.numPixels(); i>0; i--) {
    strip1.setPixelColor(6-i, strip1.Color(0,0,0));
    strip1.setPixelColor(6+i, strip1.Color(0,0,0));
    strip2.setPixelColor(i, strip1.Color(0,0,0));
    strip3.setPixelColor(i, strip1.Color(0,0,0));
    //strip4.setPixelColor(i, strip1.Color(0,0,0));
    strip5.setPixelColor(i, strip1.Color(0,0,0));
    strip1.show();
    strip2.show();
    strip3.show();
    //strip4.show();
    strip5.show();
    delay(del/3);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel((i+j) & 255));
      strip2.setPixelColor(i, Wheel((i+j) & 255));
      strip3.setPixelColor(i, Wheel((i+j) & 255));
      //strip4.setPixelColor(i, Wheel((i+j) & 255));
      strip5.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip1.show();
    strip2.show();
    strip3.show();
    //strip4.show();
    strip5.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colours on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
      strip2.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
      strip3.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
      //strip4.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
      strip5.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
    }
    strip1.show();
    strip2.show();
    strip3.show();
    //strip4.show();
    strip5.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<5; j++) {  //do 5 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, c);    //turn every third pixel on
        strip2.setPixelColor(i+q, c);    //turn every third pixel on
        strip3.setPixelColor(i+q, c);    //turn every third pixel on
        //strip4.setPixelColor(i+q, c);    //turn every third pixel on
        strip5.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip1.show();
      strip2.show();
      strip3.show();
      //strip4.show();
      strip5.show();

      delay(wait);

      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, 0);        //turn every third pixel off
        strip2.setPixelColor(i+q, 0);        //turn every third pixel off
        strip3.setPixelColor(i+q, 0);        //turn every third pixel off
        //strip4.setPixelColor(i+q, 0);        //turn every third pixel off
        strip5.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a colour value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// Returns a decimal version of the signal from the robot
uint8_t getValue() {
  return (digitalRead(pin1)==HIGH)+(2*(digitalRead(pin2)==HIGH));
}



