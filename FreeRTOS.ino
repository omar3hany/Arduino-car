#include <Arduino_FreeRTOS.h>

//Line following
#define rightSensor  2
#define leftSensor  3
#define EnableA  4
#define dir1A  5
#define dir2A  6
#define dir1B  7
#define dir2B  8
#define EnableB  9
#define buzzer 12


//LDR
#define ldr A2
#define light1 10
#define light2 11


//MP3
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int slaveAddress = 5 ;
char x='a';


//GearBox
#define pin1 22
#define pin2 23
#define pin3 24
#define pin4 25
#define pin5 26
#define pin6 27
#define pin7 28
int VRx = A0;
int VRy = A1;
int xPosition = 0;
int yPosition = 0;
int mapX = 0;
int mapY = 0;
bool flag;




void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(115200);
  //Line Following setup
  pinMode(rightSensor,INPUT);
  pinMode(leftSensor,INPUT);
  pinMode(EnableA,OUTPUT);
  pinMode(dir1A,OUTPUT);
  pinMode(dir2A,OUTPUT);
  pinMode(EnableB,OUTPUT);
  pinMode(dir1B,OUTPUT);
  pinMode(dir2B,OUTPUT);
  pinMode(buzzer,OUTPUT);
  

  //LDR setup
  pinMode(ldr, INPUT);
  pinMode(light1,OUTPUT);
  pinMode(light2,OUTPUT);


  //MP3 setup
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
  Wire.begin() ;
  
  
  //GearBox setup
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(pin5,OUTPUT);
  pinMode(pin6,OUTPUT);
  pinMode(pin7,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  flag = false;


  
  xTaskCreate( vTask1, "Line following", 1000, NULL, 1, NULL ); 
  xTaskCreate( vTask2, "LDR", 1000, NULL, 1, NULL ); 
  xTaskCreate( vTask3, "MP3", 1000, NULL, 1, NULL ); 
  xTaskCreate( vTask4, "GearBox", 1000, NULL, 1, NULL ); 

  vTaskStartScheduler();

}
void forward(int i){
      analogWrite(EnableA,i);
      digitalWrite(dir1A,LOW);
      digitalWrite(dir2A,HIGH);
      analogWrite(EnableB,i);
      digitalWrite(dir1B,HIGH);
      digitalWrite(dir2B,LOW);
    
      
    }
    
    void backward(int i){
      analogWrite(EnableA,i);
      digitalWrite(dir1A,HIGH);
      digitalWrite(dir2A,LOW);
      analogWrite(EnableB,i);
      digitalWrite(dir1B,LOW);
      digitalWrite(dir2B,HIGH);
    }
    
    void right(int i){
      analogWrite(EnableA,i);
      digitalWrite(dir1A,LOW);
      digitalWrite(dir2A,HIGH);
      analogWrite(EnableB,i);
      digitalWrite(dir1B,LOW);
      digitalWrite(dir2B,HIGH);
    }
    
    void left(int i){
      analogWrite(EnableA,i);
      digitalWrite(dir1A,HIGH);
      digitalWrite(dir2A,LOW);
      analogWrite(EnableB,i);
      digitalWrite(dir1B,HIGH);
      digitalWrite(dir2B,LOW);
    }
    void Break(){
      analogWrite(EnableA,255);
      digitalWrite(dir1A,HIGH);
      digitalWrite(dir2A,HIGH);
      analogWrite(EnableB,255);
      digitalWrite(dir1B,HIGH);
      digitalWrite(dir2B,HIGH);
    }
  static void vTask1(void* pvParameters) {
    Serial.println("Task1: Started");
    
    
    while(1){
        int rightSensorReading = digitalRead(rightSensor);
        int leftSensorReading = digitalRead(leftSensor);
        
        if(rightSensorReading == 1 && leftSensorReading == 1){
          forward(100);
          digitalWrite(buzzer,LOW);
        
        }
        if(rightSensorReading == 0 && leftSensorReading == 1){
          right(100);
          digitalWrite(buzzer,HIGH);
        }
        if(rightSensorReading == 1 && leftSensorReading == 0){
          left(100);
            digitalWrite(buzzer,HIGH);}
      
      if(rightSensorReading == 0 && leftSensorReading == 0){
          Break();
           digitalWrite(buzzer,LOW);

      }
    }
  }

   static void vTask2(void* pvParameters){
      Serial.println("Task2: Started");
    
      while(1){
        int y=analogRead(ldr);
        Serial.println(x);
        if(y>100 ){
          digitalWrite(light1,200);
          digitalWrite(light2,200);
        }
        if(y>60 && y<100){
          analogWrite(light2,70);
          analogWrite(light1,70);
        }
        if(y<60){
          digitalWrite(light2,LOW);
          digitalWrite(light1,LOW);
        }
        Serial.println(y);
        delay(10);
      }
    
    }

    static void vTask3(void* pvParameters){
      Serial.println("Task3: Started");
      bool stopped=false;
      int song=1;
      //myDFPlayer.enableLoop();
      while(1){
         static unsigned long timer = millis();
          Wire.beginTransmission(5);
          //byte error=Wire.endTransmission();
          Wire.requestFrom(5, 1);
           while (Wire.available()) { // slave may send less than requested
             x = Wire.read(); // receive a byte as character
               // print the character
          } 
           Serial.println(x); 
          switch (x){
            case 'n':if(!stopped){
                      song++;
                     if(song==4){
                      stopped = true;
                        myDFPlayer.pause();
                     song=3;
                     }
                     else {
                        myDFPlayer.next();
                           Wire.beginTransmission ( slaveAddress ) ; // Transmit to d e v i c e #5
                      Wire.write(song) ;
                      Wire.endTransmission();
                        delay(1000);
                     }
                  
                      x='a';}
                      break;
            case 'p':if(!stopped){
                      song--;
                     if(song==0){
                      stopped = true;
                      myDFPlayer.pause();
                     song=1;
                     }
                     else {
                        myDFPlayer.previous();
                        Wire.beginTransmission ( slaveAddress ) ; // Transmit to d e v i c e #5
                      Wire.write(song) ;
                      Wire.endTransmission();
                        delay(1000);
                     }
                    
                      x='a';}
                      break;
            case 'q':myDFPlayer.volumeUp();
                     x='a';
                     break;
            case 'w':myDFPlayer.volumeDown();
                     x='a';
                     break;
            case 'e':myDFPlayer.pause();
                     stopped=true;
                     x='a';
                     break;
            case 'o':myDFPlayer.start();
                     stopped=false;
                     x='a';
                     break;
          }
        
      }
      }

      static void vTask4(void* pvParameters){
        Serial.println("Task4: Started");
        while(1){
        xPosition = analogRead(VRx);
            yPosition = analogRead(VRy);
            mapX = map(xPosition, 0, 1023, -512, 512);
            mapY = map(yPosition, 0, 1023, -512, 512);
            char z ;
            
            if(mapX>-40 && mapX<40 && mapY>400){
                z='p';
                flag = true;
                //right
            }
            else if(mapY>-40 && mapY<40 && mapX>400){
                z='n';
                flag = true;
                //up
            }
            else if(mapY>-40 && mapY<40 && mapX<-400){
                z='r';
                flag = true;
                //down
            }
            else if(mapX>-40 && mapX<40 && mapY<-400){
                z='d';
                flag = true;
                //left
            }
            if (!flag){
              z = 'p';
            }
            switch(z){
              case 'p': digitalWrite(pin1,HIGH);
                        digitalWrite(pin2,LOW);
                        digitalWrite(pin3,LOW);
                        digitalWrite(pin4,HIGH);
                        digitalWrite(pin5,LOW);
                        digitalWrite(pin6,LOW);
                        digitalWrite(pin7,LOW);
                        break;
                        
              case 'n':digitalWrite(pin1,HIGH);
                        digitalWrite(pin2,LOW);
                        digitalWrite(pin3,HIGH);
                        digitalWrite(pin4,LOW);
                        digitalWrite(pin5,LOW);
                        digitalWrite(pin6,LOW);
                        digitalWrite(pin7,LOW);
                        break;
                        
              case 'r':digitalWrite(pin1,HIGH);
                        digitalWrite(pin2,LOW);
                        digitalWrite(pin3,LOW);
                        digitalWrite(pin4,LOW);
                        digitalWrite(pin5,LOW);
                        digitalWrite(pin6,LOW);
                        digitalWrite(pin7,LOW);
                        break;
              case 'd':digitalWrite(pin1,LOW);
                        digitalWrite(pin2,LOW);
                        digitalWrite(pin3,LOW);
                        digitalWrite(pin4,LOW);
                        digitalWrite(pin5,LOW);
                        digitalWrite(pin6,HIGH);
                        digitalWrite(pin7,HIGH);
                        break;
          
            }
            Serial.print("X: ");
            Serial.print(mapX);
            Serial.print(" | Y: ");
            Serial.print(mapY);
            Serial.println(" | Button: ");
                  
        }
      }
    


void loop() {
  // put your main code here, to run repeatedly:


  
  

}
