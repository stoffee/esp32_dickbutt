/*  Keypadtest.pde
 *
 *  Demonstrate the simplest use of the  keypad library.
 *
 *  The first step is to connect your keypad to the
 *  Arduino  using the pin numbers listed below in
 *  rowPins[] and colPins[]. If you want to use different
 *  pins then  you  can  change  the  numbers below to
 *  match your setup.
 *
 */
#include <Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','.',','},
  {'!','@','#','$'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 15, 16, 18, 19 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 2, 0, 4, 5 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//define dickbutt size and look
#define DICKBUTT_HEIGHT 32 
#define DICKBUTT_WIDTH  32 
static const unsigned char PROGMEM dickbutt_bmp[] =
{
  0x00, 0x00, 0x00, 0x00, //                                 
  0x00, 0x00, 0x00, 0x00, //                                 
  0x00, 0x37, 0x00, 0x00, //           ## ###                
  0x00, 0xC0, 0x80, 0x00, //         ##      #               
  0x01, 0x00, 0x80, 0x00, //        #        #               
  0x03, 0x00, 0x40, 0x00, //       ##         #              
  0x07, 0x8F, 0x40, 0x00, //      ####   #### #              
  0x06, 0xDD, 0x40, 0x00, //      ## ## ### # #              
  0x07, 0x8B, 0x40, 0x00, //      ####   # ## #              
  0x04, 0xE0, 0x40, 0x00, //      #  ###      #              
  0x07, 0xFC, 0x40, 0x30, //      #########   #        ##    
  0x04, 0x00, 0x40, 0x28, //      #           #        # #   
  0x04, 0x00, 0x40, 0x40, //      #           #       #      
  0x04, 0x00, 0x40, 0x48, //      #           #       #  #   
  0x04, 0x03, 0x40, 0x88, //      #        ## #      #   #   
  0x04, 0x01, 0x5F, 0x90, //      #         # # ######  #    
  0x04, 0x01, 0x21, 0x1C, //      #         #  #    #   ###  
  0x04, 0x01, 0x0F, 0xC6, //      #         #    ######   ## 
  0x04, 0x01, 0x00, 0x2E, //      #         #          # ### 
  0x02, 0x01, 0x00, 0x12, //       #        #           #  # 
  0x02, 0x05, 0xC0, 0x1C, //       #      # ###         ###  
  0x01, 0x07, 0x00, 0x10, //        #     ###           #    
  0x00, 0x80, 0x00, 0x20, //         #                 #     
  0x00, 0xC0, 0x00, 0x60, //         ##               ##     
  0x00, 0x30, 0x00, 0xC0, //           ##            ##      
  0x00, 0x1F, 0x6F, 0x00, //            ##### ## ####        
  0x00, 0x14, 0x18, 0x00, //            # #     ##           
  0x00, 0xD8, 0xE8, 0x00, //         ## ##   ### #           
  0x00, 0xA8, 0x48, 0x00, //         # # #    #  #           
  0x00, 0x40, 0x28, 0x00, //          #        # #           
  0x00, 0x30, 0x18, 0x00, //           ##       ##           
  0x00, 0x00, 0x00, 0x00, //                                 
};

//define inverted dickbutt
#define DICKBUTT_HEIGHT 32 
#define DICKBUTT_WIDTH  32 
static const unsigned char PROGMEM inverted_dickbutt_bmp[] =
{0xD8, 0x8F, 0x26, 0x03, 0x88, 0x88, 0x38, 0x00, 
0x88, 0x88, 0x30, 0x00, 0x90, 0x07, 0x38, 0x00, 
0xC0, 0x38, 0x24, 0x00, 0x00, 0x80, 0x02, 0x00, 
0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
0x07, 0x38, 0x00, 0x00, 0x0F, 0x30, 0x00, 0x00, 
0x05, 0x18, 0x00, 0x00, 0x09, 0xD8, 0x00, 0x00, 
0x08, 0x01, 0x02, 0x00, 0x08, 0x01, 0x02, 0x00, 
0x08, 0x01, 0x00, 0x00, 0x08, 0x0D, 0x04, 0x00, 
0x00, 0x0D, 0x88, 0x80, 0x00, 0x0C, 0x28, 0xC0, 
0x00, 0x04, 0x02, 0x60, 0x04, 0x04, 0x00, 0x20, 
0x00, 0x06, 0x00, 0xC0, 0x02, 0x0C, 0x00, 0x00, 
0x01, 0x00, 0x01, 0x00, 0x00, 0x80, 0x02, 0x00, 
0x00, 0x38, 0x38, 0x00, 0x00, 0x32, 0x80, 0x00, 
0x01, 0x33, 0x80, 0x07, 0x01, 0xE1, 0x00, 0x3C, 
0x1A, 0xE0, 0xC3, 0x04, 0x12, 0x05, 0x1C, 0x06, 
0x0F, 0x07, 0x04, 0x01, 0x89, 0x83, 0x00, 0x01};

//define skull
#define SKULL_HEIGHT 32 
#define SKULL_WIDTH  32 
static const unsigned char PROGMEM skull_bmp[] =
{0x07, 0x00, 0x00, 0xE0, 0x0F, 0xC0, 0x03, 0xF0, 
0x18, 0xC0, 0x03, 0x18, 0x38, 0x60, 0x06, 0x1C, 
0x70, 0x60, 0x06, 0x0E, 0xC0, 0x6F, 0xF6, 0x03, 
0xC0, 0x7F, 0xFE, 0x03, 0xC0, 0x20, 0x04, 0x03, 
0x60, 0x00, 0x00, 0x06, 0x7E, 0x00, 0x00, 0x7E, 
0x1F, 0x00, 0x00, 0xF8, 0x03, 0x00, 0x00, 0xC0, 
0x03, 0x1E, 0x00, 0xC0, 0x03, 0x3F, 0x38, 0xC0, 
0x03, 0x3F, 0x7C, 0xC0, 0x02, 0x3F, 0x7C, 0x40, 
0x06, 0x3F, 0x7C, 0x60, 0x02, 0x1E, 0x38, 0x40, 
0x02, 0x00, 0x00, 0x40, 0x03, 0x86, 0x61, 0xC0, 
0x03, 0x80, 0x01, 0xC0, 0x1F, 0x00, 0x00, 0xF8, 
0x7E, 0x00, 0x00, 0x7E, 0x60, 0x12, 0x48, 0x06, 
0xC0, 0x30, 0x0C, 0x03, 0xC0, 0x72, 0x4E, 0x03, 
0xC0, 0x70, 0x0E, 0x03, 0x70, 0x78, 0x1E, 0x0E, 
0x38, 0x7F, 0xFE, 0x1C, 0x18, 0xCF, 0xF3, 0x18, 
0x0F, 0xC0, 0x03, 0xF0, 0x07, 0x00, 0x00, 0xE0};
char inChar;
String string;

void setup()
{
  Serial.begin(9600);
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  // I kept this because it's got a cute flower
  display.display();
  delay(2000);
  

}

  
void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '0':
  /*display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 0");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  display.clearDisplay();*/
// stupid "looks like walking" dickbutt
  walkingdickbutt();
  display.clearDisplay();
        break;
         case '1':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 1");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  break;
       case '2':
/*  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 2");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();*/
  // stupid "looks like walking" dickbutt
  walkingdickbutt();
  display.clearDisplay();
        break;
         case '3':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Quack!");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
        case '4':
/*  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 4");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  display.clearDisplay();*/
// inverted walking dickbutt
  invertedwalkingdickbutt();
  display.clearDisplay();
        break;
      case '5':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 5");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
         case '6':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 6");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
      case '7':
/*  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 7");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();*/
//skull should flash now
  skullflash();
  display.clearDisplay();
        break;
        case '8':
/*  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 8");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();*/
  // stupid "looks like walking" dickbutt
  walkingdickbutt();
  display.clearDisplay();
        break;
        case '9':
  /*display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 9");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();*/
  //skull should flash now
  skullflash();
  display.clearDisplay();
        break;
        case '.':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking .");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case ',':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking ,");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case '!':
