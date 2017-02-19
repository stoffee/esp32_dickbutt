/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define DICKBUTTS 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

//define dickbutt size and look
#define DICKBUTT_HEIGHT 32 
#define DICKBUTT_WIDTH  32 
static const unsigned char PROGMEM dickbutt_bmp[] =
{
  0x80, 0x00, 0x00, 0x01, // #                              #
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
  0x80, 0x00, 0x00, 0x01, // #                              #
};

//check if 128x32
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
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

  // Clear the buffer.
  display.clearDisplay();

  
   // ask if they want the dickbutt
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Are you");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(2);
  display.setCursor(0,10);
  display.println("ready for");
  display.display();
  delay(2000);
  display.clearDisplay();

  // draw scrolling text
  testscrolltext();
//  delay(2000);
  display.clearDisplay();

// stupid "looks like walking" dickbutt
  walkingdickbutt();
//  delay(1000);
  display.clearDisplay();

  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(dickbutt_bmp, DICKBUTT_HEIGHT, DICKBUTT_WIDTH);

}


void loop() {
  
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

//dickbutt snowflakes
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[DICKBUTTS][11];
 
  // initialize
  for (uint8_t f=0; f< DICKBUTTS; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);

  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< DICKBUTTS; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< DICKBUTTS; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }

    }

   }
}




void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("DICKBUTT?");
  display.display();
  delay(1);
 
  /*display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  */    
  display.startscrolldiagright(0x00, 0x0F);
  delay(1000);
  display.startscrolldiagleft(0x00, 0x0F);
  delay(1000);
  display.stopscroll();
    display.startscrolldiagright(0x00, 0x0F);
  delay(1000);
  display.startscrolldiagleft(0x00, 0x0F);
  delay(1000);
  display.stopscroll();
    display.startscrolldiagright(0x00, 0x0F);
  delay(1000);
  display.startscrolldiagleft(0x00, 0x0F);
  delay(1000);
  display.stopscroll();
    display.startscrolldiagright(0x00, 0x0F);
  delay(1000);
  display.startscrolldiagleft(0x00, 0x0F);
  delay(1000);
  display.stopscroll();
}
