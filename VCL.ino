/*
 * 
 * VOLTAGE CONTROLLED LIGHT BOX
 * 
 * CREATED BY ITAI ASSEO
 * 
 * INSTAGRAM: @iiitaiii
 * 
 * 
 */

//INCLUDE FASTLED LIBRARY

#include <noise.h>
#include <bitswap.h>
#include <fastspi_types.h>
#include <pixelset.h>
#include <fastled_progmem.h>
#include <led_sysdefs.h>
#include <hsv2rgb.h>
#include <fastled_delay.h>
#include <colorpalettes.h>
#include <color.h>
#include <fastspi_ref.h>
#include <fastspi_bitbang.h>
#include <controller.h>
#include <fastled_config.h>
#include <colorutils.h>
#include <chipsets.h>
#include <pixeltypes.h>
#include <fastspi_dma.h>
#include <fastpin.h>
#include <fastspi_nop.h>
#include <platforms.h>
#include <lib8tion.h>
#include <cpp_compat.h>
#include <fastspi.h>
#include <FastLED.h>
#include <dmx.h>
#include <power_mgt.h>

//DEFINE THE RGB STRIP PINS:
 
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3


int colorToggle = 8; //Toggle switch between color CV and Color Pot
int potColorPin= 4;  //To control Color, Connect potentiometer to A5 (middle pin) stage-right pin to ground, stage left pin to 5v
int potFadePin= 5;  //To Control Fade Time, Connect potentiometer to A4 (middle pin) stage-right pin to ground, stage left pin to 5v
int cvGatePin= 1;  //CV in for GATE - Connect CV to A1
int cvColorPin= 0;  //CV in for COLOR - Connect CV to A0
int cvGateValue; //store gate values
int cvColorValue; //store color values
int fadeTime = 5; //higher = slower - this is a delay time that seems to work well
int colorValue;  // Use this variable to read Potentiometer #1
int fadeValue;  // Use this variable to read Potentiometer #2
int colorWriteValue = 1; // variable to hold the color potentiometer value
int colorCvWriteValue = 1; // variable to hold the color cv value
float fadeWriteValue = 0.02; // variable to hold the release potentiometer value
float brightness; // variable to hold the brightness value
 
void setup() {
  // Serial.begin(9600); //uncomment to debug
  pinMode(colorToggle, INPUT_PULLUP); // set the toggle switch
  pinMode(potColorPin, INPUT);  //set pot color Pin to be an input
  pinMode(potFadePin, INPUT);  //set pot release (fade time) Pin to be an input
  pinMode(cvGatePin, INPUT);  //set gate CV to be an input
  pinMode(cvColorPin, INPUT);  //set Color CV to be an input
  pinMode(REDPIN, OUTPUT); // set red LED pin output
  pinMode(GREENPIN, OUTPUT); // set green LED pin output
  pinMode(BLUEPIN, OUTPUT); // set blue LED pin output
}
 
 
void loop() {
  colorValue = analogRead(potColorPin);  //Read the voltage on  Potentiometer #1
  fadeValue = analogRead(potFadePin);  //Read the voltage on  Potentiometer #2*/
  cvColorValue = analogRead(cvColorPin); // Read the cv for the color value
  colorCvWriteValue = (255./1023.) * cvColorValue; //convert color to be 0-255 value (CV)
  colorWriteValue = (255./1023.) * colorValue; //convert color to be 0-255 value (POT)
  fadeWriteValue = (0.100/1023.000) * fadeValue; //convert release to be 0-1 value (POT)
  cvGateValue = analogRead(cvGatePin); // Read the gate value
  float cvScaled = (100.00/1023.00) * cvGateValue; //convert the gate value to 0-100
  cvScaled = cvScaled/100; // convert the gate to be 0-1
  //Serial.println(fadeValue); //debug potentiometer
  
  //if the gate value is higher than current brightness (which should always be the case unless using cv to control brighness, which I haven't optimized for)
  //then change brightness to that value
  if (cvScaled > brightness){
    brightness = cvScaled;
  }

  //if brightness is no 0, fade it out by the value determined by the potentiometer
  if (brightness > 0.01){
   brightness -= fadeWriteValue; 
   delay(fadeTime); //delay time can be set up top
  }else{
    showAnalogRGB( CRGB::Black ); //turn off the LED Strip if value is lower than 0.01
    brightness = 0.00; 
  }


  //toggle between CV color control and manual (potentiometer) control
  int myColor;
  if (digitalRead(colorToggle)){
    myColor = colorCvWriteValue;
  }else{
    myColor = colorWriteValue;
  }

  //execute command to LED strip
  showAnalogRGB( CHSV( myColor, 255, 255) );
}

// showAnalogRGB: this is like FastLED.show(), but outputs on 
// analog PWM output pins instead of sending data to an intelligent,
// pixel-addressable LED strip.
// 
// This function takes the incoming RGB values and outputs the values
// on three analog PWM output pins to the r, g, and b values respectively.
// it then multiplies it by the brightness to enable fading
void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(REDPIN,   rgb.r * brightness );
  analogWrite(GREENPIN, rgb.g * brightness);
  analogWrite(BLUEPIN,  rgb.b * brightness);
}

