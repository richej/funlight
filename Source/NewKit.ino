void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay,int pos){
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay,pos);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay,pos);
 //  if(pos != getCurrEffect())return; 
  //OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
   // if(pos != getCurrEffect())return;  
  //CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  //  if(pos != getCurrEffect())return;
  //LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  //  if(pos != getCurrEffect())return;
 // RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  //  if(pos != getCurrEffect())return;
 // OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  //  if(pos != getCurrEffect())return; 
  //CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i =((NUM_LEDS-EyeSize)/2); i>=0; i--) {
    setAll(255,255,255);
    
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue); 
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
    
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2); i++) {
    setAll(255,255,255);
    
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue); 
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
    
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay, int pos) {
  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    if(pos != getCurrEffect())return;  
    setAll(255,255,255);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay, int pos) {
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    if(pos != getCurrEffect())return;  
    setAll(255,255,255);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}