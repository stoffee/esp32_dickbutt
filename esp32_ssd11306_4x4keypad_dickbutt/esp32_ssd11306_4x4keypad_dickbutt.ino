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
static const unsigned char PROGMEM dickbutt_inverted_bmp[] =
{000000, 000000, 000000, 000000, 000000, 010101, 010101, 020202, 020202, 040404, 010101, 3D3D3D, 4E4E4E, 000000, 020202, 080808, 060606, 050505, 040404, 000000, 070707, 000000, 000000, 020202, 010101, 010101, 000000, 030303, 000000, 000000, 040404, 010101, 000000, 000000, 000000, 000000, 000000, 010101, 010101, 020202, 010101, 000000, 737373, EFEFEF, C5C5C5, C8C8C8, 1A1A1A, 000000, 020202, 000000, 030303, 101010, 000000, 070707, 010101, 020202, 000000, 000000, 000000, 010101, 0A0A0A, 030303, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 010101, 010101, 020202, 0C0C0C, 020202, BABABA, B3B3B3, ACACAC, CBCBCB, BEBEBE, 030303, 727272, 696969, 000000, 000000, 050505, 0C0C0C, 020202, 000000, 000000, 080808, 000000, 000000, 050505, 000000, 000000, 0B0B0B, 000000, 000000, 000000, 000000, 000000, 010101, 010101, 020202, 000000, 252525, DBDBDB, B9B9B9, FFFFFF, C0C0C0, AEAEAE, 7C7C7C, FEFEFE, DEDEDE, 0C0C0C, 090909, 000000, 000000, 000000, 070707, 050505, 030303, 000000, 000000, 020202, 030303, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 010101, 010101, 020202, 0B0B0B, 737373, C5C5C5, DADADA, F5F5F5, A5A5A5, CBCBCB, BDBDBD, B9B9B9, ABABAB, 292929, 9C9C9C, B4B4B4, 909090, 000000, 080808, 000000, 000000, 111111, 070707, 000000, 090909, 070707, 020202, 000000, 000000, 000000, 000000, 000000, 010101, 010101, 020202, 000000, 8F8F8F, D4D4D4, B2B2B2, BABABA, F7F7F7, 8E8E8E, BEBEBE, C0C0C0, 999999, D6D6D6, C3C3C3, AEAEAE, EEEEEE, B7B7B7, E6E6E6, 838383, 050505, 000000, 000000, 050505, 000000, 000000, 010101, 000000, 000000, 000000, 000000, 000000, 010101, 010101, 020202, 0D0D0D, 262626, B5B5B5, B2B2B2, ACACAC, 393939, 060606, E7E7E7, D9D9D9, B7B7B7, B5B5B5, C9C9C9, FFFFFF, E7E7E7, FEFEFE, C6C6C6, E4E4E4, 9E9E9E, A3A3A3, 0D0D0D, 000000, 0B0B0B, 0D0D0D, 000000, 000000, 000000, 000000, 000000, 000000, 010101, 010101, 020202, 000000, 101010, 000000, 010101, 000000, 383838, CDCDCD, DCDCDC, D3D3D3, D5D5D5, D5D5D5, B1B1B1, D1D1D1, FFFFFF, F5F5F5, 969696, C1C1C1, C0C0C0, FFFFFF, 282828, 070707, 000000, 040404, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 060606, 000000, 242424, C3C3C3, F7F7F7, B2B2B2, B6B6B6, C2C2C2, BEBEBE, A4A4A4, EBEBEB, D1D1D1, D5D5D5, D1D1D1, 727272, EEEEEE, D0D0D0, 5F5F5F, 050505, 050505, 000000, 050505, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 050505, DDDDDD, A0A0A0, 2E2E2E, DEDEDE, FFFFFF, FFFFFF, FFFFFF, C9C9C9, DFDFDF, 575757, 272727, FBFBFB, C3C3C3, CFCFCF, ACACAC, 0C0C0C, 050505, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 0D0D0D, 020202, 3D3D3D, E1E1E1, 000000, 666666, A6A6A6, FDFDFD, ADADAD, ADADAD, EEEEEE, C2C2C2, 6E6E6E, 0B0B0B, 6C6C6C, D1D1D1, CFCFCF, E1E1E1, 474747, 000000, 070707, 040404, 020202, 0D0D0D, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, A3A3A3, BEBEBE, C3C3C3, 969696, D3D3D3, B0B0B0, 080808, 676767, BFBFBF, C7C7C7, 7D7D7D, 000000, 000000, 080808, B4B4B4, EAEAEA, 303030, 000000, 000000, 060606, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 060606, 1C1C1C, ECECEC, 727272, A5A5A5, 8B8B8B, A9A9A9, BABABA, 8F8F8F, B4B4B4, A9A9A9, DBDBDB, 414141, 050505, 040404, 000000, 050505, 0C0C0C, 000000, 030303, 000000, 030303, 000000, 0A0A0A, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 8A8A8A, C9C9C9, E7E7E7, FCFCFC, D6D6D6, B0B0B0, A5A5A5, 8A8A8A, ECECEC, B4B4B4, D3D3D3, 040404, 080808, 070707, 030303, 050505, 000000, 010101, 000000, 090909, 000000, 090909, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, C5C5C5, BCBCBC, F0F0F0, F7F7F7, FFFFFF, F3F3F3, FFFFFF, FEFEFE, E8E8E8, C3C3C3, A7A7A7, 0A0A0A, 060606, 000000, 050505, 000000, 000000, 060606, 010101, 000000, 0E0E0E, 000000, 020202, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 000000, 242424, D8D8D8, B7B7B7, FFFFFF, FFFFFF, F7F7F7, FFFFFF, E5E5E5, FFFFFF, CECECE, DFDFDF, 464646, 010101, 000000, 3E3E3E, B6B6B6, B4B4B4, 3D3D3D, 000000, 000000, 050505, 000000, 050505, 000000, 000000, 060606, 000000, 000000, 010101, 000000, 000000, 060606, 2C2C2C, CFCFCF, D0D0D0, FFFFFF, FAFAFA, FBFBFB, F7F7F7, B6B6B6, DADADA, C7C7C7, BFBFBF, 000000, 030303, 111111, E8E8E8, C8C8C8, DADADA, CCCCCC, 000000, 000000, 070707, 000000, 000000, 000000, 000000, 000000, 050505, 010101, 0C0C0C, 000000, 020202, 000000, 282828, C9C9C9, D8D8D8, FFFFFF, EDEDED, FFFFFF, E4E4E4, B0B0B0, C7C7C7, AFAFAF, E3E3E3, B4B4B4, 8A8A8A, CDCDCD, C4C4C4, E4E4E4, C1C1C1, D6D6D6, 0D0D0D, 050505, 000000, 010101, 020202, 030303, 090909, 000000, 000000, 000000, 000000, 000000, 060606, 000000, 3B3B3B, C9C9C9, C5C5C5, F6F6F6, FFFFFF, FBFBFB, C3C3C3, AEAEAE, F7F7F7, 939393, AEAEAE, C4C4C4, D4D4D4, B6B6B6, D8D8D8, F2F2F2, D9D9D9, 999999, 020202, 070707, 000000, 000000, 000000, 040404, 000000, 000000, 000000, 030303, 000000, 070707, 060606, 000000, 1F1F1F, C9C9C9, DEDEDE, FFFFFF, FFFFFF, E8E8E8, BBBBBB, BCBCBC, F5F5F5, F4F4F4, C5C5C5, BFBFBF, 909090, C9C9C9, F2F2F2, AAAAAA, EEEEEE, 2F2F2F, 000000, 030303, 000000, 000000, 000000, 000000, 020202, 000000, 010101, 000000, 030303, 000000, 000000, 000000, 0F0F0F, CBCBCB, B1B1B1, FEFEFE, F9F9F9, 919191, BDBDBD, 999999, E3E3E3, FFFFFF, D2D2D2, E7E7E7, B1B1B1, C1C1C1, DDDDDD, 9F9F9F, D5D5D5, 080808, 040404, 050505, 000000, 070707, 040404, 000000, 040404, 000000, 030303, 000000, 0C0C0C, 000000, 080808, 060606, 030303, A3A3A3, B2B2B2, E5E5E5, FBFBFB, F1F1F1, B6B6B6, D7D7D7, F8F8F8, FFFFFF, ECECEC, DBDBDB, FFFFFF, BFBFBF, DADADA, BCBCBC, CFCFCF, 242424, 000000, 060606, 000000, 020202, 000000, 000000, 070707, 000000, 060606, 000000, 000000, 141414, 252525, 030303, 0E0E0E, 888888, F9F9F9, 979797, F4F4F4, FFFFFF, F9F9F9, FFFFFF, FFFFFF, EDEDED, F3F3F3, FEFEFE, FCFCFC, D6D6D6, A4A4A4, BBBBBB, D3D3D3, 242424, 000000, 030303, 000000, 000000, 000000, 040404, 000000, 050505, 000000, 0A0A0A, 000000, A1A1A1, E6E6E6, C8C8C8, EEEEEE, D4D4D4, FBFBFB, A6A6A6, 7F7F7F, C6C6C6, DDDDDD, FFFFFF, FEFEFE, FFFFFF, F6F6F6, FFFFFF, DDDDDD, A7A7A7, E7E7E7, D9D9D9, B9B9B9, 000000, 040404, 020202, 000000, 000000, 020202, 000000, 020202, 000000, 040404, 000000, 0B0B0B, DBDBDB, 9F9F9F, BABABA, D4D4D4, A6A6A6, C1C1C1, A8A8A8, E9E9E9, D5D5D5, B2B2B2, A1A1A1, D0D0D0, B2B2B2, CACACA, BBBBBB, B0B0B0, F6F6F6, 6C6C6C, 1F1F1F, 080808, 000000, 030303, 010101, 000000, 010101, 070707, 000000, 010101, 0C0C0C, 000000, 070707, 2D2D2D, CACACA, D4D4D4, CBCBCB, B5B5B5, CECECE, B6B6B6, DFDFDF, FCFCFC, F7F7F7, BABABA, B4B4B4, B5B5B5, E0E0E0, D6D6D6, DADADA, B0B0B0, 383838, 000000, 000000, 000000, 111111, 000000, 0A0A0A, 000000, 000000, 020202, 000000, 000000, 000000, 000000, 050505, 404040, D9D9D9, B8B8B8, 909090, EAEAEA, F4F4F4, D8D8D8, F8F8F8, EBEBEB, FBFBFB, B3B3B3, CECECE, DEDEDE, 858585, 080808, 000000, 080808, 000000, 000000, 080808, 000000, 020202, 010101, 000000, 030303, 000000, 000000, 070707, 050505, 010101, 020202, 010101, 3E3E3E, D9D9D9, B1B1B1, E5E5E5, 989898, C1C1C1, 2E2E2E, C0C0C0, D7D7D7, FEFEFE, CCCCCC, BABABA, E4E4E4, C3C3C3, 747474, 646464, 2E2E2E, 919191, A7A7A7, 858585, 616161, 1D1D1D, 070707, 020202, 000000, 030303, 050505, 000000, 010101, 000000, 040404, 040404, 0A0A0A, B5B5B5, EAEAEA, B9B9B9, E7E7E7, 848484, 000000, B5B5B5, BFBFBF, A7A7A7, D9D9D9, D0D0D0, EDEDED, A8A8A8, BDBDBD, E9E9E9, EDEDED, F7F7F7, B9B9B9, B4B4B4, F7F7F7, BDBDBD, 000000, 000000, 080808, 060606, 000000, 030303, 010101, 010101, 000000, 000000, 000000, 0F0F0F, 565656, 717171, 5A5A5A, 030303, 000000, 858585, F3F3F3, CFCFCF, C7C7C7, 020202, A7A7A7, C8C8C8, AAAAAA, E1E1E1, 818181, 818181, C9C9C9, B3B3B3, DBDBDB, 888888, 020202, 080808, 000000, 000000, 060606, 000000, 000000, 000000, 0A0A0A, 010101, 090909, 000000, 000000, 030303, 010101, 000000, 090909, 000000, 363636, 4F4F4F, 131313, 030303, 1A1A1A, F1F1F1, E8E8E8, 171717, 000000, 272727, E3E3E3, EFEFEF, 1E1E1E, 000000, 030303, 000000, 040404, 010101, 000000, 000000, 000000, 070707, 000000, 000000, 030303, 030303, 000000, 030303, 020202, 000000, 010101, 030303, 050505, 010101, 000000, 010101, 010101, 3C3C3C, 323232, 030303, 000000, 010101, 484848, 313131, 040404, 000000, 050505, 000000, 000000, 000000, 000000, 030303
}

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
  delay(7000);
  

}

  
void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '0':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 0");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  display.clearDisplay();
// stupid "looks like walking" dickbutt
  walkingdickbutt();
//  delay(1000);
  display.clearDisplay();
        break;
         case '1':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 1");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
       case '2':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 2");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
         case '3':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 3");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
        case '4':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 4");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();;
        break;
      case '5':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 5");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
         case '6':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 6");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
      case '7':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 7");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
        case '8':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 8");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
        case '9':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking 9");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
        case '.':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking .");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case ',':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking ,");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case '!':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking !");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case '@':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking @");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case '#':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking #");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
        break;
   case '$':
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("You Pushed Fucking $");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
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

