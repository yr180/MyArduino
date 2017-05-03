void setup() 
{
  Serial.begin(9600);
  
  pinMode(2,OUTPUT); //make Vcc
  pinMode(3,OUTPUT); //trig
  pinMode(4,INPUT);  //echo
  pinMode(5,OUTPUT); //make Gnd
 }

void loop() 
{
 digitalWrite(2,HIGH);
 digitalWrite(5,LOW); 
 while(1)
  {
   float duration,distance;
   digitalWrite(3,LOW);
   delayMicroseconds(10);
   digitalWrite(3,HIGH);
   delayMicroseconds(10);
   digitalWrite(3,LOW);
 
   duration=pulseIn(4,HIGH);
   distance=duration*0.018;
   Serial.print(duration);
   Serial.print("us\t");
   if(distance>=100)
   {
     Serial.print(distance/100);
     Serial.print("m\n");
   }
   else 
   {
     Serial.print(distance);
     Serial.print("cm\n");
   }
   delay(2000);
  } 
}
