// For Color Text on 8 Parallel WS2812 strings 
// Features: Bluetooth support, 2 Lines, 8x8 Font
// by: BOB Davis  February 2020

// Split between Ports B and D to allow serial communications on D0&D1
// Displays 2 lines of text switching between them.
// PORTD is Digital Pins 0-7 (Uses D4-D7=Top 4 lines of text) 
// POPRB is Digital Pins 8-13 (Uses D8-D11=Bottom 4 lines of text)

// Colors: R=Red, G=Green, B=Blue, W=White
// Colors: N=Black, Y=Yellow, P=Purple, C=Cyan
// Effects: F=Flashing, A=Alternating
 
#define PIXEL_PORT   PORTD  // Port the pixels are connected to
#define PIXEL_DDR    DDRD   // Port the pixels are connected to
#define PIXEL_PORTB  PORTB  // Port the pixels are connected to
#define PIXEL_DDRB   DDRB   // Port the pixels are connected to
#include <EEPROM.h>
void writeString(char add,String data);
String read_String(char add);

// Variables for colors of letters and background
int red=12; int green=12; int blue=12;
int redb=0; int greenb=0; int blueb=0;

// Format: RGB (foreground) then RGB (Background) then text
String text1="GN Testing12345678901234567890  ";
String text2="AN This is a test of this sign  ";
String textT="  ";
int ind1; // Delimiter locations
int ind2;

// Send the next set of 8 WS2812B encoded bits to the 8 pins.
// The delay timing is for an Arduino UNO.
void sendBits( byte bits ) {
  PORTD= 0xFF;  // turn on
  PORTB= 0xFF;  // turn on
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay
  PORTD= 0xFF;  // delay (add more for faster processors)
  PORTD= bits;  // send data
  PORTB= bits;  // send data
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= bits;  // delay
  PORTD= 0x00;  // Turn off;
  PORTB= 0x00;  // Turn off;
}

// Send bytes to LED's, no loops for maximum speed!
void sendPixelCol(byte Col) {
    if (greenb&0x80)sendBits(255-Col); // background 
    else if (green&0x80)sendBits(Col); else sendBits(0x00);  
    if (greenb&0x40)sendBits(255-Col); // background 
    else if (green&0x40)sendBits(Col); else sendBits(0x00);  
    if (greenb&0x20)sendBits(255-Col); // background 
    else if (green&0x20)sendBits(Col); else sendBits(0x00);  
    if (greenb&0x10)sendBits(255-Col); // background 
    else if (green&0x10)sendBits(Col); else sendBits(0x00);  
    if (greenb&0x08)sendBits(255-Col); // background 
    else if (green&0x08)sendBits(Col); else sendBits(0x00);  
    if (greenb&0x04)sendBits(255-Col); // background 
    else if (green&0x04)sendBits(Col); else sendBits(0x00);  
    if (greenb&0x02)sendBits(255-Col); // background 
    else if (green&0x02)sendBits(Col); else sendBits(0x00);  
    if (greenb&0x01)sendBits(255-Col); // background 
    else if (green&0x01)sendBits(Col); else sendBits(0x00); 
           
    if (redb&0x80)sendBits(255-Col); // background 
    else if (red & 0x80)sendBits(Col); else sendBits(0x00);  
    if (redb&0x40)sendBits(255-Col); // background 
    else if (red & 0x40)sendBits(Col); else sendBits(0x00);  
    if (redb&0x20)sendBits(255-Col); // background 
    else if (red & 0x20)sendBits(Col); else sendBits(0x00);  
    if (redb&0x10)sendBits(255-Col); // background 
    else if (red & 0x10)sendBits(Col); else sendBits(0x00);  
    if (redb&0x08)sendBits(255-Col); // background 
    else if (red & 0x08)sendBits(Col); else sendBits(0x00);  
    if (redb&0x04)sendBits(255-Col); // background 
    else if (red & 0x04)sendBits(Col); else sendBits(0x00);  
    if (redb&0x02)sendBits(255-Col); // background 
    else if (red & 0x02)sendBits(Col); else sendBits(0x00);  
    if (redb&0x01)sendBits(255-Col); // background 
    else if (red & 0x01)sendBits(Col); else sendBits(0x00);
      
    if (blueb&0x80)sendBits(255-Col); // background 
    else if (blue & 0x80)sendBits(Col); else sendBits(0x00);  
    if (blueb&0x40)sendBits(255-Col); // background 
    else if (blue & 0x40)sendBits(Col); else sendBits(0x00);  
    if (blueb&0x20)sendBits(255-Col); // background 
    else if (blue & 0x20)sendBits(Col); else sendBits(0x00);  
    if (blueb&0x10)sendBits(255-Col); // background 
    else if (blue & 0x10)sendBits(Col); else sendBits(0x00);  
    if (blueb&0x08)sendBits(255-Col); // background 
    else if (blue & 0x08)sendBits(Col); else sendBits(0x00);  
    if (blueb&0x04)sendBits(255-Col); // background 
    else if (blue & 0x04)sendBits(Col); else sendBits(0x00);  
    if (blueb&0x02)sendBits(255-Col); // background 
    else if (blue & 0x02)sendBits(Col); else sendBits(0x00);  
    if (blueb&0x01)sendBits(255-Col); // background 
    else if (blue & 0x01)sendBits(Col); else sendBits(0x00); 
 }

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++) {  EEPROM.write(add+i,data[i]);  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
//  EEPROM.commit();
}
 
