#define xSen 340
#define ySen 340
#define zSen 300
#define xMean 1650
#define yMean 1650
#define zMean 1690
#define ADC_REF 4540

void setup() 
{
   pinMode(14,OUTPUT);
   pinMode(18,OUTPUT);
   Serial.begin(9600);
   digitalWrite(14,HIGH);//Vcc
   digitalWrite(18,LOW);//GND 
}

void loop() 
{
  //Raw readings
  float xRead = analogRead(A1);
  float yRead = analogRead(A2);
  float zRead = analogRead(A3);
  
  //Converting to mV
  float Vx = ADC_REF*xRead/1023;
  float Vy = ADC_REF*yRead/1023;
  float Vz = ADC_REF*zRead/1023;
  
  Serial.print("\nValues in mV of x y z\n"); 
  Serial.print(Vx);
  Serial.print("\t");  
  Serial.print(Vy);
  Serial.print("\t");
  Serial.print(Vz);
  
  //Converting to g's and print
  Serial.print("\nValues of g force along x y z\n");
  Serial.print((Vx-xMean)/xSen);
  Serial.print("\t");  
  Serial.print((Vy-yMean)/ySen);
  Serial.print("\t");
  Serial.print((Vz-zMean)/zSen);
  Serial.print("\n");
  
  delay(1000);
}
