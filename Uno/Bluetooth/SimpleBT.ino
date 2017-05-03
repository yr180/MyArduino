// D11   <<<  Rx_HC05
// D10   >>>  Tx_HC05
#include <SoftwareSerial.h>// import the serial library

SoftwareSerial btsoftserial(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
char BluetoothData;

void setup()
{
  btsoftserial.begin(9600);
  pinMode(ledpin,OUTPUT);
}

void loop() 
{
    if (btsoftserial.available())
    {
      BluetoothData=btsoftserial.read();
      if(BluetoothData=='1')
      {
       digitalWrite(ledpin,HIGH);
      }
      else
       digitalWrite(ledpin,LOW);
    }
   delay(100);// prepare for next data ...
}
