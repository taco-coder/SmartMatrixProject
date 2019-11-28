/*
 * Code for 64x32 LED matrix panel
 */

#include <SmartLEDShieldV4.h>  // comment out this line for if you're not using SmartLED Shield V4 hardware (this line needs to be before #include <SmartMatrix3.h>)
#include <SmartMatrix3.h>

#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 64;        // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 32;       // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 36;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN; // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels, or use SMARTMATRIX_HUB75_64ROW_MOD32SCAN for common 64x64 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
const uint8_t kIndexedLayerOptions = (SM_INDEXED_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(firstWord, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(secondWord, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
SMARTMATRIX_ALLOCATE_INDEXED_LAYER(indexedLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);

const int defaultBrightness = (100*255)/100;    // full (100%) brightness
//const int defaultBrightness = (15*255)/100;    // dim: 15% brightness
const rgb24 defaultBackgroundColor = {0x40, 0, 0};

// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;


// the setup() method runs once, when the sketch starts
void setup() {
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);

  Serial.begin(38400);

  matrix.addLayer(&backgroundLayer); 
  matrix.addLayer(&firstWord); 
  matrix.addLayer(&secondWord);
  matrix.addLayer(&indexedLayer); 
  matrix.begin();

  matrix.setBrightness(defaultBrightness);

  backgroundLayer.enableColorCorrection(true);

  backgroundLayer.fillScreen({0x00, 0x00, 0x00});  
  //brightness is set 20%
  backgroundLayer.setBrightness((20 * 255) / 100);
  backgroundLayer.swapBuffers();

  current = millis();
    
  //Sets text at the top
  firstWord.setColor({0xff, 0x0d, 0x00});
  firstWord.setMode(wrapForward);
  firstWord.setSpeed(30);
  firstWord.setFont(font3x5);
  firstWord.setOffsetFromTop(0);
  firstWord.start("Red",-1);
  if(current == 1000){
    firstWord.setMode(stopped);
  }
  delay(1750);

  secondWord.setColor({0x00, 0xa3, 0x13});
  secondWord.setMode(wrapForward);
  secondWord.setSpeed(30);
  secondWord.setFont(font3x5);
  secondWord.setOffsetFromTop(0);
  secondWord.start("green", -1);
  if(current == 2500){
    secondWord.setMode(stopped);
  }
  

}

void loop() {



}
