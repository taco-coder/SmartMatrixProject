/*
 * Code for 64x32 LED matrix panel
 */

#include <SmartLEDShieldV4.h>  // comment out this line for if you're not using SmartLED Shield V4 hardware (this line needs to be before #include <SmartMatrix3.h>)
#include <SmartMatrix3.h>


#define FIRST_SECOND_DELAY 500
#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 64;        // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 32;       // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 36;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN; // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels, or use SMARTMATRIX_HUB75_64ROW_MOD32SCAN for common 64x64 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(firstWord, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(secondWord, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);

const int defaultBrightness = (100*255)/100;    // full (100%) brightness
//const int defaultBrightness = (50*255)/100;    // dim: 50% brightness

// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;

//function to update tree lights
void updateLights(const rgb24 & color){
  /*lines to draw lights across tree                                                                               
 * x1, y1
 * x2, y2
 * color
 */
    backgroundLayer.drawLine(matrix.getScreenWidth() - 16, matrix.getScreenHeight() - 23,
                            matrix.getScreenWidth() - 11, matrix.getScreenHeight() - 25,
                            color);      
    backgroundLayer.drawLine(matrix.getScreenWidth() - 18, matrix.getScreenHeight() - 18,
                            matrix.getScreenWidth() - 10, matrix.getScreenHeight() - 20,
                            color);                                   
    backgroundLayer.drawLine(matrix.getScreenWidth() - 20, matrix.getScreenHeight() - 13,
                            matrix.getScreenWidth() - 8, matrix.getScreenHeight() - 15,
                            color);                               
    backgroundLayer.drawLine(matrix.getScreenWidth() - 22, matrix.getScreenHeight() - 8,
                            matrix.getScreenWidth() - 6, matrix.getScreenHeight() - 10,
                            color);    
                                delay(500);
    backgroundLayer.swapBuffers();
}

