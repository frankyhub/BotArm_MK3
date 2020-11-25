/* Board NANO
 *  ATmegam328Pm(Old Bootloader)
 *  Stepper mit Poti
 *  Serieller Monitor > Joy
 *  INT LED HIGH bei Mittelstellung
 *  
 *  Stillstand optimiert re/li 
 *  V10
 *  KHF 06.11. 2020
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
 
void setup()
{
   Serial.begin(9600);
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
}
