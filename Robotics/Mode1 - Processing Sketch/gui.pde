/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void button_Right_Click(GButton source, GEvent event) { //_CODE_:button_Right:540285:
  println("button_Right - GButton >> GEvent." + event + " @ " + millis());
  connection.write('d');
} //_CODE_:button_Right:540285:

public void buttonBack_click1(GButton source, GEvent event) { //_CODE_:button_Back:864437:
  println("button_Back - GButton >> GEvent." + event + " @ " + millis());
  connection.write('s');
} //_CODE_:button_Back:864437:

public void buttonLeft_click1(GButton source, GEvent event) { //_CODE_:button_Left:554081:
  println("button_Left - GButton >> GEvent." + event + " @ " + millis());
  connection.write('a');
} //_CODE_:button_Left:554081:

public void buttonup_click1(GButton source, GEvent event) { //_CODE_:buttun_up:563288:
  println("buttun_up - GButton >> GEvent." + event + " @ " + millis());
  connection.write('w');
} //_CODE_:buttun_up:563288:

public void buttonStop_click1(GButton source, GEvent event) { //_CODE_:button_Stop:392378:
  println("button_Stop - GButton >> GEvent." + event + " @ " + millis());
  connection.write('e');
} //_CODE_:button_Stop:392378:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  surface.setTitle("Sketch Window");
  button_Right = new GButton(this, 203, 130, 88, 74);
  button_Right.setText("Right");
  button_Right.addEventHandler(this, "button_Right_Click");
  button_Back = new GButton(this, 110, 130, 88, 74);
  button_Back.setText("Back");
  button_Back.addEventHandler(this, "buttonBack_click1");
  button_Left = new GButton(this, 17, 129, 88, 74);
  button_Left.setText("Left");
  button_Left.addEventHandler(this, "buttonLeft_click1");
  buttun_up = new GButton(this, 109, 51, 88, 74);
  buttun_up.setText("Forward");
  buttun_up.addEventHandler(this, "buttonup_click1");
  button_Stop = new GButton(this, 201, 51, 88, 74);
  button_Stop.setText("STOP");
  button_Stop.setLocalColorScheme(GCScheme.ORANGE_SCHEME);
  button_Stop.addEventHandler(this, "buttonStop_click1");
  label1 = new GLabel(this, 116, 29, 80, 20);
  label1.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label1.setText("MODE 1");
  label1.setOpaque(false);
}

// Variable declarations 
// autogenerated do not edit
GButton button_Right; 
GButton button_Back; 
GButton button_Left; 
GButton buttun_up; 
GButton button_Stop; 
GLabel label1; 
