#include "FastLED.h"
#define DATA_PIN 3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 72
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 96
String inString = "";

int color;
int brightness;
bool brightnessLow;
void setup() {
  brightnessLow = false;
  brightness = 0;
  color = 0;
  Serial.begin(9600);
  delay(3000); 
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // initializes LED strip
  FastLED.setBrightness(BRIGHTNESS);// global brightness

}

void loop(){
  //read serial input
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (inChar == '\n') {
      //If it sees a new line, it converts everthing it has seen to an integer,representing how bright the LEDs should be
      Serial.println(inString);
      brightness = inString.toInt();
      inString = "";
    }
    else if (isAscii(inChar)) {
      inString += (char)inChar;
    }
  }

  //Change the color if the sound drops below a certain level
  if(brightness<50 && !brightnessLow){
    color = random8();
    brightnessLow = true;  
  }
  else if(brightness>100){
    brightnessLow = false;
  }

  // Determine how many LEDs need to be lit up
  int num = (int)(brightness/6.75)+1;
  if(num>=NUM_LEDS/2){
    num = NUM_LEDS/2;
  }
  else if(num<=0){
    num = 1;
  }
  //Reset all LEDs to off
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  //Update the LEDs with the correct color and brightness
  fill_solid(&(leds[NUM_LEDS/2 - num]), num*2, CHSV(color,255,brightness));
  FastLED.show();
  delay(3);
}
