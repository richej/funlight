
void MeteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay,int pos) {  
  setAll(0,0,0);
  

    for(int i = 0; i < NUM_LEDS_IN_ROW*2; i++) {
    
      // fade brightness all LEDs one step
      for(int j=0; j<NUM_LEDS_IN_ROW; j++) {
        if( (!meteorRandomDecay) || (random(10)>5) ) {
          for(int row=0;row<NUM_ROWS;row++){             
            fadeToBlack(NUM_LEDS-(j+row*NUM_LEDS_IN_ROW), meteorTrailDecay );     
          }
          if(pos != getCurrentEffect())return; 
        }
      }
      
      // draw meteor
      for(int j = 0; j < meteorSize; j++) {
        if( ( i-j <NUM_LEDS_IN_ROW) && (i-j>=0) ) {
          for(int row=0;row<NUM_ROWS;row++){  
            setPixel((NUM_LEDS-(i+row*NUM_LEDS_IN_ROW))-(NUM_LEDS-(j+row*NUM_LEDS_IN_ROW)), red, green, blue);
          }

          if(pos != getCurrentEffect())return; 

        } 
      }
    
      showStrip();
      waitFor(SpeedDelay);
    }
  }


void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=3)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=3)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=3)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}