String read_String(char add){
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500) {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
   
// This 8x8 Basic font from http://asecular.com/maxmatrix/
byte font[][8] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // space
  0x00,0x00,0x00,0x30,0x79,0x79,0x30,0x00, // !
  0x00,0x00,0x60,0x70,0x00,0x70,0x60,0x00, // "
  0x14,0x7F,0x7f,0x14,0x7f,0x7f,0x14,0x00, // #
  0x00,0x00,0x12,0x2a,0x6b,0x2a,0x24,0x00, // $
  0x00,0x62,0x66,0x0c,0x18,0x33,0x23,0x00, // %
  0x26,0x7f,0x51,0x59,0x77,0x23,0x05,0x00, // &
  0x00,0x00,0x00,0x08,0x78,0x70,0x00,0x00, // '
  0x00,0x00,0x00,0x1c,0x3e,0x63,0x41,0x00, // (
  0x00,0x00,0x41,0x63,0x3e,0x1c,0x00,0x00, // )
  0x08,0x2a,0x3e,0x1C,0x3e,0x2a,0x08,0x00, // *
  0x00,0x00,0x08,0x08,0x3e,0x08,0x08,0x00, // +
  0x00,0x00,0x01,0x0f,0x0e,0x00,0x00,0x00, // ,
  0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x00, // -
  0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00, // .
  0x00,0x02,0x06,0x0C,0x18,0x30,0x20,0x00, // /
  0x00,0x3e,0x7f,0x49,0x51,0x7f,0x3e,0x00, // 0
  0x00,0x01,0x11,0x7f,0x7f,0x01,0x01,0x00, // 1
  0x00,0x23,0x67,0x45,0x49,0x79,0x31,0x00, // 2
  0x00,0x22,0x63,0x49,0x49,0x7f,0x36,0x00, // 3
  0x00,0x0c,0x14,0x24,0x7f,0x7f,0x04,0x00, // 4
  0x00,0x72,0x73,0x51,0x51,0x5f,0x4e,0x00, // 5
  0x00,0x3e,0x7f,0x49,0x49,0x6f,0x26,0x00, // 6
  0x00,0x60,0x60,0x47,0x5f,0x78,0x60,0x00, // 7
  0x00,0x36,0x7f,0x49,0x49,0x7f,0x36,0x00, // 8
  0x00,0x32,0x7b,0x49,0x49,0x7f,0x3e,0x00, // 9
  0x00,0x00,0x00,0x00,0x36,0x36,0x00,0x00, // :
  0x00,0x00,0x00,0x01,0x37,0x36,0x00,0x00, // ;
  0x00,0x00,0x08,0x1c,0x36,0x63,0x41,0x00, // <
  0x00,0x00,0x00,0x14,0x14,0x14,0x14,0x00, // =
  0x00,0x41,0x63,0x36,0x1c,0x08,0x00,0x00, // >
  0x00,0x20,0x60,0x4d,0x4d,0x78,0x30,0x00, // ?
  0x00,0x3c,0x42,0x5a,0x5a,0x32,0x04,0x00, // @
  0x00,0x3f,0x7f,0x48,0x48,0x7f,0x3f,0x00, // A
  0x00,0x7f,0x49,0x49,0x7f,0x7f,0x36,0x00, // B
  0x00,0x3e,0x7f,0x41,0x41,0x63,0x22,0x00, // C
  0x00,0x7f,0x7f,0x41,0x41,0x7f,0x3e,0x00, // D
  0x00,0x7f,0x7f,0x49,0x49,0x49,0x41,0x00, // E
  0x00,0x7f,0x7f,0x48,0x48,0x48,0x40,0x00, // F
  0x00,0x3e,0x7f,0x41,0x45,0x67,0x26,0x00, // G
  0x00,0x7f,0x7f,0x08,0x08,0x7f,0x7f,0x00, // H
  0x00,0x00,0x00,0x41,0x7f,0x7f,0x41,0x00, // I
  0x00,0x06,0x07,0x41,0x7f,0x7e,0x40,0x00, // J
  0x00,0x7f,0x7f,0x1c,0x36,0x63,0x41,0x00, // K
  0x00,0x7f,0x7f,0x01,0x01,0x01,0x01,0x00, // L
  0x7f,0x7f,0x30,0x18,0x30,0x7f,0x7f,0x00, // M
  0x7f,0x7f,0x30,0x18,0x0c,0x7f,0x7f,0x00, // N
  0x00,0x3e,0x7f,0x41,0x41,0x7f,0x3e,0x00, // O
  0x00,0x7f,0x7f,0x44,0x44,0x7c,0x38,0x00, // P
  0x00,0x3c,0x7e,0x42,0x46,0x7f,0x3d,0x00, // Q
  0x00,0x7f,0x7f,0x4c,0x4e,0x7b,0x31,0x00, // R
  0x00,0x32,0x7b,0x49,0x49,0x6f,0x26,0x00, // S
  0x00,0x60,0x40,0x7f,0x7f,0x40,0x60,0x00, // T
  0x00,0x7e,0x7f,0x01,0x01,0x7f,0x7f,0x00, // U
  0x00,0x7c,0x7e,0x03,0x03,0x7e,0x7c,0x00, // V
  0x7f,0x7f,0x06,0x0c,0x06,0x7f,0x7f,0x00, // W
  0x63,0x77,0x1c,0x08,0x1c,0x77,0x63,0x00, // X
  0x00,0x70,0x78,0x0f,0x0f,0x78,0x70,0x00, // Y
  0x00,0x43,0x47,0x4d,0x59,0x71,0x61,0x00, // Z
};

