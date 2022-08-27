const int trigPin = 2;
const int echoPin = 3;
long distance, duration;

void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600);
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


}
