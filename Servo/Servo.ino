/*
 * Servo mit Poti ansteuern
 * Board: Uno
 */

#include <Servo.h>


Servo Motor;

int ReglerWert;

int Position;
void setup()
{
// Motor an Pin 9 angeschlossen (attach)
Motor.attach(6);
}
void loop()
{
int ReglerWert = analogRead(A4);

Position = map(ReglerWert, 0, 1023, 0, 180);
Motor.write(Position);
}
