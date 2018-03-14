// Program for sending data to one WS2812 string
// By Robert Davis II
// Uses Digital Pin 6 change for other pins. 
int LEDpin=6;
int MaxLed=256;
int DotBright=64; // sets your brightness

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

void sendColor( int red, int green, int blue ) {
 // Send the bit 8 times down the row, each pixel is 8 bits each for R,G,B
  int mask = 0x01;  // shifting mask to determine bit status
    for (int bit=8; bit>0; bit--){       
      if (green & (mask<<bit))sendBit( 0xF0 ); else sendBit( 0x00 ); }
    for (int bit=8; bit>0; bit--){       
       if (red & (mask<<bit))sendBit( 0xF0 ); else sendBit( 0x00 ); }
    for (int bit=8; bit>0; bit--){       
       if (blue & (mask<<bit))sendBit( 0xF0 ); else sendBit( 0x00 ); }
 }
 
void setup() {
  pinMode (LEDpin, OUTPUT);
  }
  
void loop() {
  // RED COLOR TEST
  cli();                        // No time for interruptions!
  for (int l=0; l<MaxLed; l++){     //  number of LED's
    sendColor( l*2, 0, 0);       // Light All red
    }
  delay(300000);
  sei();

  // GREN COLOR TEST
  cli();                        // No time for interruptions!
  for (int l=0; l<MaxLed; l++){     //  number of LED's
    sendColor( 0, l*2, 0);       // Light All green
    }
  delay(300000);
  sei();

  // BLUE COLOR TEST
  cli();                        // No time for interruptions!
  for (int l=0; l<MaxLed; l++){     //  number of LED's
    sendColor( 0, 0, l*2);       // Light All blue
    }
  delay(300000);
  sei();

  // CLEAR SCREEN
  cli();                        // No time for interruptions!
  for (int l=0; l<MaxLed; l++){     //  number of LED
    sendColor( 0, 0, 0);       // clear the screen
  }
  sei();

  // WORM TEST
  cli();                        // No time for interruptions!
  int worm = 1;
  for (int cycle=1; cycle<MaxLed; cycle++){
    for (int l=0; l<MaxLed; l++){     //  number of LED's
      if (l==worm)   sendColor( DotBright, DotBright, DotBright); // Light All
      if (l==worm-1) sendColor( DotBright, 0, 0);       // Light red
      if (l==worm-2) sendColor( 0, DotBright, 0);       // Light green
      if (l==worm-3) sendColor( 0, 0, DotBright);       // Light blue
      if (l <worm-3) sendColor( 0, 0, 0);       // Erase old
    }
    worm++;
    delay(20000); 
  }
  delay(20);
  sei();

  // FIREWORKS
  cli();                        // No time for interruptions!
  for (int cycle=0; cycle<500; cycle++){
    int rano=random(MaxLed);        // Set Random location
    for (int l=0; l<MaxLed; l++){   // number of bytes to send
      if (l==rano) sendColor( DotBright, DotBright, DotBright); 
      else         sendColor( 0, 0, 0);  
    } 
    delay(20); 
  }
  sei();
  return;  
}

