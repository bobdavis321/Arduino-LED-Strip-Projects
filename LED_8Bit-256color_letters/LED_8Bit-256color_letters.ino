// Version for sending data to 8 Parallel WS2812 strings
// by: BOB Davis  
// Removed Assembler and simplified the code

// PORTD is Digital Pins 0-7 on the Uno change for other boards. 
#define PIXEL_PORT  PORTD  // Port the pixels are connected to
#define PIXEL_DDR   DDRD   // Port the pixels are connected to
int textb=128;  // brightness of text
int maxled=180;

// Send the next set of 8 WS2812B encoded bits to the 8 pins.
// The delay timing is for an Arduino UNO.
void sendBitX8( uint8_t bits ) {
  PORTD= 0xFF;  // turn on
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay (add more for faster processors)
  PORTD= bits;  // send data
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= 0x00;  // Turn off;
}

// Set default color for letters 
int red=1; int green=1; int blue=1;  

void sendPixelRow( uint8_t row ) {
  // Send the bit 8 times down every row, each pixel is 8 bits/color
 int mask = 0x01;  // shifting mask to determine bit status
    for (int bit=8; bit>0; bit--){       
      if (green & (mask<<bit))sendBitX8( row ); else sendBitX8( 0x00 ); }
    for (int bit=8; bit>0; bit--){       
      if (red & (mask<<bit))sendBitX8( row ); else sendBitX8( 0x00 ); }
    for (int bit=8; bit>0; bit--){       
      if (blue & (mask<<bit))sendBitX8( row ); else sendBitX8( 0x00 ); }
 }
    
char text[]="ARDUINO ADXABLE LED PROJECTS    ";

// This font from http://sunge.awardspace.com/glcd-sd/node4.html
byte font[][6] = {
0x00,0x00,0x00,0x00,0x00,0x00, // ascii 32 
0x00,0x00,0xfa,0x00,0x00,0x00, // !
0x00,0xe0,0x00,0xe0,0x00,0x00, // "
0x28,0xfe,0x28,0xfe,0x28,0x00, // #
0x24,0x54,0xfe,0x54,0x48,0x00, // $
0xc4,0xc8,0x10,0x26,0x46,0x00, // %
0x6c,0x92,0xaa,0x44,0x0a,0x00, // &
0x00,0xa0,0xc0,0x00,0x00,0x00, // '
0x00,0x38,0x44,0x82,0x00,0x00, // (
0x00,0x82,0x44,0x38,0x00,0x00, // )
0x10,0x54,0x38,0x54,0x10,0x00, // *
0x10,0x10,0x7c,0x10,0x10,0x00, // +
0x00,0x0a,0x0c,0x00,0x00,0x00, // ,
0x10,0x10,0x10,0x10,0x10,0x00, // -
0x00,0x06,0x06,0x00,0x00,0x00, // .
0x04,0x08,0x10,0x20,0x40,0x00, // /
0x7c,0x8a,0x92,0xa2,0x7c,0x00, // 0
0x00,0x42,0xfe,0x02,0x00,0x00, // 1
0x42,0x86,0x8a,0x92,0x62,0x00, // 2
0x84,0x82,0xa2,0xd2,0x8c,0x00, // 3
0x18,0x28,0x48,0xfe,0x08,0x00, // 4
0xe4,0xa2,0xa2,0xa2,0x9c,0x00, // 5
0x3c,0x52,0x92,0x92,0x0c,0x00, // 6
0x80,0x8e,0x90,0xa0,0xc0,0x00, // 7
0x6c,0x92,0x92,0x92,0x6c,0x00, // 8
0x60,0x92,0x92,0x94,0x78,0x00, // 9
0x00,0x6c,0x6c,0x00,0x00,0x00, // :
0x00,0x6a,0x6c,0x00,0x00,0x00, // ;
0x00,0x10,0x28,0x44,0x82,0x00, // <
0x28,0x28,0x28,0x28,0x28,0x00, // =
0x82,0x44,0x28,0x10,0x00,0x00, // >
0x40,0x80,0x8a,0x90,0x60,0x00, // ?
0x4c,0x92,0x9e,0x82,0x7c,0x00, // @
0x7e,0x90,0x90,0x90,0x7e,0x00, // A
0xfe,0x92,0x92,0x92,0x6c,0x00, // B
0x7c,0x82,0x82,0x82,0x44,0x00, // C
0xfe,0x82,0x82,0x44,0x38,0x00, // D
0xfe,0x92,0x92,0x92,0x82,0x00, // E
0xfe,0x90,0x90,0x80,0x80,0x00, // F
0x7c,0x82,0x82,0x8a,0x4c,0x00, // G
0xfe,0x10,0x10,0x10,0xfe,0x00, // H
0x00,0x82,0xfe,0x82,0x00,0x00, // I
0x04,0x02,0x82,0xfc,0x80,0x00, // J
0xfe,0x10,0x28,0x44,0x82,0x00, // K
0xfe,0x02,0x02,0x02,0x02,0x00, // L
0xfe,0x40,0x20,0x40,0xfe,0x00, // M
0xfe,0x20,0x10,0x08,0xfe,0x00, // N
0x7c,0x82,0x82,0x82,0x7c,0x00, // O
0xfe,0x90,0x90,0x90,0x60,0x00, // P
0x7c,0x82,0x8a,0x84,0x7a,0x00, // Q
0xfe,0x90,0x98,0x94,0x62,0x00, // R
0x62,0x92,0x92,0x92,0x8c,0x00, // S
0x80,0x80,0xfe,0x80,0x80,0x00, // T
0xfc,0x02,0x02,0x02,0xfc,0x00, // U
0xf8,0x04,0x02,0x04,0xf8,0x00, // V
0xfe,0x04,0x18,0x04,0xfe,0x00, // W
0xc6,0x28,0x10,0x28,0xc6,0x00, // X
0xc0,0x20,0x1e,0x20,0xc0,0x00, // Y
0x86,0x8a,0x92,0xa2,0xc2,0x00, // Z
};

