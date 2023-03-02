//ASSIGNMENT MODE 3 FULLY AUTONOMOUS MAZE NAVIGATION
#include <Wire.h>
#include <Zumo32U4.h>
#include <Keyboard.h>
#include <Zumo32U4Buzzer.h>
#include <StopWatch.h>

StopWatch stopwatch(StopWatch::MILLIS);
StopWatch personFoundTimer(StopWatch::MILLIS);
Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4LineSensors lineSensors;
Zumo32U4Buzzer buzzer;

int peopleFound = 0;
int leftRead = 500;
int middleRead = 500;
int rightRead = 500;

unsigned int sensors[5];
bool turningRight = false;
bool turningLeft = false;
uint16_t turnSpeed=150;

int proxThreshhold = 6;
uint16_t blackThreshold = 550;
int loopCounter = 0;

void setup() 
{
  proxSensors.initThreeSensors();
  lineSensors.initFiveSensors();
  Serial.println("Code Initiated");
}

void turnRight()
{
  motors.setSpeeds(-220,220);
  delay(250);
  turningLeft = false;
  turningRight = true;
}

void turnLeft()
{
  motors.setSpeeds(-150, 150);
  turningLeft = true;
  turningRight = false;
}

void goForward()
{
  motors.setSpeeds(turnSpeed, turnSpeed);
  turningLeft = false;
  turningRight = false;
}

void goBackward()
{
  motors.setSpeeds(-turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = false;
}

void stop()
{
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}


void pushCupFromMaze(){
  lineSensors.read(sensors);
  if(sensors[0] > blackThreshold)
  {
    // motors.setSpeeds(-100, 0);
    // delay(200);
    motors.setSpeeds(-50, -50);
    delay(200);
    motors.setSpeeds(-350, 200);
    delay(250);
  }
  else if(sensors[0] > blackThreshold && sensors[2] > blackThreshold-300){
    motors.setSpeeds(-50, -50);
    delay(200);
    motors.setSpeeds(-350, 100);
    delay(200);
  }
  else if(sensors[4] > blackThreshold && sensors[2] > blackThreshold-300)
  {
    motors.setSpeeds(-50, -50);
    delay(200);
    motors.setSpeeds(-200, 100);
    delay(300);
  }
  else{
    motors.setSpeeds(100, 100);
    pushCupFromMaze();
  }
  personFoundTimer.start();
  peopleFound++;
  Serial.write("Person Found!");
}

void loop() 
{
  stopwatch.start();
  hugRightWall();
  proxSensorsLoop();
  if(personFoundTimer.elapsed() > 5000)
  {
    personFoundTimer.reset();
  }
}

void proxSensorsLoop(){
  proxSensors.read();
  float leftValue = proxSensors.countsFrontWithLeftLeds();
  float rightValue = proxSensors.countsFrontWithRightLeds();
  //buzzer.playNote('C4', 20, 15);
  lineSensors.read(sensors);
  //buzzer.playNote(A1, 20, 15);
  if(!personFoundTimer.isRunning())
  {

    if(stopwatch.elapsed() > 2000)
    {
      if (leftValue == proxThreshhold && rightValue == proxThreshhold){
        stopwatch.reset();
        stopwatch.start();
        buzzer.stopPlaying();
        buzzer.playNote('C4', 20, 15);
        motors.setSpeeds(0,0);
        //display.print(F("Person found"));
        pushCupFromMaze();
        //display.clear();

        // This is where the program should start a new routine to get the robot not detecting the person found 
      }
      if (leftValue == proxThreshhold && rightValue != proxThreshhold){
        motors.setSpeeds(0, 0);
        motors.setSpeeds(-turnSpeed, turnSpeed);
        buzzer.playNote(A3, 15, 8);
        proxSensorsLoop();
      }
      else if (rightValue == proxThreshhold && leftValue != proxThreshhold){
        motors.setSpeeds(0,0);
        motors.setSpeeds(turnSpeed, -turnSpeed);
        proxSensorsLoop();
      }
    }
  }
}


void hugRightWall()
{
  lineSensors.read(sensors);

  for (int i = 0; i < 5; i++) 
  {
    Serial.print("Line sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(sensors[i]);
    Serial.print("\t");
  }

  //Stores value of line sensors as a variable everytime the program loops.
  uint16_t leftLineValue = sensors[0];
  uint16_t rightLineValue = sensors[4];
  uint16_t centerLineValue = sensors[2];

  delay(50);


  if(leftLineValue > blackThreshold)
  {
    motors.setSpeeds(-50, -50);
    delay(100);
    turnRight();
  }

  //CAUSES THE ROBOT TO HUG THE LEFT WALL.
  if(centerLineValue < middleRead -300)
  {
    motors.setSpeeds(120,0);
  }

  if(rightLineValue > rightRead)
  {
    motors.setSpeeds(0,120);
  }

  if(rightLineValue > rightRead && centerLineValue > middleRead-300)
  {
    takeManualControl();
    motors.setSpeeds(0, 0);
  }
}

void takeManualControl()
{
  char action = 'a';
  if (Serial.available() > 0)
  {
    action = Serial.read();

    switch (action)
    {
      case 'l': 
      {
        turnLeft();
        hugRightWall();
        break;
      }
      case 'r':
      {
        turnRight();
        hugRightWall();
      }
    }
  }
  else {takeManualControl();}

}