void sendline(String line) {
  cli();                     // No time for interruptions!
  for (int l=3; l<36; l++){  // 36 is number of characters to send
    int x =l%3;  // remainder of l / 3
    if (((line)[0])=='A') { // Alternating
      if (x==0) red=128, green=000, blue=000;
      if (x==1) red=000, green=128, blue=000;
      if (x==2) red=000, green=000, blue=128;
    }
    // Using a loop can be too slow with the character lookups.
    if (font[(line)[l]-32][0]!= 0x00)sendPixelCol(font[(line)[l]-32][0]); 
    if (font[(line)[l]-32][1]!= 0x00)sendPixelCol(font[(line)[l]-32][1]);  
    if (font[(line)[l]-32][2]!= 0x00)sendPixelCol(font[(line)[l]-32][2]);  
    sendPixelCol(font[(line)[l]-32][3]);  // -32 is to correct ascii
    sendPixelCol(font[(line)[l]-32][4]);  
    sendPixelCol(font[(line)[l]-32][5]);  
    sendPixelCol(font[(line)[l]-32][6]);  
    sendPixelCol(font[(line)[l]-32][7]);  // Last line is always 0x00
  }
  sei();
}

void setup() {
  Serial.begin(9600);    // opens serial port, data rate 9600 bps
  PIXEL_DDR = 0xF0;      // Set pins to output Cannot use D0 and D1! 
  PIXEL_DDRB = 0x0F;     // Set pins to output 
}
void loop() {
  if (Serial.available() > 0) {
    text2=text1;
    text1=Serial.readString(); 
    for(int i = text1.length(); i < 40; i++){ text1 += ' '; }
    text1.toUpperCase();
    writeString(10, text1+"~"+text2+"~");  // Strings to EEPROM
  }
  // Pad length to 40 characters, upper case
  for(int i = text1.length(); i < 40; i++){ text1 += ' '; }
  for(int i = text2.length(); i < 40; i++){ text2 += ' '; }
  text1.toUpperCase();
  text2.toUpperCase();
  
  //  String Recived Data;
  textT = read_String(10);  // Strings from EEPROM
  Serial.print("Read Data:");
  Serial.println(textT);

  ind1 = textT.indexOf('~');          //finds location of first ~
  text1 = textT.substring(0, ind1);   //captures first String
  ind2 = textT.indexOf('~', ind1+1 );  //finds location of second ~
  text2 = textT.substring(ind1+1, ind2); //captures second String

  // Read colors from string, 
  if ((text1[0])=='R') red=128, green=000, blue=000;
  if ((text1[0])=='G') red=000, green=128, blue=000;
  if ((text1[0])=='B') red=000, green=000, blue=128;
  if ((text1[0])=='W') red=128, green=128, blue=128;
  if ((text1[0])=='F') red=128, green=128, blue=128;
  if ((text1[0])=='Y') red=128, green=128, blue=000;
  if ((text1[0])=='P') red=128, green=000, blue=128;
  if ((text1[0])=='C') red=000, green=128, blue=128;
  if ((text1[0])=='N') red=000, green=000, blue=000;
  if ((text1[1])=='R') redb=8, greenb=0, blueb=0;
  if ((text1[1])=='G') redb=0, greenb=8, blueb=0;
  if ((text1[1])=='B') redb=0, greenb=0, blueb=8;
  if ((text1[1])=='W') redb=8, greenb=8, blueb=8;
  if ((text1[1])=='Y') redb=8, greenb=8, blueb=0;
  if ((text1[1])=='P') redb=8, greenb=0, blueb=8;
  if ((text1[1])=='C') redb=0, greenb=8, blueb=8;
  if ((text1[1])=='N') redb=0, greenb=0, blueb=0;
  //Serial.print(text1);

  if ((text1[0])=='F'){
    sendline(text1);
    delay(1000);               // Wait to display results
    for (int l=1; l<250; l++){ sendPixelCol(0x00); }
    delay(1000);               // Wait to display results
    sendline(text1);
    delay(1000);               // Wait to display results
    for (int l=1; l<250; l++){ sendPixelCol(0x00); }
    delay(1000);               // Wait to display results
    sendline(text1);
    delay(1000);               // Wait to display results
  }
  else {
    sendline(text1);
    delay(4000);               // Wait to display results
  }
     
  // Get New foreground and background colors
  if ((text2[0])=='R') red=128, green=000, blue=000;
  if ((text2[0])=='G') red=000, green=128, blue=000;
  if ((text2[0])=='B') red=000, green=000, blue=128;
  if ((text2[0])=='W') red=128, green=128, blue=128;
  if ((text2[0])=='F') red=128, green=128, blue=128;
  if ((text2[0])=='Y') red=128, green=128, blue=000;
  if ((text2[0])=='P') red=128, green=000, blue=128;
  if ((text2[0])=='C') red=000, green=128, blue=128;
  if ((text2[0])=='N') red=000, green=000, blue=000;
  if ((text2[1])=='R') redb=8, greenb=0, blueb=0;
  if ((text2[1])=='G') redb=0, greenb=8, blueb=0;
  if ((text2[1])=='B') redb=0, greenb=0, blueb=8;
  if ((text2[1])=='W') redb=8, greenb=8, blueb=8;
  if ((text2[1])=='Y') redb=8, greenb=8, blueb=0;
  if ((text2[1])=='P') redb=8, greenb=0, blueb=8;
  if ((text2[1])=='C') redb=0, greenb=8, blueb=8;
  if ((text2[1])=='N') redb=0, greenb=0, blueb=0;

  if ((text2[0])=='F'){
    sendline(text2);
    delay(1000);               // Wait to display results
    for (int l=1; l<250; l++){ sendPixelCol(0x00); }
    delay(1000);               // Wait to display results
    sendline(text2);
    delay(1000);               // Wait to display results
    for (int l=1; l<250; l++){ sendPixelCol(0x00); }
    delay(1000);               // Wait to display results
    sendline(text2);
    delay(1000);               // Wait to display results
  }
  else {
    sendline(text2);
    delay(4000);               // Wait to display results
  }
  return;  
}
