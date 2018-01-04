/*********************************************************************

Code for controlling and maintaining the speed of a motor using PID 
control.

Author: Yash Rao
Date: 7/8/17

*********************************************************************/

#define pin_a 2   //for encoder pulse A
#define pin_b 3   //for encoder pulse B
#define pin_fwd 4 //for H-bridge: run motor forward
#define pin_bwd 5 //for H-bridge: run motor backward
#define pin_pwm 6 //for H-bridge: motor speed

int timer1_counter;  //for timer
int encoder = 0, totalPulse=0;
int m_direction = 0;
int set_speed = 100, pwm_pulse = 100;
float pv_speed = 0, e_speed = 0, e_speed_pre = 0, e_speed_sum = 0;
bool motor_start = 1;
float kp = 0.4, ki = 0.8, kd = 1;
String mySt = "n";

void setup() {
  pinMode(pin_a,INPUT_PULLUP);
  pinMode(pin_b,INPUT_PULLUP);
  pinMode(pin_fwd,OUTPUT);
  pinMode(pin_bwd,OUTPUT);
  pinMode(pin_pwm,OUTPUT);
  pinMode(7,OUTPUT);
  attachInterrupt(0, detect_a, RISING);
  digitalWrite(7,HIGH);
  // start serial port at 9600 bps:
  Serial.begin(9600);
  
  //timer setup
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 3036;    // preload timer 65536-16MHz/256/2Hz

  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
/********************************************************************/

/***********************Interrupt routine****************************/
void detect_a() {
   encoder+=1;                           //increasing encoder at new pulse
   totalPulse+=1;
   m_direction = 0; //digitalRead(pin_b);    //read direction of motor
   //Serial.println(encoder);
 }
 
 ISR(TIMER1_OVF_vect)                    // interrupt service routine - tick every 1sec
 {
   TCNT1 = timer1_counter;               // set timer
   pv_speed = 2*encoder;                 //calculate motor speed, unit is rpm
   encoder=0;
   //print out speed
   if (Serial.available() <= 0) 
   {
     Serial.print("speed");
     Serial.println(pv_speed);           //Print speed (rpm) value to Visual Studio
   }
   //PID program
   if (motor_start){
     e_speed = set_speed - pv_speed;
     pwm_pulse = e_speed*kp + e_speed_sum*ki + (e_speed - e_speed_pre)*kd;
     e_speed_pre = e_speed;             //save last (previous) error
     e_speed_sum += e_speed;            //sum of error
     if (e_speed_sum >4000) e_speed_sum = 4000;
     if (e_speed_sum <-4000) e_speed_sum = -4000;
   }
   else{
     e_speed = 0;
     e_speed_pre = 0;
     e_speed_sum = 0;
     pwm_pulse = 0;
   }
   
  //update new speed
   if (pwm_pulse < 255 & pwm_pulse > 0)
   {
     analogWrite(pin_pwm,pwm_pulse);  //set motor speed 
   }
   else
   {
     if (pwm_pulse>255)
     {
       analogWrite(pin_pwm,255);
     }
     else
     {
       analogWrite(pin_pwm,0);
     }
   }
}
/********************************************************************/

void loop() {
  while(motor_start){
    digitalWrite(pin_fwd,HIGH);
    digitalWrite(pin_bwd,LOW);
  }
       
 }

