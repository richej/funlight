void FireInRows(int Cooling, int Sparking, int SpeedDelay)
{
    static byte heat[NUM_LEDS];
    int cooldown;

    for(int row=0;row<NUM_ROWS;row++)
    {
        // Step 1.  Cool down every cell a little
        for( int i = 0; i < NUM_LEDS_IN_ROW; i++) {
          int currLed = row*NUM_LEDS_IN_ROW+i;
          cooldown = random(0, ((Cooling * 10) / NUM_LEDS_IN_ROW) + 2);
          
          if(cooldown>heat[currLed]) {
            heat[currLed]=0;
          } else {
            heat[currLed]=heat[currLed]-cooldown;
          }
        }
    }

    for(int row=0;row<NUM_ROWS;row++)
    {
        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( int k= NUM_LEDS_IN_ROW - 1; k >= 2; k--) {
          int currLed = row*NUM_LEDS_IN_ROW+k;
          heat[currLed] = (heat[currLed - 1] + heat[currLed - 2] + heat[currLed - 2]) / 3;
        }
    }

    for(int row=0;row<NUM_ROWS;row++)
    {
      for(int row=0;row<NUM_ROWS;row++)
      {
        // Step 3.  Randomly ignite new 'sparks' near the bottom
        if( random(255) < Sparking ) {
          int y = random(4)+row*NUM_LEDS_IN_ROW;
          heat[y] = heat[y] + random(160,200);
          //heat[y] = random(160,255);
        }
      }
    }

    for(int row=1;row<=NUM_ROWS;row++)
    {
       int currLed = row*NUM_LEDS_IN_ROW;
       heat[currLed] = 0;
    }

     // Step 4.  Convert heat to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      setPixelHeatColor(j, heat[NUM_LEDS-j] );
    }

    showStrip();
    waitFor(SpeedDelay);
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}



void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}