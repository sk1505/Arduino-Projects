void setup() {
  // put your setup code here, to run once:
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=0;i<16;i++)
{
  int k=i;
  for(int j=0;j<4;j++)
{
  if(k%2==1)
  {
    digitalWrite(8+j,HIGH);
     }

  else{
    digitalWrite(8+j,LOW);
    
   }
   k/=2;
}
delay(1000);
}



}
