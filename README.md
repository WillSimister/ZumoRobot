# ZumoRobot

ReadMe contains explanations on how to set up environments to run different modes of the assignment on the Zumo Robot. 

The main folder contents
 - Mode1 - Arduino Sketch
 - Mode1 - Processing Sketch
 - Mode2 - Arduino Sketch
 - Mode2 - Proccessing Sketch
 - Mode3 - Arduino Sketch
 - Mode3 - Processing Sketch
 
 If a folder is finished with 'Arduino Sketch' this means that the contents of the folder should be opened in the Arduino IDE and uploaded to the Zumo 32U4 Robot.
 (If you haven't already done so make sure that in you Arduino IDE - the Zumo Libraries have been installed.)
 
 If a folder is finished with 'Processing Sketch' this means that the contents of the folder should be opened in the Processing IDE and ran. 
 (If you havent already done so - inside Processing navigate to Tools | Manage Libraries and search 'g4p' on the libraries tab and install 'G4P' by Peter Lager,
 on the Tools tab install 'G4P Gui Buidler' also by peter lager.
 
 In the Processing sketch you will need to change the following line of code so it is accessing the correct Serial Port. 
 String portName = Serial.list()[2];
 By changing the number until the GUI builds, runs and connects without error. 
 
 For Mode 3 - 
 Start the robot so it is facing forwards - touching the right hand line.
 
 For all modes - 
 If you would like to communicate with the Zumo robot over wifi - in the Arduino sketch - communicate over Serial1. 
 If you would like to communicate with the Zumo robot over USB connection - in the Arduino Sketch - communicate over Serial.
 
 
