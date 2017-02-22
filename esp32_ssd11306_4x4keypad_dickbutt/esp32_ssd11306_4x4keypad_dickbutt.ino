/*
* Dickbutt is the name of the game
* 
* Short game utilizing the ESP32, a 64x32 OLED, and a 4x4 Keypad.
* 
*/
#include <Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//define random keymap
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'A','B','C','D'},
  {'E','F','G','H'},
  {'I','J','K','L'},
  {'M','N','O','P'}
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
{0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
0x00, 0x07, 0xC0, 0x00, 0x00, 0x07, 0xE0, 0x00, 
0x00, 0x07, 0x60, 0x00, 0x00, 0x02, 0x20, 0x00, 
0x00, 0x36, 0x20, 0x00, 0x00, 0x3F, 0xE0, 0x00, 
0x00, 0x3F, 0xA0, 0x00, 0x00, 0x7F, 0xE0, 0x40, 
0x00, 0x7F, 0xE0, 0xE0, 0x00, 0x7F, 0xE1, 0xE0, 
0x00, 0xFF, 0xC1, 0xC0, 0x00, 0x7F, 0xDB, 0x80, 
0x00, 0x7F, 0xFF, 0x80, 0x00, 0x7F, 0xF7, 0xC0, 
0x00, 0x7F, 0xFF, 0xC0, 0x00, 0x7F, 0xFF, 0xE0, 
0x00, 0x3F, 0xFF, 0xE0, 0x00, 0x1F, 0xFF, 0x80, 
0x03, 0x7F, 0xFF, 0x00, 0x03, 0x67, 0xFF, 0x00, 
0x01, 0xC0, 0xFC, 0x00, 0x01, 0xC0, 0xC0, 0x00, 
0x00, 0x02, 0xC0, 0x00, 0x00, 0x07, 0xC0, 0x00, 
0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
;

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

//randomize the keypad
// Initialize 2D array values
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      keys[i][j] = "ABCDEFGHIJKLMNOP"[rand () % 16];
//       keys[i][j] = "PONABCKDEFGHIJLM"[rand () % 16];
    }
} 

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
      case 'A':
// stupid "looks like walking" dickbutt
  walkingdickbutt();
  display.clearDisplay();
        break;
         case 'B':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed B");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  break;
       case 'C':
  // stupid "looks like walking" dickbutt
  walkingdickbutt();
  display.clearDisplay();
        break;
         case 'D':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Quack!");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
        case 'E':
// inverted walking dickbutt
  skullflash();
  display.clearDisplay();
        break;
      case 'F':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println(" <^> <(@_@)> <^> FUUUU <^> <(@_@)> <^>");
  display.display();
  display.startscrollleft(0x00, 0x0F);
  delay(2500);
  display.stopscroll();
        break;
         case 'G':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Ahhh, touch me");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
      case 'H':
//skull should flash now
  skullflash();
  display.clearDisplay();
        break;
        case 'I':
  // stupid "looks like walking" dickbutt
  walkingdickbutt();
  display.clearDisplay();
        break;
        case 'J':
  //skull should flash now
  skullflash();
  display.clearDisplay();
        break;
        case 'K':
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("I will Kick you!");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case 'L':
  //skull should flash now
  skullflash();
  display.clearDisplay();
        break;
   case 'M':
  // inverted walking dickbutt
  skullflash();
  display.clearDisplay();
        break;
   case 'N':
  //skull should flash now
  skullflash();
  display.clearDisplay();
        break;
   case 'O':
 //Skull GO
  skullflash();
  display.clearDisplay();
        break;
   case 'P':
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

for (uint8_t i=0; i<2; i++){
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

for (uint8_t i=0; i<2; i++){
  display.clearDisplay();
  display.drawBitmap(108, 0,  inverted_dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(72, 4,  inverted_dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(36, 0,  inverted_dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
  display.drawBitmap(0, 4,  inverted_dickbutt_bmp, 32, 32, 1);
  display.display();
  delay(500);
  display.clearDisplay();
}
}

  //make skull flash
void skullflash(void) {

for (uint8_t i=0; i<2; i++){
  display.clearDisplay();
  display.drawBitmap(36, 0,  skull_bmp, SKULL_HEIGHT, SKULL_WIDTH, 1);
  display.display();
  delay(50);
  display.clearDisplay();
  display.drawBitmap(72, 0,  skull_bmp, SKULL_HEIGHT, SKULL_WIDTH, 1);
  display.display();
  delay(50);
  display.clearDisplay();
  display.drawBitmap(36, 0,  skull_bmp, SKULL_HEIGHT, SKULL_WIDTH, 1);
  display.display();
  delay(50);
  display.clearDisplay();
  display.drawBitmap(72, 0,  skull_bmp, SKULL_HEIGHT, SKULL_WIDTH, 1);
  display.display();
  delay(50);
  display.clearDisplay();
}
}


