#include <Adafruit_NeoPixel.h>

#define s1PIN 6

#define pin1 3
#define pin2 4

// Parameter 1 = number of pixels in strip1
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(15, s1PIN, NEO_GRB + NEO_KHZ800);

const uint8_t del = 50; // Standard delay time

uint8_t currentPat;

void setup() {

  // Start the pins from the robot as input (they are unpredictable otherwise)
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);

  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'
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
  if (c) colorWipe(strip1.Color(0,   255,   0), del*2); // Green
  else theaterChase(strip1.Color(  127,   0, 0), del*2); // Red
}

// idle
void idle() {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, strip1.Color(255,140,0));
    strip1.show();
    delay(del/2);
  }
  for(uint16_t i=strip1.numPixels(); i>0; i--) {
    strip1.setPixelColor(i, strip1.Color(0,0,0));
    strip1.show();
    delay(del/2);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, c);
    strip1.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colours on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip1.show();

      delay(wait);

      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, 0);        //turn every third pixel off
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
  return digitalRead(pin1) + (digitalRead(pin2)*2);
}



