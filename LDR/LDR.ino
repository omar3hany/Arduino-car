#define ldr A2
#define light1 29
#define light2 30
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ldr, INPUT);
  pinMode(light1,OUTPUT);
  pinMode(light2,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int x=analogRead(ldr);
  Serial.println(x);
  if(x>50 && x<80){
    digitalWrite(light1,HIGH);
    digitalWrite(light2,LOW);
  }
  if(x>80){
    digitalWrite(light2,HIGH);
    digitalWrite(light1,HIGH);
  }
  if(x<50){
    digitalWrite(light2,LOW);
    digitalWrite(light1,LOW);
  }
  Serial.println(x);
  delay(10);

}
