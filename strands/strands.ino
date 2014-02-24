#include <Adafruit_NeoPixel.h>

#define MidPIN 6
#define Side1Pin 10
#define Side2Pin 11
//#define s4PIN 9
#define s5PIN 5

#define SignalingPin1 3
#define SignalingPin2 4

// Parameter 1 = number of pixels in strip1
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel MidStrip = Adafruit_NeoPixel(15, MidPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SideStrip1 = Adafruit_NeoPixel(15, Side1Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SideStrip2 = Adafruit_NeoPixel(15, Side2Pin, NEO_GRB + NEO_KHZ800);


const uint8_t del = 50; // Standard delay time

void setup() {

  // Start the signaling pins from the robot as input (they are unpredictable otherwise)
  pinMode(SignalingPin1, INPUT);
  pinMode(SignalingPin2, INPUT);

  MidStrip.begin();
  SideStrip1.begin();
  SideStrip2.begin();

  MidStrip.show(); // Initialize all pixels to 'off'
  SideStrip1.show();
  SideStrip2.show();
}

void loop() {
  // switch on codes from robot
  // 0: #SWAG (so swags by default)
  // 1: Red (or team color)
  // 2: Yellow
  // 3: Green (Catch ready)
  switch (getValue()) {
    case 0:
      swag();
      break;
    case 1:
      theaterChase(MidStrip.Color(  127,   0, 0), del*2); // Red
      break;
    case 2:
      colorWipe(MidStrip.color(255, 140, 0), del*2); // Yellow
      break;
    case 3:
      colorWipe(MidStrip.Color(0,   255,   0), del*2); // Green
      break;
  }
}

// #SWAG
void swag() {
  // Hopefully pretty
  rainbow(2);
  rainbowCycle(5);
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  //Add lights from bottom/middle
  for(uint8_t i=0; i<strip1.numPixels(); i++) {
    MidStrip.setPixelColor(6+i, c);
    MidStrip.setPixelColor(6-i, c);
    SideStrip1.setPixelColor(i, c);
    SideStrip2.setPixelColor(i, c);

    MidStrip.show();
    SideStrip1.show();
    SideStrip2.show();
    delay(del/3);
  }
  //Remove lights from top/outside
  for(uint8_t i=strip1.numPixels(); i>0; i--) {
    MidStrip.setPixelColor(6-i, strip1.Color(0,0,0));
    MidStrip.setPixelColor(6+i, strip1.Color(0,0,0));
    SideStrip1.setPixelColor(i, strip1.Color(0,0,0));
    SideStrip2.setPixelColor(i, strip1.Color(0,0,0));
    MidStrip.show();
    SideStrip1.show();
    SideStrip2.show();
    delay(del/3);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      MidStrip.setPixelColor(i, Wheel((i+j) & 255));
      SideStrip1.setPixelColor(i, Wheel((i+j) & 255));
      SideStrip2.setPixelColor(i, Wheel((i+j) & 255));
    }
    MidStrip.show();
    SideStrip1.show();
    SideStrip2.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colours on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      MidStrip.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
      SideStrip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
      SideStrip2.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
    }
    MidStrip.show();
    SideStrip1.show();
    SideStrip2.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<5; j++) {  //do 5 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip1.numPixels(); i=i+3) {
        MidStrip.setPixelColor(i+q, c);    //turn every third pixel on
        SideStrip1.setPixelColor(i+q, c);    //turn every third pixel on
        SideStrip2.setPixelColor(i+q, c);    //turn every third pixel on
      }
      MidStrip.show();
      SideStrip1.show();
      SideStrip2.show();

      delay(wait);

      for (int i=0; i < strip1.numPixels(); i=i+3) {
        MidStrip.setPixelColor(i+q, 0);        //turn every third pixel off
        SideStrip1.setPixelColor(i+q, 0);        //turn every third pixel off
        SideStrip2.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a colour value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return MidStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return MidStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return MidStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// Returns an integer version of the signal from the robot
uint8_t getValue() {
  return (digitalRead(SignalingPin1)==HIGH)+(2*(digitalRead(SignalingPin2)==HIGH));
}



