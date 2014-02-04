#include <Adafruit_NeoPixel.h>

#define s1PIN 6

#define testPin 3
#define readyPin 4

// Parameter 1 = number of pixels in strip1
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(30, s1PIN, NEO_GRB + NEO_KHZ800);

const uint8_t del = 1; // Standard delay time

uint16_t time = 50; // pattern timer
uint8_t currentPat;

void setup() {
  
  // Start the pins from the robot as input (they are unpredictable otherwise)
  pinMode(testPin, INPUT);
  
  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (time==50) currentPat = random(2);
  
  if(digitalRead(!readyPin)) {
    // 
    switch (currentPat) {
      case 0:
        colorWipe(strip1.Color(0,255,0), del);
        break;
      case 1:
        theaterChase(strip1.Color(0,255,0),del);
        break;
    }
    time++;
  }
  if(digitalRead(testPin)) {
    // Example
    colorWipe(strip1.Color(255, 0, 0), 50); // Red
    colorWipe(strip1.Color(0, 255, 0), 50); // Green
    colorWipe(strip1.Color(0, 0, 255), 50); // Blue
    // Send a theater chase in...
    theaterChase(strip1.Color(127, 127, 127), 50); // White
    theaterChase(strip1.Color(127,   0,   0), 50); // Red
    theaterChase(strip1.Color(  0,   0, 127), 50); // Blue

    // Hopefully pretty
    rainbow(20);
    rainbowCycle(20);
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


