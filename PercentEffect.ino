void PercentEffect(int percent,CRGB& col){  
  for(int i=0;i<NUM_LEDS;i++){
    float currPercent = 100/NUM_LEDS*i;
    if(currPercent <= percent){
      setPixel(i,col.red,col.green,col.blue);
    }else{
      setPixel(i,0,0,0);
    }

  }
  showStrip();
}