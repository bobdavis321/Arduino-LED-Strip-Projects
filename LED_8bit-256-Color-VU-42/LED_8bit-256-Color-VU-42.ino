// Version for sending data to 8 Parallel WS2812 strings
// By BOB Davis 
// Changed to VU meter with MSGEQ7 Supports 6 MSGEQ7's

// PORTD is Digital Pins 0-7 on the Uno change for other boards. 
#define PIXEL_PORT  PORTD  // Port they are connected to
#define PIXEL_DDR   DDRD   // Port thry are connected to
int textb=128;  // Brightness of text
int maxled=180; // Number of LED's

// MSGEQ7 pins
#define PIN_STROBE 9
#define PIN_RESET 10
#define PIN_0 0 //analog input
#define PIN_1 1 //analog input
#define PIN_2 2 //analog input
#define PIN_3 3 //analog input
#define PIN_4 4 //analog input
#define PIN_5 5 //analog input

//band arrays
int left0[7]; 
int right0[7];
int left1[7]; 
int right1[7];
int left2[7]; 
int right2[7];
int col=0;

void readMSGEQ7() { //reset the chip
  digitalWrite(PIN_RESET, HIGH);
  digitalWrite(PIN_RESET, LOW);
  for(int band=0; band < 7; band++) {  //loop thru all 7 bands
    digitalWrite(PIN_STROBE,LOW);      // go to the next band 
    delayMicroseconds(30);             // gather data
    left0[band] = analogRead(PIN_0);   // store band reading
    right0[band] = analogRead(PIN_1);  // store band reading
    left1[band] = analogRead(PIN_2);   // store band reading
    right1[band] = analogRead(PIN_3);  // store band reading
    left2[band] = analogRead(PIN_4);   // store band reading
    right2[band] = analogRead(PIN_5);  // store band reading
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
  pinMode(PIN_RESET, OUTPUT); // reset
  pinMode(PIN_STROBE, OUTPUT); // strobe
}

void loop() {
    readMSGEQ7();             // collect samples
    cli();                    // No time for interruptions!
    for (int b=0; b<7; b++){  //7 is number of freq per MSGEQ7
      col=0x00FF;                  // Set initial value
      col=col<<left0[b]/64;   // Shift active bit up to match level
      col=col>>8;             // Extra shift dumps the noise
      if (col&0x80) {red=textb; green=0;}
      else {red=0; green=textb;}
      sendPixelRow(col);
      col=0x00FF;                  // Set initial value
      col=col<<left1[b]/64;   // Shift active bit up to match level
      col=col>>8;
      if (col&0x80) {red=textb; green=0;}
      else {red=0; green=textb;}
      sendPixelRow(col);
      col=0x00FF;                  // Set initial value
      col=col<<left2[b]/64;   // Shift active bit up to match level
      col=col>>8;
      if (col&0x80) {red=textb; green=0;}
      else {red=0; green=textb;}
      sendPixelRow(col);
    }
    red=0; green=0; blue=textb;
    sendPixelRow(0xFF);       // Left to Right seperator marker.
    red=0; green=textb; blue=0;
    for (int b=0; b<7; b++){  //7 is number of freq per MSGEQ7
      col=0x00FF;                  // Set initial value
      col=col<<right0[b]/64;   // Shift active bit up to match level
      col=col>>8;
      if (col&0x80) {red=textb; green=0;}
      else {red=0; green=textb;}
      sendPixelRow(col);
      col=0x00FF;                  // Set initial value
      col=col<<right1[b]/64;   // Shift active bit up to match level
      col=col>>8;
      if (col&0x80) {red=textb; green=0;}
      else {red=0; green=textb;}
      sendPixelRow(col);
      col=0x00FF;                  // Set initial value
      col=col<<right2[b]/64;   // Shift active bit up to match level
      col=col>>8;
      if (col&0x80) {red=textb; green=0;}
      else {red=0; green=textb;}
      sendPixelRow(col);
    }
    sei();                        // interrupts back on
    delay (50);
}

