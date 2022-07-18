#define rightSensor  2
#define leftSensor  3
#define EnableA  4
#define dir1A  5
#define dir2A  6
#define dir1B  7
#define dir2B  8
#define EnableB  9
#define buzzer 10



void setup() {
pinMode(rightSensor,INPUT);
pinMode(leftSensor,INPUT);
pinMode(EnableA,OUTPUT);
pinMode(dir1A,OUTPUT);
pinMode(dir2A,OUTPUT);
pinMode(EnableB,OUTPUT);
pinMode(dir1B,OUTPUT);
pinMode(dir2B,OUTPUT);
pinMode(buzzer,OUTPUT);
Serial.begin(9600);
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



void loop() {
int rightSensorReading = digitalRead(rightSensor);
int leftSensorReading = digitalRead(leftSensor);

if(rightSensorReading == 1 && leftSensorReading == 1){
  forward(180);
  digitalWrite(buzzer,LOW);

}
if(rightSensorReading == 0 && leftSensorReading == 1){
  right(180);
  digitalWrite(buzzer,HIGH);
}
if(rightSensorReading == 1 && leftSensorReading == 0){
  left(180);
    digitalWrite(buzzer,HIGH);

}
  


}
