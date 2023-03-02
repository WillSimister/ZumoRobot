#include <Wire.h>
#include <Zumo32U4.h>


Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
char action;
int speed = 200;

//Begin comms
void setup()
{
  Serial.begin(9600);
  ledGreen(1);
}

//Simple switch to get an action and perform the action with the Zumo.
void loop()
{
  if (Serial.available() > 0)
  {
    action = Serial.read();

    switch (action)
    {
      case 'w':
        ledYellow(1);
        ledRed(0);
        ledGreen(0);
        motors.setSpeeds (speed, speed);
        delay(100);
        break; 
      case 's':
        ledYellow(0);
        ledRed(0);
        ledGreen(1);
        motors.setSpeeds(speed*-1, speed*-1);
        delay(100);
        break;  
      case 'a':
        // turn left
        ledRed(1);
        ledGreen(0);
        ledYellow(0);
        motors.setLeftSpeed(0);
        motors.setRightSpeed(speed);
        delay(100);
        break;   
      case 'd':
        // turn right
        ledRed(1);
        ledGreen(0);
        ledYellow(0);
        motors.setLeftSpeed(speed);
        motors.setRightSpeed(0);
        delay(100);
        break;  
      case 'e':
        // turn right
        ledRed(1);
        ledGreen(0);
        ledYellow(0);
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        delay(100);
        break;       
      default:
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        ledYellow(0);
        ledRed(0);
        ledGreen(0);
        delay(100);
    }
  }
}