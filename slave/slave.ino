#include <Wire.h>
int LED = 13 ;
int Rxcommand = 0 ;
void setup ( ) {
  // Def ine the LED pin as output
  pinMode (LED, OUTPUT) ;
  Serial.begin (9600) ;
  Wire.begin (5) ; // Join as Slav e on addr e s s 5
  // Attach a f unc t i on to t r i g g e r when something i s r e c e i v e d .
  Wire.onReceive ( receiveEvent ) ;
  Wire.onRequest(requestEvent);
}
void receiveEvent ( int bytes ) {
  Rxcommand = Wire.read() ; // Read one c h a r a c t e r from the I2C
  if (Rxcommand == 0)
    digitalWrite (LED, LOW) ;
  else
    digitalWrite (LED, HIGH) ;
}
void requestEvent() {
  Wire.write("hi"); // respond with message of 6 bytes
}

void loop ( ) {
  delay(500);
}