void setup() {
  PIXEL_DDR = 0xff;    // Set all row pins to output
}
void loop() {
// 256 SHADE COLOR TEST
  cli();                      // No time for interruptions!
  for (int l=0; l<(maxled/4); l++){ // max number lines to send
    red=l+2; green=0; blue=0;    
    sendPixelRow(0xFF);       // Light red
  }
  for (int l=0; l<(maxled/4); l++){ // max number lines to send
    red=0; green=l+2; blue=0;    
    sendPixelRow(0xFF);       // Light green
  }
  for (int l=0; l<(maxled/4); l++){ // max number lines to send
    red=0; green=0; blue=l+2;    
    sendPixelRow(0xFF);       // Light blue
  }
  for (int l=0; l<(maxled/4); l++){ // max number lines to send
    red=l+2; green=l+2; blue=l+2;    
    sendPixelRow(0xFF);       // Light white
  }
  sei();
  delay(4000);                  // Wait to display results
  
  cli();                        // No time for interruptions!
  for (int l=0; l<30; l++){     // 30 is number of characters to send
    switch (l){                 // case is faster than if's
      case 0: red=textb; green=0; blue=0; break; // red
      case 1: red=0; green=textb; blue=0; break;  // green
      case 2: red=0; green=0; blue=textb; break;  // blue
      case 3: red=textb; green=textb; blue=0; break; //yellow
      case 4: red=0; green=textb; blue=textb; break; // cyan
      case 5: red=textb; green=0; blue=textb; break; // purple
      case 6: red=textb; green=0; blue=0; break; // red
      case 7: red=0; green=textb; blue=0; break;  // green
      case 8: red=0; green=0; blue=textb; break;  // blue
      case 9: red=textb; green=textb; blue=0; break; //yellow
      case 10: red=0; green=textb; blue=textb; break; // cyan
      case 11: red=textb; green=0; blue=textb; break; // purple
      case 12: red=textb; green=0; blue=0; break; // red
      case 13: red=0; green=textb; blue=0; break;  // green
      case 14: red=0; green=0; blue=textb; break;  // blue
      case 15: red=textb; green=textb; blue=0; break; //yellow
      case 16: red=0; green=textb; blue=textb; break; // cyan
      case 17: red=textb; green=0; blue=textb; break; // purple
      case 18: red=textb; green=0; blue=0; break; // red
      case 19: red=0; green=textb; blue=0; break;  // green
      case 20: red=0; green=0; blue=textb; break;  // blue
      case 21: red=textb; green=textb; blue=0; break; //yellow
      case 22: red=0; green=textb; blue=textb; break; // cyan
      case 23: red=textb; green=0; blue=textb; break; // purple
      case 24: red=textb; green=0; blue=0; break; // red
      case 25: red=0; green=textb; blue=0; break;  // green
      case 26: red=0; green=0; blue=textb; break;  // blue
      case 27: red=textb; green=textb; blue=0; break; //yellow
      case 28: red=0; green=textb; blue=textb; break; // cyan
      case 29: red=textb; green=0; blue=textb; break; // purple
    }
    // Using a loop is too slow with the character lookups.
    sendPixelRow(font[text[l]-32][0]); // -32 is to get to correct ascii
    sendPixelRow(font[text[l]-32][1]); // -32 is to get to correct ascii
    sendPixelRow(font[text[l]-32][2]); // -32 is to get to correct ascii
    sendPixelRow(font[text[l]-32][3]); // -32 is to get to correct ascii
    sendPixelRow(font[text[l]-32][4]); // -32 is to get to correct ascii
    sendPixelRow(font[text[l]-32][5]); // -32 is to get to correct ascii
  }
  sei();
  delay(4000);                  // Wait to display results

  cli();                        // No time for interruptions!
  for (int l=0; l<maxled; l++){     // 30 is number of characters to clear
    sendPixelRow(0x00);       // clear the screen
  }
  sei();

// FIREWORKS
  cli();                        // No time for interruptions!
  red=textb;  green=textb;  blue=textb;
  for (int cycle=0; cycle<100; cycle++){
    int rabit=random(7);
    byte ls=0x01;
    byte sbit=ls << rabit;      // Set up random bit
    int rano=random(maxled);        // Set Random location
    for (int l=0; l<maxled; l++){   // 180 is number of bytes to send
      if (l==rano) sendPixelRow(sbit); else sendPixelRow(0x00);  
    } 
    delay(20); 
  }
  sei();
  return;  
}