//function to create fire in position 1
void fireOne(const rgb24 & color1, const rgb24 & color2){
/*lines to draw fire                                                                                
 * x1, y1
 * x2, y2
 * color
 */
  backgroundLayer.drawLine(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 4,
                            matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 4,
                            color1);
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 4,
                            color2);          
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 10,
                            color1);    
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 10,
                            color1);                                                                                  
  backgroundLayer.drawLine(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 5,
                            matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 5,
                            color1);  
  backgroundLayer.drawLine(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 5,
                            matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 5,
                            color2);                                
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 6,
                                matrix.getScreenWidth() - 45, matrix.getScreenHeight() - 7,
                                color1); 
                                                                
  /* Orange Triangle left
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 12, 
                               color1);   
  /* Orange Triangle mid
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 15, 
                               color1);                                                                
  /* Orange Triangle right
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 45, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 45, matrix.getScreenHeight() - 13, 
                               color1);    
  /*                                   
   * yellow rectangles
   */
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 6,
                                matrix.getScreenWidth() - 47, matrix.getScreenHeight() - 7,
                                color2);  
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 7,
                                matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 8,
                                color2);   
  /* Triangle right
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 49, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 11, 
                               color2);   
  /* Triangle mid
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 51, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 49, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 12, 
                               color2);    
  /* Triangle left
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 10, 
                               color2);  
  backgroundLayer.swapBuffers();
}

//function to create fire in position 2
void fireTwo(const rgb24 & color1, const rgb24 & color2){
/*lines to draw fire                                                                                
 * x1, y1
 * x2, y2
 * color
 */
  backgroundLayer.drawLine(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 4,
                            matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 4,
                            color1);
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 4,
                            color2);          
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 10,
                            color1);    
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 10,
                            color1);                                                                                  
  backgroundLayer.drawLine(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 5,
                            matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 5,
                            color1);  
  backgroundLayer.drawLine(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 5,
                            matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 5,
                            color2);                                
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 6,
                                matrix.getScreenWidth() - 45, matrix.getScreenHeight() - 7,
                                color1); 
                                                                
  /* Orange Triangle left
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 12, 
                               color1);   
  /* Orange Triangle mid
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 15, 
                               color1);                                                                
  /* Orange Triangle right
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 45, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 47, matrix.getScreenHeight() - 13, 
                               color1);    
  /*                                   
   * yellow rectangles
   */
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 6,
                                matrix.getScreenWidth() - 47, matrix.getScreenHeight() - 7,
                                color2);  
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 7,
                                matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 8,
                                color2);   
  /* Triangle right
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 49, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 11, 
                               color2);   
  /* Triangle mid
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 51, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 49, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 12, 
                               color2);    
  /* Triangle left
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 10, 
                               color2);  
  backgroundLayer.swapBuffers();
}

//function to create fire in position 3
void fireThree(const rgb24 & color1, const rgb24 & color2){
/*lines to draw fire                                                                                
 * x1, y1
 * x2, y2
 * color
 */
  backgroundLayer.drawLine(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 4,
                            matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 4,
                            color1);
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 4,
                            color2);          
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 10,
                            color1);    
  backgroundLayer.drawPixel(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 10,
                            color1);                                                                                  
  backgroundLayer.drawLine(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 5,
                            matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 5,
                            color1);  
  backgroundLayer.drawLine(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 5,
                            matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 5,
                            color2);                                
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 6,
                                matrix.getScreenWidth() - 45, matrix.getScreenHeight() - 7,
                                color1); 
                                                                
  /* Orange Triangle left
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 12, 
                               color1);   
  /* Orange Triangle mid
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 52, matrix.getScreenHeight() - 15, 
                               color1);                                                                
  /* Orange Triangle right
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 45, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 47, matrix.getScreenHeight() - 13, 
                               color1);    
  /*                                   
   * yellow rectangles
   */
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 6,
                                matrix.getScreenWidth() - 47, matrix.getScreenHeight() - 7,
                                color2);  
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 7,
                                matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 8,
                                color2);   
  /* Triangle right
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 49, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 46, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 48, matrix.getScreenHeight() - 11, 
                               color2);   
  /* Triangle mid
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 51, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 49, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 50, matrix.getScreenHeight() - 12, 
                               color2);    
  /* Triangle left
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 53, matrix.getScreenHeight() - 8, 
                               matrix.getScreenWidth() - 54, matrix.getScreenHeight() - 10, 
                               color2);  
  backgroundLayer.swapBuffers();
}
//draws line to make ornaments
void makeOrnament(int x1, int x2, int y, int x3, int y1, int y2, const rgb24 & color){
  backgroundLayer.drawLine(matrix.getScreenWidth() - x1, matrix.getScreenHeight() - y,
                           matrix.getScreenWidth() - x2, matrix.getScreenHeight() - y,
                           color);         

   backgroundLayer.drawLine(matrix.getScreenWidth() - x3, matrix.getScreenHeight() - y1,
                            matrix.getScreenWidth() - x3, matrix.getScreenHeight() - y2,
                            color); 
}

// the setup() method runs once, when the sketch starts
void setup() {
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);

  Serial.begin(38400);

  matrix.addLayer(&backgroundLayer); 
  matrix.addLayer(&firstWord); 
  matrix.addLayer(&secondWord);
  matrix.begin();

  matrix.setBrightness(defaultBrightness);

  backgroundLayer.enableColorCorrection(true);

  backgroundLayer.fillScreen({0x00, 0x00, 0x00});  
  //brightness is set 20%
  backgroundLayer.setBrightness((20 * 255) / 100);
 /* Triangle top
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 17, matrix.getScreenHeight() - 22, 
                               matrix.getScreenWidth() - 13, matrix.getScreenHeight() - 28, 
                               matrix.getScreenWidth() - 9, matrix.getScreenHeight() - 22, 
                               {0x09, 0x9e, 0x01});
  /* Triangle mid 1
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 19, matrix.getScreenHeight() - 17, 
                               matrix.getScreenWidth() - 13, matrix.getScreenHeight() - 24, 
                               matrix.getScreenWidth() - 7, matrix.getScreenHeight() - 17, 
                               {0x09, 0x9e, 0x01});
  /* Triangle mid 2
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 21, matrix.getScreenHeight() - 12, 
                               matrix.getScreenWidth() - 13, matrix.getScreenHeight() - 20, 
                               matrix.getScreenWidth() - 5, matrix.getScreenHeight() - 12, 
                               {0x09, 0x9e, 0x01});
  /* Triangle bottom
  * X1, Y1
  * X2, Y2
  * X3, Y3
  * Color
  */
  backgroundLayer.fillTriangle(matrix.getScreenWidth() - 23, matrix.getScreenHeight() - 7, 
                               matrix.getScreenWidth() - 13, matrix.getScreenHeight() - 16, 
                               matrix.getScreenWidth() - 3, matrix.getScreenHeight() - 7, 
                               {0x09, 0x9e, 0x01});     
/* Rectangle bottom                                                         
 * X1, Y1                                                          
 * X2, Y2
 * Color
 */
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 15, matrix.getScreenHeight() - 6,
                                matrix.getScreenWidth() - 11, matrix.getScreenHeight(),
                                {0x66, 0x35, 0x00});            

/*                                           
 * lines to draw the star
 * x1, y1
 * x2, y2
 * color
 */
  backgroundLayer.drawLine(matrix.getScreenWidth() - 15, matrix.getScreenHeight() - 28,
                           matrix.getScreenWidth() - 11, matrix.getScreenHeight() - 28,
                           {0xff, 0xf2, 0x00});
                           
  backgroundLayer.drawLine(matrix.getScreenWidth() - 13, matrix.getScreenHeight() - 26,
                           matrix.getScreenWidth() - 13, matrix.getScreenHeight() - 30,
                           {0xff, 0xf2, 0x00});  
                           
  backgroundLayer.drawLine(matrix.getScreenWidth() - 14, matrix.getScreenHeight() - 29,
                           matrix.getScreenWidth() - 12, matrix.getScreenHeight() - 27,
                           {0xff, 0xf2, 0x00});       

  backgroundLayer.drawLine(matrix.getScreenWidth() - 14, matrix.getScreenHeight() - 27,
                           matrix.getScreenWidth() - 12, matrix.getScreenHeight() - 29,
                           {0xff, 0xf2, 0x00});                                                                                    

