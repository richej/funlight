 CRGB targetArr[ NUM_LEDS ];
 CRGB sourceArr[ NUM_LEDS ];


 CRGB bgColor = CRGB(170,0,60);
 CRGB targetColor = CRGB(255,0,80);

 float lightSticks[12] = {-100,-20,-10,-1,-50,-55,-100,-20,-10,-1,-50,-55};
 int stickLenghts[12] = {2,5,1,3,1,1,2,5,1,3,1,1};
 float stickSpeeds[12] = {0.6,0.8,1.2,1,1.4,0.6,0.8,1.2,1,1.4};
 int numberOfSticks = sizeof(lightSticks)/sizeof(float);
 

void MyEffect(int contrast){

  EVERY_N_MILLISECONDS(5) {
    for(int i=0;i<NUM_LEDS;i++){
      targetArr[i] = fadeTowardColor(targetArr[i], sourceArr[i], contrast);
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
    for(int row=0;row<NUM_ROWS;row++){
      for(int i=0;i<NUM_LEDS_IN_ROW;i++){
        bool show = false;
        for(int k=0;k<numberOfSticks;k++){
          if(show == false && (i <= lightStickPos[k] && i >= lightStickPos[k]-stickLenghts[k])){
            show = true;
          }
        }
        if(show){
          sourceArr[i+row*NUM_LEDS_IN_ROW] = targetColor;
        }else{
          sourceArr[i+row*NUM_LEDS_IN_ROW] = bgColor;
        }
      }
    }
      // for(int i=0;i<NUM_LEDS;i++){
    //   bool show = false;
    //   for(int k=0;k<numberOfSticks;k++){
    //     if(show == false && (i <= lightStickPos[k] && i >= lightStickPos[k]-stickLenghts[k])){
    //       show = true;
    //     }
    //   }
    //   if(show){
    //     sourceArr[i] = targetColor;
    //   }else{
    //     sourceArr[i] = bgColor;
    //   }
    // }
  }

  for(int i=0;i<NUM_LEDS;i++){
    setPixel(NUM_LEDS-i,targetArr[i].red,targetArr[i].green,targetArr[i].blue);
  }
  showStrip();
}
