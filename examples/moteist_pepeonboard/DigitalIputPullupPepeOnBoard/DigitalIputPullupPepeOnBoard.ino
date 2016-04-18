/*
 Input Pullup Serial
 
 This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a 
 digital input on pin 5 and prints the results to the serial monitor.
 
 The circuit: 
 * Momentary switch attached from pin 5 to ground 
 * Built-in LED on pin 14
 
 Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal 
 resistor is pulled to 3.3V. This configuration causes the input to 
 read HIGH when the switch is open, and LOW when it is closed. 
 
 created 14 March 2012
 by Scott Fitzgerald
 modified 27 Apr 2012
 Robert Wessels
 
 http://www.arduino.cc/en/Tutorial/InputPullupSerial
 
 This example code is in the public domain
 
 */

void setup(){
  //start serial connection
  Serial.begin(9600);
  //configure pin 5 as an input and enable the internal pull-up resistor
  pinMode(SWITCH3, INPUT_PULLUP); //Existem dois push buttons SWITCH3 e SWITCH4
  pinMode(LED1, OUTPUT); //Estao disponiveis os leds LED1, LED2, LED3, LED4

}

void loop(){
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(SWITCH3);
  //print out the value of the pushbutton
  Serial.println(sensorVal);
  
  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pin 13 when the 
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    digitalWrite(LED1, LOW);
  } 
  else {
    digitalWrite(LED1, HIGH);
  }
}