/*                           
 *  draw ornaments
 */
  makeOrnament(24, 22, 6, 23, 7, 5, {0xff, 0x00, 0x00});
  makeOrnament(4, 2, 6, 3, 7, 5, {0x00, 0x00, 0xff});    
  makeOrnament(22, 20, 11, 21, 12 ,10, {0x00, 0xff, 0xff});
  makeOrnament(6, 4, 11, 5, 12, 10, {0xff, 0xff, 0x00});
  makeOrnament(20, 18, 17, 19, 18, 16, {0xff, 0xff, 0xff});
  makeOrnament(8, 6, 17, 7, 18 ,16, {0xff, 0xaa, 0x00});
  makeOrnament(18, 16, 22, 17, 23, 21, {0xff, 0x11, 0xdf});
  makeOrnament(10, 8, 22, 9, 23, 21, {0x6b, 0x02, 0xff}); 
                                
/* Rectangle boxes                                                       
 * X1, Y1                                                          
 * X2, Y2
 * Color
 */
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 33, matrix.getScreenHeight() - 6,
                                matrix.getScreenWidth() - 26, matrix.getScreenHeight(),
                                {0xff, 0x00, 0x00});   
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 30, matrix.getScreenHeight() - 8,
                                matrix.getScreenWidth() - 29, matrix.getScreenHeight(),
                                {0xff, 0xff, 0x00});                                      
  backgroundLayer.drawLine(matrix.getScreenWidth() - 31, matrix.getScreenHeight() - 7,
                                matrix.getScreenWidth() - 28, matrix.getScreenHeight() - 7,
                                {0xff, 0xff, 0x00});   
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 40, matrix.getScreenHeight() - 11,
                                matrix.getScreenWidth() - 35, matrix.getScreenHeight(),
                                {0x00, 0x00, 0xff});   
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 40, matrix.getScreenHeight() - 7,
                                matrix.getScreenWidth() - 35, matrix.getScreenHeight() - 6,
                                {0xff, 0xff, 0x00});                                   
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 38, matrix.getScreenHeight() - 11,
                                matrix.getScreenWidth() - 37, matrix.getScreenHeight(),
                                {0xff, 0xff, 0x00});
/*lines to draw lights across tree                                                                               
 * x1, y1
 * x2, y2
 * color
 */                                     
    backgroundLayer.drawLine(matrix.getScreenWidth() - 16, matrix.getScreenHeight() - 23,
                            matrix.getScreenWidth() - 11, matrix.getScreenHeight() - 25,
                            {0xff, 0xff, 0x00});      
    backgroundLayer.drawLine(matrix.getScreenWidth() - 18, matrix.getScreenHeight() - 18,
                            matrix.getScreenWidth() - 10, matrix.getScreenHeight() - 20,
                            {0xff, 0xff, 0x00});                                   
    backgroundLayer.drawLine(matrix.getScreenWidth() - 20, matrix.getScreenHeight() - 13,
                            matrix.getScreenWidth() - 8, matrix.getScreenHeight() - 15,
                            {0xff, 0xff, 0x00});                               
    backgroundLayer.drawLine(matrix.getScreenWidth() - 22, matrix.getScreenHeight() - 8,
                            matrix.getScreenWidth() - 6, matrix.getScreenHeight() - 10,
                            {0xff, 0xff, 0x00});  

/* log block                                            
 * X1, Y1                                                          
 * X2, Y2
 * Color
 */
  backgroundLayer.fillRectangle(matrix.getScreenWidth() - 55, matrix.getScreenHeight() - 3,
                                matrix.getScreenWidth() - 45, matrix.getScreenHeight(),
                                {0x66, 0x35, 0x00});   
                                                                                                                                              
  backgroundLayer.swapBuffers();

    
  //Sets text at the top
  firstWord.setColor({0xff, 0x0d, 0x00});
  firstWord.setMode(wrapForward);
  firstWord.setSpeed(30);
  firstWord.setFont(gohufont11);
  firstWord.setOffsetFromTop(0);
  firstWord.start("Merry", 1);

  delay(FIRST_SECOND_DELAY);

  secondWord.setColor({0x00, 0xa3, 0x13});
  secondWord.setMode(wrapForward);
  secondWord.setSpeed(30);
  secondWord.setFont(font5x7);
  secondWord.setOffsetFromTop(11);
  secondWord.start("Christmas", 1);

  delay(2200);
  firstWord.setMode(stopped);
  firstWord.setStartOffsetFromLeft(0);
  delay(FIRST_SECOND_DELAY);
  secondWord.setMode(stopped);
  secondWord.setStartOffsetFromLeft(0);

}
//runs repeatedly
void loop() {
  //fire in the first position
    fireOne({0xff, 0x64, 0x00}, {0xff, 0xff, 0x00});
  //update lights on tree
    updateLights({0xff, 0xff, 0x00});
    updateLights({0xff, 0xff, 0xff});
    updateLights({0x00, 0xff, 0xff});
    updateLights({0x00, 0x00, 0xff});                                                                             
    updateLights({0xff, 0x00, 0x00});
    updateLights({0xff, 0x00, 0xff});                            
}
