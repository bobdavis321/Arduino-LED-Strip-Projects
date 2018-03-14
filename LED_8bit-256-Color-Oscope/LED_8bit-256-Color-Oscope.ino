// Version for sending data to 8 Parallel WS2812 strings
// By BOB Davis 
// Changed to Oscope with input on A0 

// PORTD is Digital Pins 0-7 on the Uno change for other boards. 
#define PIXEL_PORT  PORTD  // Port they are connected to
#define PIXEL_DDR   DDRD   // Port thry are connected to
int textb=128;   // Brightness of text
int maxled=180;  // Number of LED's
#define APIN 0   //analog input pin
int right[200];  // number of samples
int col=0;

// Actually send the next set of 8 WS2812B encoded bits to the 8 pins.
// The delay timing is for an Arduino UNO.
void sendBitX8( uint8_t bits ) {
  PORTD= 0xFF;  // turn on
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay (Increse for faster processors)
  PORTD= bits;  // send data
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= 0x00;  // Turn off;
}

// Set default color for letters 
int red=1; int green=textb; int blue=1; 
 
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

void setup() {
  PIXEL_DDR = 0xff;    // Set all row pins to output
}

void loop() {
    for (int s=0; s<maxled/2; s++){
    right[s]=analogRead(APIN);  // collect samples
    delay(1);                 // Sample interval
    }
    cli();                    // No time for interruptions!
    for (int b=0; b<(maxled/2); b++){ 
      col=0x01;               // Set initial value
      col=col<<right[b]/32;   // Shift active bit up to match level
      col=col>>8;             // Shift dumps the lower 8
      if (col&0x80) {red=textb; green=0;}
      else {red=0; green=textb;}
      sendPixelRow(col);
    }
    red=0; green=textb; blue=0;
    //  Bottom half
    for (int b=0; b<(maxled/2); b++){ 
      col=0x01;               // Set initial value
      col=col<<right[b]/32;   // Shift active bit up to match level
      if (col&0x01) {red=textb; green=0;}
      else {red=0; green=textb;}
      sendPixelRow(col);
    }
    sei();                     // interrupts back on
    delay (50);
}

