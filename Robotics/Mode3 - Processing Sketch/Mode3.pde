// Need G4P library
import g4p_controls.*;
import processing.serial.*;

Serial connection;

//How many people have been found
int personCount = 0;

public void setup(){
  //GUI setup
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  //Connection setup
  String portName = Serial.list()[2];
  connection = new Serial(this, portName, 9600);
}

public void draw(){
  background(230);
  //Listen for commands from the Zumo
  while (connection.available() > 0)
  {
    int msg = connection.read();
    print(connection.read());
    if (msg == 1)
    {
      personCount++;
      textarea1.appendText("\n"+ "People Found: " + personCount);
    } 
  }
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){

}
