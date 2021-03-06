// Program for sending data to one WS2812 string
// ZIGZAG text displayed
// By Robert Davis II
// Uses Digital Pin 6 change for other pins. 
int LEDpin=6;
int MaxLed=256;  // how many LED's
char PixelRow;
int textc=128;  // brightness of text

// Set default color for letters 
int red=1; int green=1; int blue=1;

// The delay timing is for an Arduino UNO.
// Sorry digitalWrite is too slow to use.
void sendBit( uint8_t bits ) {
  PORTD= 0xF0;  // turn on
  PORTD= 0xF0;  // delay
  PORTD= 0xF0;  // delay
  PORTD= 0xF0;  // delay
  PORTD= 0xF0;  // delay (Add more for faster processors)
  PORTD= bits;  // send data
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= 0x00;  // Turn off;
}

void sendColor( uint8_t row ) {
 // Send the bit 8 times down the row, each pixel is 8 bits each for R,G,B
 int mask = 0x01;  // shifting mask to determine bit status
    for (int bit=8; bit>0; bit--){       
      if (green & (mask<<bit))sendBit( row ); else sendBit( 0x00 ); }
    for (int bit=8; bit>0; bit--){       
      if (red & (mask<<bit))sendBit( row ); else sendBit( 0x00 ); }
    for (int bit=8; bit>0; bit--){       
      if (blue & (mask<<bit))sendBit( row ); else sendBit( 0x00 ); }
 }

char text1[]="ARDUINO POWERED WS2812 LED SIGN                    ";

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
0x00,0x00,0xfe,0x82,0x82,0x00, // [
0x40,0x20,0x10,0x08,0x04,0x00, // slash
0x82,0x82,0xfe,0x00,0x00,0x00, // ]
0x20,0x40,0x80,0x40,0x20,0x00, // ^
0x02,0x02,0x02,0x02,0x02,0x00, // _
0x00,0x80,0x40,0x20,0x00,0x00, // `
0x00,0x10,0x6c,0x82,0x00,0x00, // {
0x00,0x00,0xfe,0x00,0x00,0x00, // |
0x00,0x82,0x6c,0x10,0x00,0x00, // }
0x10,0x10,0x54,0x38,0x10,0x00, // ~
0x10,0x38,0x54,0x10,0x10,0x00, // 
};
 
void setup() {
  pinMode (LEDpin, OUTPUT);
  }
  
void loop() {
  // RED COLOR TEST
  red=1; green=0; blue=0;
  cli();                        // No time for interruptions!
  for (int l=0; l<MaxLed/4; l++){     //  number of LED's
    red=l;
    sendColor( 0xF0);       // Light All red
    }
  // GREEN COLOR TEST
  red=0; green=1; blue=0;
  for (int l=0; l<MaxLed/4; l++){     //  number of LED's
    green=l;
    sendColor( 0xF0);       // Light All green
    }
  // BLUE COLOR TEST
  red=0; green=0; blue=1;
  for (int l=0; l<MaxLed/4; l++){     //  number of LED's
    blue=l;
    sendColor( 0xF0);       // Light All blue
    }
  // WHITE COLOR TEST
  for (int l=0; l<MaxLed/4; l++){     //  number of LED's
    red=l; green=l; blue=l;
    sendColor( 0xF0);       // Light All white
    }
  sei();
  delay(2000);

  //TEXT with ZIGZAG layout tested bit order reverses for each column.
  cli();                        // No time for interruptions!
  for (int l=0; l<30; l++){     // 30 is number of characters to send
      switch (l){                 // case is faster than if's
      case 0: red=textc; green=0; blue=0; break; 
      case 1: red=0; green=textc; blue=0; break; 
      case 2: red=0; green=0; blue=textc; break; 
      case 3: red=textc; green=0; blue=0; break; 
      case 4: red=0; green=textc; blue=0; break; 
      case 5: red=0; green=0; blue=textc; break; 
    }
    for (int r=0; r<6; r++) {
      PixelRow=(font[text1[l]-32][r]); // -32 is to get to correct ascii
      if (r & 0x01){     // invert odd rows
      // Using a loop and shifting is too slow with the character lookups.
      if (PixelRow & 0x01 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x02 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x04 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x08 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x10 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x20 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x40 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x80 ) sendColor (0xF0); else sendColor (0x00);
      }
      else{
      if (PixelRow & 0x80 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x40 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x20 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x10 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x08 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x04 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x02 ) sendColor (0xF0); else sendColor (0x00);
      if (PixelRow & 0x01 ) sendColor (0xF0); else sendColor (0x00);
      }
    }
  }
  sei();
  delay(4000);                  // Wait to display results

  // FIREWORKS
  red=textc; green=textc; blue=textc;  
  cli();                        // No time for interruptions!
  for (int cycle=0; cycle<500; cycle++){
    int rano=random(MaxLed);        // Set Random location
    for (int l=0; l<MaxLed; l++){   // number of bytes to send
      if (l==rano) sendColor( 0xF0); else sendColor( 0x00);  
    } 
    delay(20); 
  }
  sei();
  return;  
}

