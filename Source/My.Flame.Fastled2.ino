#include "FastLED.h"
#include <Encoder.h>



// NEOPIXEL https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
#define PIN D4
#define NUM_LEDS 77

// ENCODER https://blog.squix.org/2016/05/esp8266-peripherals-ky-040-rotary-encoder.html
Encoder myEnc(D1, D2);


long oldPosition  = -999;
boolean isButtonPressed = false;
long lastUpdateMillis = 0;
int currEffect = 0;
int currentPercentBarValue = 0;
CRGB currentPercentBarColor = CRGB(255,255,255);

#define BRIGHTNESS  255

void handleKey() {
  isButtonPressed = true;  
}


CRGB leds[NUM_LEDS];


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("starting");
  FastLED.addLeds<NEOPIXEL, 4>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(D3, INPUT_PULLUP);
  attachInterrupt(D3, handleKey, RISING);

}

int getCurrEffect(){
  return abs(myEnc.read())/2%12;
}

void loop() {
   
  long newPosition = abs(myEnc.read());
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    currEffect = getCurrEffect();
    Serial.println(currEffect);
    //Serial.println(newPosition);
  }

   // software debounce
  if (isButtonPressed && millis() - lastUpdateMillis > 50) {
    isButtonPressed = false;
    lastUpdateMillis = millis();
    // Reset the counter
    myEnc.write(0);
  }


  switch(currEffect){
    case 10:
      rainbowCycle(25,currEffect);
      break;
    case 1:
      Fire(65,160,50);
      break;
    case 2:
      MeteorRain(0xff,0xff,0xff,10, 64, true, 10,currEffect);
      break;
    case 3:
      Noise();
      break;
    case 4:
      NewKITT(0xff, 0, 0xff, 8, 10, 50,currEffect);
      break;
    case 5:
      ripple();
      break;
    case 6:
      Sparkle(0xff, 0xff, 0xff, 10);
      break;
    case 7:
      setAll(0xff,0xdd,0xaa); 
      break;
    case 8:
      colorWipe(0xff,0x00,0xff, 25,currEffect);
      colorWipe(0xff,0xff,0xff, 50,currEffect);
      break;
    case 9:
      setAll(0xff,0,0xd4); // rosa ;)
      break;
    case 0:
      MyEffect();
      break;
    case 100:
      PercentEffect(currentPercentBarValue,currentPercentBarColor);
      break;
    default:
      break;
  }
  

  

}



void showStrip() {
   FastLED.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].setRGB( red, green, blue);
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  FastLED.show();
}