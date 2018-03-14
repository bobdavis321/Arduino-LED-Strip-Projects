// Version for sending data to 8 Parallel WS2812 strings
// By BOB Davis 
// Removed Assembler and simplified the code
// Changed to VU meter with MSGEQ7

// PORTD is Digital Pins 0-7 on the Uno change for other boards. 
#define PIXEL_PORT  PORTD  // Port they are connected to
#define PIXEL_DDR   DDRD   // Port thry are connected to
int textb=128;  // Brightness of text
int maxled=180; // Number of LED's

// MSGEQ7 pins
#define PIN_STROBE 9
#define PIN_RESET 10
#define PIN_LEFT 4 //analog input
#define PIN_RIGHT 5 //analog input
#define PIN2_LEFT 2 //analog input
#define PIN2_RIGHT 3 //analog input

//band arrays
int left[7]; 
int right[7];
int left2[7]; 
int right2[7];
int col=0;

void readMSGEQ7() { //reset the chip
  digitalWrite(PIN_RESET, HIGH);
  digitalWrite(PIN_RESET, LOW);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(30);             // gather data
    left[band] = analogRead(PIN_LEFT); // store left band reading
    right[band] = analogRead(PIN_RIGHT); // store right band reading
    left2[band] = analogRead(PIN2_LEFT); // store left band reading
    right2[band] = analogRead(PIN2_RIGHT); // store right band reading
    digitalWrite(PIN_STROBE,HIGH);     // reset the strobe pin
  }
}

// Actually send the next set of 8 WS2812B encoded bits to the 8 pins.
// The delay timing is for an Arduino UNO.
void sendBitX8( uint8_t bits ) {
  PORTD= 0xFF;  // turn on
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay (Remove for faster processors)
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

void setup() {
  PIXEL_DDR = 0xff;    // Set all row pins to output
  pinMode(PIN_RESET, OUTPUT); // reset
  pinMode(PIN_STROBE, OUTPUT); // strobe
}

void loop() {
    readMSGEQ7();                   // collect samples
    cli();                          // No time for interruptions!
    for (int b=0; b<maxled/2; b++){      //90 is number of bytes to send
      if (b < maxled/4) {red=0; green=textb; blue=0;}
      if (b > maxled/4+10) {red=textb; green=textb;}
      if (b > maxled/4+20) {red=textb; green=0;}
      col=0;
      if (left2[3]-128 >= b) col=col+1;  // Send bytes as VU meter data
      if (left[3]-128 >= b) col=col+2;  // Send bytes as VU meter data
      if (left2[4]-128 >= b) col=col+4;  // Send bytes as VU meter data
      if (left[4]-128 >= b) col=col+8;  // Send bytes as VU meter data
      if (left2[5]-128 >= b) col=col+16;  // Send bytes as VU meter data
      if (left[5]-128 >= b) col=col+32;  // Send bytes as VU meter data
      if (left2[6]-128 >= b) col=col+64;  // Send bytes as VU meter data
      if (left[6]-128 >= b) col=col+128;  // Send bytes as VU meter data
      sendPixelRow(col);
      }   
       
    for (int b=0; b<maxled/2; b++){      //90 is number of bytes to send
      if (b < maxled/4) {red=0; green=textb; blue=0;}
      if (b > maxled/4+10) {red=textb; green=textb;}
      if (b > maxled/4+20) {red=textb; green=0;}
      col=0;
      if (left2[0]-128 >= b) col=col+4;  // Send bytes as VU meter data
      if (left[0]-128 >= b) col=col+8;  // Send bytes as VU meter data
      if (left2[1]-128 >= b) col=col+16;  // Send bytes as VU meter data
      if (left[1]-128 >= b) col=col+32;  // Send bytes as VU meter data
      if (left2[2]-128 >= b) col=col+64;  // Send bytes as VU meter data
      if (left[2]-128 >= b) col=col+128;  // Send bytes as VU meter data
      if ((left2[0]+left2[1]+left2[2]+left2[3]+left2[4]+left2[5]+left2[6]+left2[7])/7-128 >= b) col=col+1;  
      if ((left[0]+left[1]+left[2]+left[3]+left[4]+left[5]+left[6]+left[7])/7-128 >= b) col=col+2;  
      sendPixelRow(col);
      }
      

    sei();                        // interrupts back on
    delay (50);
//  }
}

