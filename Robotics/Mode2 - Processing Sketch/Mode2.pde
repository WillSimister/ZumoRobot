// Need G4P library
import g4p_controls.*;
import processing.serial.*;

Serial connection;

public void setup(){
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  String portName = Serial.list()[2];
  connection = new Serial(this, portName, 9600);
}

public void draw(){
  background(230);
  
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){

}
