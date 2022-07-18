// Paint example specifically for the TFTLCD breakout board.
// If using the Arduino shield, use the tftpaint_shield.pde sketch instead!
// DOES NOT CURRENTLY WORK ON ARDUINO LEONARDO
//#include <stdint.h>
//#include <Adafruit_GFX.h>    // Core graphics library
#include <TftSpfd5408.h> // Hardware-specific library
#include "TouchScreen.h"
#include <Wire.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif


#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
int touch = 0 ;

char Rxcommand = 'a' ;
char x='a';
String s="song";
int temp=1;


TftSpfd5408 tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

void setup(void) {
  Serial.begin(9600);
  Serial.print("hi");
  tft.print(temp);
  Serial.println(F("Paint!"));
  Wire.begin(5);
  
  tft.reset();

  tft.begin(0x9341);
  tft.setRotation(3);
  tft.fillScreen(BLACK);

  tft.setTextColor(WHITE);  
  tft.setTextSize(2);  
  tft.fillScreen(BLACK);  

  tft.fillTriangle(180,100,180,130,200,115,WHITE);

  tft.fillRect(130,100,10,30,WHITE);
  tft.fillRect(115,100,10,30,WHITE);

  
  tft.fillTriangle(250,100,250,130,270,115,WHITE); 
 tft.fillRect(270,100,5,30,WHITE);
 
  tft.fillTriangle(70,100,70,130,50,115,WHITE);
  tft.fillRect(50,100,5,30,WHITE); 
  
  tft.fillRect(50,200,20,5,WHITE);

  tft.fillRect(250,200,20,5,WHITE); 
 tft.fillRect(257,192,5,20,WHITE);



  /*tft.fillRect(0, 0, 120, 120, GREEN);  
  tft.fillRect(120, 0, 120, 120, RED);  
  tft.setCursor(15, 45);  
  tft.println("LED ON");  
  tft.setCursor(128, 45);  
  tft.println("LED OFF");  */
  tft.setTextColor(WHITE, BLACK);  
  tft.setTextSize(8);  
  
 
  currentcolor = RED;
 
  pinMode(13, OUTPUT);
   // Join as Slav e on addr e s s 5
  // Attach a f unc t i on to t r i g g e r when something i s r e c e i v e d .
  Wire.onReceive ( receiveEvent ) ;
  Wire.onRequest(requestEvent);
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void receiveEvent ( int x ) {
  temp=Wire.read();
  //s="song"+temp;

}

void requestEvent() {
  
    if (touch==4){
    Wire.write('n');}
    if (touch==1){
    Wire.write('p');}
    if (touch==6){
    Wire.write('q');}
    if (touch==5){
    Wire.write('w');}
    if (touch==2){
    Wire.write('e');}
    if (touch==3){
    Wire.write('o');}
}


void loop()
{
  TSPoint p = ts.getPoint();
   touch=0;
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);


  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    Serial.println("px " + p.x);
    Serial.println("py "+p.y);
    Serial.println(s);
    //tft.print(temp);

    
      if (p.x > 100 && p.x < 180) {  
    if (p.y > 200 && p.y < 250) { 
      //x=170 to 200 & y=100 to 130 
     touch = 1;  //backwards p
    }  
   }  
   if (p.x > 100 && p.x < 180) {  
    if (p.y >140 && p.y < 190) {  
      // x=110 to 140 & y=100 to 130
     touch = 2; //pause e
    }  
   }  

   if (p.x > 100 && p.x < 180) {  
    if (p.y > 80 && p.y < 130) {
      // x=250 to 280 & y=100 to 130  
     touch = 3; //play o
    }  
   }

   if (p.x > 100 && p.x < 180) {  
    if (p.y > 0 && p.y < 60) {  
      //x=50 to 70 & y=100 to 130
     touch = 4;  //forward n
    }  
   }

   if (p.x > 240 && p.x < 290) {  
    if (p.y > 200 && p.y < 230) {  
      // x=50 to 80 & y=200 to 230
     touch = 5;  //minus w
    }  
   }

   if (p.x > 250 && p.x < 290) {  
    if (p.y > 0 && p.y < 80) { 
      // x=250 to 280 & y=200 to 230 
     touch = 6;  //plus q
    }  
   }
  }  
  // Process the touch in box 1  
//  if (touch == 1) {  
//   tft.setCursor(100,20);  
//   tft.print(temp);  
//   //touch = 0;  
//   delay(100);  
//  }  
//  // Process the touch in box 2  
//  if (touch == 2) {  
//   tft.setCursor(100,20);  
//   tft.print(temp);  
//   //touch = 0;  
//   delay(100);  
//  }  
//
//  if (touch == 3) {  
//   tft.setCursor(100,20);  
//   tft.print(temp);  
//   //touch = 0;  
//   delay(100);  
//  } 
//
//  if (touch == 4) {  
//   tft.setCursor(100,20);  
//   tft.print(temp);  
//   //touch = 0;  
//   delay(100);  
//  } 
//
//  if (touch == 5) {  
//   tft.setCursor(100,20);  
//   tft.print(temp);  
//   //touch = 0;  
//   delay(100);  
//  } 
//
//  if (touch == 6) {  
//   tft.setCursor(100,20);  
//   tft.print(temp);  
//   //touch = 0;  
//   delay(100);  
//  } 
 tft.setCursor(100,20);  
   tft.print(temp);  
   //touch = 0;  
   delay(100);  
  }
