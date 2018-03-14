// Version for sending data to 8 Parallel WS2812 strings
// by: BOB Davis  
// Random number Fireplace 

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
  PORTD= 0x00;  // Turn off
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


void setup() {
  PIXEL_DDR = 0xff;    // Set all row pins to output
}
void loop() {
// More intense fireworks
  int rnum[180];
  int solidt[180];
  int solidb[180];

  for (int n=0; n<maxled/2; n++){
    rnum[n]=random(16); // random 0 to 15
  }
  for (int c=0; c<16; c++){
    for (int n=0; n<maxled/2; n++){
      // processing must be done here it takes too long in display loop
      int ls=0x00001;    
//      ls=ls << rnum[n]-c;
      solidb[n]=ls <<rnum[n]-c;
//      ls=ls >> 8;
      solidt[n]=solidb[n]>>8;
    }
    cli();                        // No time for interruptions!
    red=textb;  green=0;  blue=0;
    for (int l=0; l<maxled/2; l++){   // number of bytes to send
      sendPixelRow(solidt[l]);  
    } 
    for (int l=0; l<maxled/2; l++){   // number of bytes to send
      sendPixelRow(solidb[l]);  
    } 
  delay(5000);
  } 
  sei();
  
//  return;  
}

