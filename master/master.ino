#include <Wire.h>
int Txcommand = 0;
int slaveAddress = 5 ;
const int buttonPin = 2 ;
int buttonState = 0 ; // Var iab l e f o r r eading the push but ton s t a t u s
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin , INPUT) ;
  Wire.begin() ; // Join I2C bus as Master
}
void loop() {
  buttonState = digitalRead ( buttonPin ) ;
  if ( buttonState == HIGH) {
    Txcommand = 1 ;
  }
  else {
    Txcommand = 0 ;
  }
//  Wire.beginTransmission ( slaveAddress ) ; // Transmit to d e v i c e #5
//  Wire.write(1 ) ;
//  Wire.endTransmission() ; // Stop t r a n smi t t i n g
 Wire.requestFrom(5, 2);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  delay(200) ;
}
