/* Board NANO
 *  ATmegam328Pm(Old Bootloader
 *  
 *  Stepper für MK3
 *  Serieller Monitor > Joy-Poti
 *  INT LED HIGH bei Mittelstellung
 *  
 *  
 *  KHF 07.11.2020 Servo eingefügt
 *  KHF 06.11. 2020 Stillstand optimiert re/li 
 *  
 *  Stepper 
 *      joystick A0
 *      IN4, IN2, IN3, IN1
 *  PIN 11   10   9    8
 *  
 *  Servo
 *  Poti1 = A4
 *  PWM PIN 6
 *  V10 
 * 17.11.2020
 *  KHF
 */
#include <Stepper.h>
 
#define STEPS 32
 
// Stepper Anschlüsse
#define IN1 8
#define IN2 10
#define IN3 9
#define IN4 11
 
// Library initialisieren
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
 //PINS NANO             11   10   9    8
 
// Joystick/Poti an NANO A0
#define joystick A0

int LED13 = 13;     // Interne LED


//----------Servo--------------------
#include <VarSpeedServo.h> 


VarSpeedServo Gr_servo; //Greifarm

int Poti1 = A4;     //Greifarm
int Greifarm;

//Speed festlegen:
int SPEED_Gr = 30; //30 bei Test

//-----------------------------------
 
void setup()
{
   Serial.begin(9600);
   Gr_servo.attach(6);   //PWM#6
   int Poti1 = analogRead(A4);
}
 
void loop()
{
   
// Analogwert einlesen
int val = analogRead(joystick);
 Serial.print(val);  
  Serial.println();  
 
// Wenn Joystick in Mittelstellung = Motor stopp
if( (val > 523) && (val < 500) )
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
digitalWrite(LED13, HIGH); 
}
 
else
{
// Motor rechts
//while (val >= 523)
while (val >= 723)

{
  digitalWrite(LED13, LOW); 
// map Speed zwischen 0 und 500 rpm
int speed_ = map(val, 723, 1023, 5, 500);

// Motor Speed
stepper.setSpeed(speed_);
 
// Motordrehung = 1 Stepp
stepper.step(1);
 
val = analogRead(joystick);
 Serial.print(val);  
  Serial.println();  
}
 
// Motor links
while (val <= 300)
{
    digitalWrite(LED13, LOW);
// Speed zwischen 0 und 500 rpm
int speed_ = map(val, 500, 0, 5, 300);
// Set Motor Speed
stepper.setSpeed(speed_);
 
// Motordrehung = 1 Stepp
stepper.step(-1);
val = analogRead(joystick);
Serial.print(val);  
 Serial.println();  
}
}
  //Greifarm
  Greifarm = map(Poti1, 0, 1023, 0, 175);
  Gr_servo.write(Greifarm, SPEED_Gr);
  delay(100);
}
