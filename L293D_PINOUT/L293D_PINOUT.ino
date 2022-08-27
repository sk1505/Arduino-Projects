const int trigPin = 2;
const int echoPin = 3;
long distance, duration;

void setup() {
  // put your setup code here, to run once:
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

Serial.begin(9600);
}

void Left()
{
 
  
}

void Right()
{
   digitalWrite(6,HIGH);
digitalWrite(7,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);

}
void Forward()
{
digitalWrite(6,HIGH);
digitalWrite(7,LOW);
digitalWrite(10,HIGH);
digitalWrite(11,LOW);

}

void Reverse()
{
  digitalWrite(7,HIGH);
digitalWrite(6,LOW);
digitalWrite(11,HIGH);
digitalWrite(10,LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin,LOW);
delay(2);
digitalWrite(trigPin,HIGH);
delay(10);
digitalWrite(trigPin,LOW);

duration = pulseIn(echoPin,HIGH);
distance = (duration* 0.0340)/2;
Serial.print("Distance: ");
Serial.println(distance);
if(distance<=10){
  Reverse();
  delay(1000);
  Right();
  delay(2000);
  Forward();
  
}
else{
  Forward();
}

}
