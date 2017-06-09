#include <DigiKeyboard.h>


/*
   BYJ48 Stepper motor code
   Connect :
   IN1 >> D8
   IN2 >> D9
   IN3 >> D10
   IN4 >> D11
   VCC ... 5V Prefer to use external 5V Source
   Gnd
   written By :Mohannad Rawashdeh
  https://www.instructables.com/member/Mohannad+Rawashdeh/
     28/9/2013
  */

#define USE_DIGIKEYBOARD

// Specify the DigiSpark pins to use
#define IN1  0
#define IN2  1
#define IN3  2
#ifdef USE_DIGIKEYBOARD
#define IN4  5
#else
#define IN4  3
#endif

int Steps = 0;
boolean Direction = true; // gre
unsigned long last_time;
unsigned long currentMillis ;
int steps_per_shot=128;
int steps_left=steps_per_shot;
long time;
void setup()
{
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
#ifdef USE_DIGIKEYBOARD
  DigiKeyboard.delay(1000);
#else
  delay(1000);
#endif

}
void loop()
{
  while(steps_left>0)
  {
    currentMillis = micros();
    if(currentMillis-last_time>=1000)
    {
      stepper(1); 
      time=time+micros()-last_time;
      last_time=micros();
      steps_left--;
    }
  }
#ifdef USE_DIGIKEYBOARD
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println("Hello Digispark!");
  DigiKeyboard.delay(1000);
#else
  delay(1000);
#endif
  steps_left=steps_per_shot;
}

void stepper(int xw)
{
  for (int x=0;x<xw;x++)
  {
    switch(Steps)
    {
       case 0:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       case 1:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, HIGH);
       break; 
       case 2:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 3:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 4:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 5:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
         case 6:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 7:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       default:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
    }
    SetDirection();
  }
} 
void SetDirection()
{
  if(Direction==1){ Steps++;}
  if(Direction==0){ Steps--; }
  if(Steps>7){Steps=0;}
  if(Steps<0){Steps=7; }
}
