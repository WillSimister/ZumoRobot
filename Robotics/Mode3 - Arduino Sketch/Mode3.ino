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
Zumo32U4LineSensors lineSensors;

int leftRead = 500;
int middleRead = 500;
int rightRead = 500;

unsigned int sensors[5];
int turnSpeed=150;

int proxThreshhold = 6;
int blackThreshold = 550;
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
}

void turnLeft()
{
  motors.setSpeeds(-150, 150);
}

void goForward()
{
  motors.setSpeeds(turnSpeed, turnSpeed);
}

void goBackward()
{
  motors.setSpeeds(-turnSpeed, -turnSpeed);
}

void stop()
{
  motors.setSpeeds(0, 0);
}

//When a Cup (Person) is found gently remove them from the maze and carry on.
void pushCupFromMaze(){
  lineSensors.read(sensors);
  //If left sensor is over the line
  if(sensors[0] > blackThreshold)
  {
    //Reverse
    motors.setSpeeds(-50, -50);
    delay(200);
    //Slight Backwards left turn
    motors.setSpeeds(-350, 200);
    delay(250);
  }
  //If Left sensore and Middle sensor are over the line
  else if(sensors[0] > blackThreshold && sensors[2] > blackThreshold-300){
    motors.setSpeeds(-50, -50);
    delay(200);
    motors.setSpeeds(-350, 100);
    delay(200);
  }
  //If right sensor is over the line
  else if(sensors[4] > blackThreshold && sensors[2] > blackThreshold-300)
  {
    motors.setSpeeds(-50, -50);
    delay(200);
    motors.setSpeeds(-200, 100);
    delay(300);
  }
  //Else continue to push cup
  else{
    motors.setSpeeds(100, 100);
    pushCupFromMaze();
  }
  //Start a delay before another person can be found
  personFoundTimer.start();
  //Relay to the gui that we have found a person.
  Serial.write(1);
}

void loop() 
{
  //Start the prox checking timer
  stopwatch.start();
  //Use method of navigation
  hugRightWall();
  //Call the prox sensors check
  proxSensorsLoop();
  //Reset the person found timer as the robot will have moved away from the last person found.
  if(personFoundTimer.elapsed() > 5000)
  {
    personFoundTimer.reset();
  }
}

void proxSensorsLoop(){
  //Take readings
  proxSensors.read();
  float leftValue = proxSensors.countsFrontWithLeftLeds();
  float rightValue = proxSensors.countsFrontWithRightLeds();
  lineSensors.read(sensors);

  //If the person found timer has been reset or hasnt started - look for people
  if(!personFoundTimer.isRunning())
  {
    if(stopwatch.elapsed() > 2000)
    {
      if (leftValue == proxThreshhold && rightValue == proxThreshhold){
        stopwatch.reset();
        stopwatch.start();
        motors.setSpeeds(0,0);
        pushCupFromMaze();
      }
      //This if-else statement turns the robot to face the cup (person)
      if (leftValue == proxThreshhold && rightValue != proxThreshhold){
        motors.setSpeeds(0, 0);
        motors.setSpeeds(-turnSpeed, turnSpeed);
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

  //Get values
  int leftVal = sensors[0];
  int rightVal = sensors[4];
  int middleVal = sensors[2];

  delay(50);

  if(leftVal > blackThreshold)
  {
    motors.setSpeeds(-50, -50);
    delay(100);
    turnRight();
  }

  //Hug the right wall
  //Because I have a faulty middle sensor I have to be careful with values I use - so middle sensor I have created its own threshold, seperate from left and right.
  if(middleVal < middleRead -300)
  {
    motors.setSpeeds(120,0);
  }

  if(rightVal > rightRead)
  {
    motors.setSpeeds(0,120);
  }

  if(rightVal > rightRead && middleVal > middleRead-300)
  {
    motors.setSpeeds(-50, -50);
    delay(100);
    turnRight();
  }
}