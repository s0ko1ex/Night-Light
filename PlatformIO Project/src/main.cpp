#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
    #include <avr/power.h>
#endif

#define N 15

uint32_t Wheel(byte WheelPos);

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(N, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(2, 5, NEO_RGB + NEO_KHZ800);

void setup() {
    strip_1.begin();
    strip_2.begin();
}

void loop() {
    uint16_t i, j;

    for(j = 0; j < 256; j++) { // 5 cycles of all colors on wheel
        for(i = 0; i < strip_1.numPixels(); i++) {
            strip_1.setPixelColor(i, Wheel(((i * 256 / (strip_1.numPixels() + strip_2.numPixels())) + j) & 255));
        }

        for(i = strip_1.numPixels(); i < strip_1.numPixels() + strip_2.numPixels(); i++) {
            strip_2.setPixelColor(i - strip_1.numPixels(), Wheel(((i * 256 / (strip_1.numPixels() + strip_2.numPixels())) + j) & 255));
        }

        strip_1.show();
        strip_2.show();

        delay(20);
    }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip_1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip_1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip_1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}