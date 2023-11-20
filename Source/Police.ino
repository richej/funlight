float highlightPositions[NUM_LEDS_IN_ROW];

 void Police(int startLed, int numLeds, CRGB backgroundColor, CRGB highlightColor,
 bool clockwise,float lightSize)
 {
   
     int bgRed = backgroundColor.red;
     int bgGreen = backgroundColor.green;
     int bgBlue = backgroundColor.blue;

     //CRGB highlightColor = CRGB(red, green, blue);

    
    highlightPositions[startLed] = highlightPositions[startLed]+ ((clockwise?-1:1));

    if(highlightPositions[startLed]<0){
      highlightPositions[startLed] = 359;
    }
    else if(highlightPositions[startLed]>=360)
    {
      highlightPositions[startLed] = 0;
    }


    
    float currHighlightPos = highlightPositions[startLed]; 

    float beamSize= lightSize*(360/NUM_ROWS);

    CRGB targetArr[ NUM_ROWS ];
    for(int row=0;row<NUM_ROWS;row++)
    {
        float angle = row*(360.0/NUM_ROWS);
        float distToHighlight = abs(currHighlightPos-angle);
        float alternativeDistToHighlight1 = abs((currHighlightPos-360)-angle);
        float alternativeDistToHighlight2 = abs((currHighlightPos+360)-angle);
        
        if(alternativeDistToHighlight1 < distToHighlight){
          distToHighlight = alternativeDistToHighlight1;
        }

        if(alternativeDistToHighlight2 < distToHighlight){
          distToHighlight = alternativeDistToHighlight2;
        }

        int brightness = (beamSize-distToHighlight)*255.0/beamSize;

        if(brightness > 0){
          CRGB col = CRGB(bgRed, bgGreen, bgBlue);
          targetArr[row] = fadeTowardColor(col, highlightColor, brightness);
        }else{
          targetArr[row] = CRGB(bgRed, bgGreen, bgBlue);
        }
        
    }

    for(int row=0;row<NUM_ROWS;row++){
        for(int i=0;i<numLeds;i++){
            int currLed = row*NUM_LEDS_IN_ROW+i+startLed;
            setPixel(currLed,targetArr[row].red,targetArr[row].green,targetArr[row].blue);
        }
    }
    showStrip();

    
    
 }