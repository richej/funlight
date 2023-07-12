 CRGB targetArr[ NUM_LEDS ];
 CRGB sourceArr[ NUM_LEDS ];
 int currIter = 0;

 CRGB bgColor = CRGB(170,0,60);
 CRGB targetColor = CRGB(255,0,80);

 float lightSticks[12] = {-100,-20,-10,-1,-50,-55,-100,-20,-10,-1,-50,-55};
 int stickLenghts[12] = {2,5,1,3,1,1,2,5,1,3,1,1};
 float stickSpeeds[12] = {0.6,0.8,1.2,1,1.4,0.6,0.8,1.2,1,1.4};
 int numberOfSticks = sizeof(lightSticks)/sizeof(float);
 

void MyEffect(){
  if(currIter >= NUM_LEDS){
    currIter = 0;
  }
  EVERY_N_MILLISECONDS(5) {
    for(int i=0;i<NUM_LEDS;i++){
      targetArr[i] = fadeTowardColor(targetArr[i], sourceArr[i], 7);
    }
  }

  EVERY_N_MILLISECONDS(30) {
    int lightStickPos[numberOfSticks];
    
    for(int k=0;k<numberOfSticks;k++){

      lightSticks[k] = lightSticks[k]+1+abs(lightSticks[k])*0.01;
      lightStickPos[k] = lightSticks[k]*stickSpeeds[k];

      if(lightStickPos[k]>=NUM_LEDS){
        lightSticks[k] = -1*(int)random(100);
        lightStickPos[k] = -1;
        stickLenghts[k] = (int)random(1,6);
        float speed = random(100)/200.1;
        stickSpeeds[k] = speed+0.01;
        
      }
    }
    for(int i=0;i<NUM_LEDS;i++){
      bool show = false;
      for(int k=0;k<numberOfSticks;k++){
        if(show == false && (i <= lightStickPos[k] && i >= lightStickPos[k]-stickLenghts[k])){
          show = true;
        }
      }
      if(show){
        sourceArr[i] = targetColor;
      }else{
        sourceArr[i] = bgColor;
      }
    }

    // for(int i=0;i<NUM_LEDS;i++){
    //   if(i == currIter || i == currIter-1 || i == currIter-2 || i == currIter-3){
    //     sourceArr[i] = targetColor;
    //   }else{
    //     sourceArr[i] = bgColor;        
    //   }
    // }
    currIter++;
  }

  for(int i=0;i<NUM_LEDS;i++){
    setPixel(i,targetArr[i].red,targetArr[i].green,targetArr[i].blue);
  }
  showStrip();
}

CRGB fadeTowardColor( CRGB& cur, const CRGB& target, uint8_t amount)
{
  nblendU8TowardU8( cur.red, target.red, amount);
  nblendU8TowardU8( cur.green, target.green, amount);
  nblendU8TowardU8( cur.blue, target.blue, amount);
  return cur;
}

void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount)
{
  if( cur == target) return;

  if( cur < target ) {
    uint8_t delta = target - cur;
    delta = scale8_video( delta, amount);
    cur += delta;
  } else {
    uint8_t delta = cur - target;
    delta = scale8_video( delta, amount);
    cur -= delta;
  }
}