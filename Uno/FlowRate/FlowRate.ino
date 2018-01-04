/*********************************************************************

Code for measuring flow rate of a liquid. The flow rate sensor used
has a resolution of 4.5 pulses per litre

Author: Yash Rao
Date: 6/8/17

*********************************************************************/

int FRS = 2;                 //Input pin for FRS signal
int pulseCount = 0;          //Pulse count from FRS
float flowRate = 0.0;        //flow rate computed as litres per minute
float totalLitres = 0;       //total liquid quantity through FRS 
int oldTime = 0;             //time variable 

void setup() {
  pinMode(FRS,INPUT);
  Serial.begin(9600);
  Serial.println("Initializing, place module at zero mark");
  attachInterrupt(0,pulseCounter,FALLING);
}

void pulseCounter()
{
  pulseCount++;
}

void loop() {
  if(millis() - oldTime > 1000)
  {
    //disable interrupts for calculating values
    detachInterrupt(0);
    //flowRate for 1 second
    flowRate = (1000/(millis() - oldTime))*pulseCount/7.5;  
    oldTime = millis();
    //quantity in litres through FRS in 1 second
    totalLitres += flowRate / 60;                             
    
    //display data on UART terminal
    Serial.print("Flow rate = ");
    Serial.print(flowRate);
    Serial.print(" litres per minute");
    
    Serial.print("\tTotal litres = ");
    Serial.print(totalLitres);
    Serial.println(" litres");
    
    //enable interrupt
    attachInterrupt(0,pulseCounter,RISING);
    //Reset pulse counter for next calculation
    pulseCount = 0;
  }
}

