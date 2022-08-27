void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(A0,INPUT);

digitalWrite(6,HIGH);
digitalWrite(7,LOW);
digitalWrite(10,HIGH);
digitalWrite(11,LOW);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

int store= analogRead(A0);
int x=map(store,0,1024,0,255);
Serial.println(store);
Serial.println(x);
analogWrite(6,x);
analogWrite(10,x);

}
