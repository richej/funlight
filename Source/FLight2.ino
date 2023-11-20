
#include <FastLED.h>
#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Preferences.h>

#define PIN_IN1 D2
#define PIN_IN2 D1
#define BUTTON_ENCODER_PIN D3
#define LED_PWM_PIN D5
#define BUTTON_FORWARD_PIN D6
#define BUTTON_BACKWARD_PIN D7
#define DATA_PIN D4
#define COLOR_ORDER GRB
#define NUM_LEDS_IN_ROW 29
#define NUM_LEDS 145
#define NUM_ROWS 5



Preferences preferences;
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::FOUR3);
CRGBArray<NUM_LEDS> leds;
int currEffect = 0;
int encoderPos = 0;
int brightnessArr[15]={1,2,3,5,7,10,15,25,40,60,90,130,180,220,255};
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;  
int ctr = 0;
int forwardState = 1;
int backwardState = 1;
int encoderButtonState = 1;

void setup() {
  Serial.begin(115200);

  //Create a namespace
  preferences.begin("funlight", false);

  currEffect = preferences.getInt("currEffect", 0); 
  encoderPos = preferences.getInt("encoderPos", 7); 
  encoder.setPosition(encoderPos);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //FastLED.addLeds<WS2812, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear();  // clear all pixel data
  FastLED.show();
  pinMode(BUTTON_FORWARD_PIN, INPUT_PULLUP);
  pinMode(BUTTON_BACKWARD_PIN, INPUT_PULLUP);
  pinMode(BUTTON_ENCODER_PIN, INPUT);
  updateBrightness();
}



int numEffects = 15;

void loop() 
{


  switch (currEffect)
  {
    case 0:
      FastLED.clear();  // clear all pixel data
      FastLED.show();
    // Default effect is the white LED stripe. We set its brightness in SetBrightness(). So nothing to do here...
    break;
    case 1:
      FireInRows(65,10,24);
      break;
    case 2:
      ripple();
      break;
    case 3:
      Sparkle(0xff,0xff,0xff,15);
      break;
    case 4:
      Sparkle(0xff,0xff,0x00,15);
      break;
    case 5:
      Sparkle(0xff,0x00,0x00,15);
      break;
    case 6:
      Police(0,7,CRGB(0,0,0),CRGB(0,58,255),false,1.5);
      Police(7,7,CRGB(0,58,255),CRGB(0,0,0),true,1.5);
      Police(14,7,CRGB(0,0,0),CRGB(255,255,0),false,1.5);
      Police(21,8,CRGB(255,255,0),CRGB(0,0,0),true,1.5);
      break;
    case 7:
      Police(0,7,CRGB(0,0,0),CRGB(0,255,0),false,1.5);
      Police(7,7,CRGB(255,0,0),CRGB(0,0,0),true,1.5);
      Police(14,7,CRGB(0,0,0),CRGB(0,0,255),false,1.5);
      Police(21,8,CRGB(255,255,0),CRGB(0,0,0),true,1.5);
      break;
    case 8:
      Police(0,7,CRGB(0,0,0),CRGB(255,0,125),false,1.5);
      Police(7,7,CRGB(0,125,255),CRGB(0,0,0),true,1.5);
      Police(14,7,CRGB(0,0,0),CRGB(0,255,125),false,1.5);
      Police(21,8,CRGB(125,255,0),CRGB(0,0,0),true,1.5);
      break;
    case 9:
      RunningLights(0xff,0x00,0xff,25,currEffect);
      break;
    case 10:
      RunningLights(0x00,0xff,0x22,25,currEffect);
      break;
    case 11:
      RunningLights(0x00,0x22,0xff,25,currEffect);
      break;
    case 12:
      setAll(0x00,0x00,0xff);
      showStrip();
      break;
    case 13:
      setAll(0x00,0xff,0x00);
      showStrip();
      break;
    case 14:
      setAll(0xff,0x00,0x00);
      showStrip();
      break;
    default:
      break;
  }
  checkButtonStates();
  setBrightness();
  
}

void waitFor(int myMillis)
{
  unsigned long startMillis = millis(); 
  while((millis()-startMillis)<myMillis){
    checkButtonStates();
    setBrightness();
    delay(2);
  }
}



int getCurrentEffect(){
  checkButtonStates();
  setBrightness();
  return currEffect;
}

void checkButtonStates()
{
  int curr_forwardState = digitalRead(BUTTON_FORWARD_PIN);
  int curr_backwardState = digitalRead(BUTTON_BACKWARD_PIN);
  int curr_encoderButtonState = digitalRead(BUTTON_ENCODER_PIN);

  int oldEffect = currEffect;
  if(curr_forwardState != forwardState && (millis() - lastDebounceTime) > debounceDelay){
    lastDebounceTime = millis();
    forwardState = curr_forwardState;
    if(forwardState == 0){
      currEffect++;
      Serial.print("currEffect: ");
      Serial.println(currEffect);
    }
  }

  if(curr_backwardState != backwardState && (millis() - lastDebounceTime) > debounceDelay){
    lastDebounceTime = millis();
    backwardState = curr_backwardState;
    if(backwardState == 0){
      currEffect--;
      Serial.print("currEffect: ");
      Serial.println(currEffect);
    }
  }

  if(curr_encoderButtonState != backwardState && (millis() - lastDebounceTime) > debounceDelay){
    lastDebounceTime = millis();
    encoderButtonState = curr_encoderButtonState;
    if(encoderButtonState == 0){
      currEffect = 0;
      Serial.print("currEffect: ");
      Serial.println(currEffect);
    }
  }

  if(currEffect < 0){
    currEffect = numEffects-1;
  }
  if(currEffect >= numEffects){
    currEffect = 0;
  }

  if(oldEffect != currEffect){
    Serial.print("Changed effect to: ");
    Serial.println(currEffect);
    preferences.putInt("currEffect", currEffect);
    FastLED.clear();
    updateBrightness();
  }
}




/// @brief Brightness can be adjusted with the rotary encoder
void setBrightness(){
  encoder.tick();

  if(encoder.getPosition()<0){
    encoder.setPosition(0);
  }

  if(encoder.getPosition()>=15){
    encoder.setPosition(14);
  }
  

  if (encoderPos != encoder.getPosition()) {
    encoderPos = encoder.getPosition();
    Serial.print("pos:");
    Serial.println(encoder.getPosition());
    
    preferences.putInt("encoderPos", encoderPos);
    updateBrightness();
   
    showStrip();
  }
} 

void updateBrightness(){
   int brightnessPos = encoder.getPosition();
    if(brightnessPos < 0){
      brightnessPos = 0;
    }else if(brightnessPos>=15){
      brightnessPos = 14;
    }

    if(currEffect == 0){
      analogWrite(LED_PWM_PIN,255- brightnessArr[brightnessPos]);
      FastLED.clear();
      Serial.println("RGB-Leds: off");
    }else{
      analogWrite(LED_PWM_PIN, 255);
      FastLED.setBrightness(brightnessArr[brightnessPos]);
      Serial.println("RGB-Leds: on");
    }
    showStrip();
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

void showStrip() {
   FastLED.show();
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