/*  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking !");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();*/
  // inverted walking dickbutt
  invertedwalkingdickbutt();
  display.clearDisplay();
        break;
   case '@':
/*  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking @");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();*/
  //skull should flash now
  skullflash();
  display.clearDisplay();
        break;
   case '#':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking #");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case '$':
/*  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking $");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();*/
  // inverted walking dickbutt
  invertedwalkingdickbutt();
  display.clearDisplay();
        break;
        default:
        Serial.println(key);
    }
  }
  {   
      display.clearDisplay();
      inChar = Serial.read();
      string+=inChar;
      display.setCursor(0,0);
      display.print(string);
      display.display();
  }
}

  //make dickbutt walk
//need to add more dickbutt poses
void walkingdickbutt(void) {

for (uint8_t i=0; i<4; i++){
  display.clearDisplay();
  display.drawBitmap(108, 0,  dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(72, 0,  dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(36, 0,  dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(0, 0,  dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
}
}

  //make inverted dickbutt walk
void invertedwalkingdickbutt(void) {

for (uint8_t i=0; i<4; i++){
  display.clearDisplay();
  display.drawBitmap(108, 0,  inverted_dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(72, 0,  inverted_dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(36, 0,  inverted_dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(0, 0,  inverted_dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
}
}

  //make skull flash
void skullflash(void) {

for (uint8_t i=0; i<2; i++){
  display.clearDisplay();
  display.drawBitmap(36, 0,  skull_bmp, 32, 32, 1);
  display.display();
  delay(250);
  display.clearDisplay();
  display.drawBitmap(72, 0,  skull_bmp, 32, 32, 1);
  display.display();
  delay(250);
  display.clearDisplay();
  display.drawBitmap(36, 0,  skull_bmp, 32, 32, 1);
  display.display();
  delay(250);
  display.clearDisplay();
  display.drawBitmap(72, 0,  skull_bmp, 32, 32, 1);
  display.display();
  delay(250);
  display.clearDisplay();
}
}

