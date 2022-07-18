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
  Serial.begin(9600); 
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

}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(13,HIGH);
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  char x ;
  
  if(mapX>-30 && mapX<20 && mapY>400){
      x='p';
      flag = true;
      //right
  }
  else if(mapY>-25 && mapY<20 && mapX>400){
      x='n';
      flag = true;
      //up
  }
  else if(mapY>-25 && mapY<20 && mapX<-400){
      x='r';
      flag = true;
      //down
  }
  else if(mapX>-30 && mapX<20 && mapY<-400){
      x='d';
      flag = true;
      //left
  }
  if (!flag){
    x = 'p';
  }
  switch(x){
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
//  //Serial.println(SW_state);
  //delay(1000);


}
