#define xSen 0.34
#define ySen 0.34
#define zSen 0.3
#define xMean 1.65
#define yMean 1.65
#define zMean 1.69
#define ADC_REF 4.54

float xRead, yRead, zRead, xAcc, yAcc, zAcc, xAng, yAng, zAng;

void setup() {
  pinMode(14,OUTPUT);
  pinMode(18,OUTPUT);
  Serial.begin(9600); 
  digitalWrite(14,HIGH);
  digitalWrite(18,LOW);
}

void loop() {
  //Raw readings
  xRead = analogRead(A1);
  yRead = analogRead(A2);
  zRead = analogRead(A3);
  
  xAcc = ((ADC_REF*xRead/1024.0) - xMean)/xSen;
  yAcc = ((ADC_REF*yRead/1024.0) - yMean)/ySen;
  zAcc = ((ADC_REF*zRead/1024.0) - zMean)/zSen; 
 
  xAng = RAD_TO_DEG * (atan2(-yAcc, -zAcc) + PI);
  yAng = RAD_TO_DEG * (atan2(-xAcc, -zAcc) + PI);
  zAng = RAD_TO_DEG * (atan2(-yAcc, -xAcc) + PI);
  
  Serial.println("Angle for rotation axis:");
  Serial.print("x: ");
  Serial.println(xAng);
//  Serial.print(" | y: ");
//  Serial.print(yAng);
//  Serial.print(" | z: ");
//  Serial.println(zAng);
  
  delay(100;)
}
