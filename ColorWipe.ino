


void colorWipe(byte red, byte green, byte blue, int SpeedDelay,int pos) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      setPixel(i, red, green, blue);
      showStrip();
      delay(SpeedDelay);

       
      if(pos != getCurrEffect())return;
        
  }
}