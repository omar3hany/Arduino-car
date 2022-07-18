

//#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>

DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int slaveAddress = 5 ;
char x='a';

void setup()
{

  Serial1.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
   // while(true){
   //   delay(0); // Code to compatible with ESP8266 watch dog.
    //}
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3

//  
//  Serial1.begin(9600);
//    Serial.begin(11);
//
//   Serial1.print("setup1");
//  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
//    while(true);
//  }
//  Serial1.print("setup2");
//  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
//  myDFPlayer.play(1);  //Play the first mp3
  Wire.begin() ;
}

void loop()
{
//  Serial.println("loop");
  static unsigned long timer = millis();
  Wire.beginTransmission(5);
  byte error=Wire.endTransmission();
 // Serial.println(error);
  Wire.requestFrom(5, 1);
 // Serial.println(Wire.available());
   while (Wire.available()) { // slave may send less than requested
     x = Wire.read(); // receive a byte as character
       // print the character
  } 
//  if (millis() - timer > 3000) {
//    timer = millis();
//    myDFPlayer.next();  //Play next mp3 every 3 second.
//  }

 // if (myDFPlayer.available()) {
      // char x='n';
   Serial.println(x); 
  switch (x){
    case 'n': myDFPlayer.next();
              x='a';
              break;
    case 'p':myDFPlayer.previous();
              x='a';
              break;
    case 'q':myDFPlayer.volumeUp();
             x='a';
             break;
    case 'w':myDFPlayer.volumeDown();
             x='a';
             break;
    case 'e':myDFPlayer.pause();
             x='a';
             break;
    case 'o':myDFPlayer.start();
             x='a';
             break;
  }
  


}
