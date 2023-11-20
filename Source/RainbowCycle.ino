void rainbowCycle(int SpeedDelay,int pos) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(int row=0;row<NUM_ROWS;row++){
      for(i=0; i< NUM_LEDS_IN_ROW; i++) {
        c=Wheel(((i * 256 / NUM_LEDS_IN_ROW) + j) & 255);
        setPixel(NUM_LEDS_IN_ROW-i+row*NUM_LEDS_IN_ROW, *c, *(c+1), *(c+2));
        Serial.println(i);
        if(pos != getCurrentEffect()){
          return;
        }
      }
      showStrip();
      waitFor(SpeedDelay);
    }
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}