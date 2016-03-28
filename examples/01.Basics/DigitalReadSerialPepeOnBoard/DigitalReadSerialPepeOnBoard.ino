/*
  DigitalReadSerial with on-board Pushbutton
  Reads a digital input on pin 4(SWITCH3) or 6(SWITCH4), prints the result to the serial monitor 
 
  Harware Required:
  * PepeOnBoard
  
  This example code is in the public domain.
 */

//  PepeOnBoard Switch 3( pin4 ) and Switch 4 (pin 6) has a pushbutton attached to it.
int pushButton = SWITCH3; 

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); 
  // make the on-board pushbutton's pin an input pullup:
  pinMode(pushButton, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.println(buttonState);
  delay(1);        // delay in between reads for stability
}



