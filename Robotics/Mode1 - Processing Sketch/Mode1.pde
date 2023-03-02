// Need G4P library
import g4p_controls.*;
// You can remove the PeasyCam import if you are not using
// the GViewPeasyCam control or the PeasyCam library.

import processing.serial.*;

Serial connection;

public void setup(){
  //Connection Setup
  String portName = Serial.list()[2];
  connection = new Serial(this, portName, 9600);
  //GUI setup
  size(1000, 600, JAVA2D);
  createGUI();
  customGUI(); 
}

public void draw(){
  background(230);
  
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){

}
