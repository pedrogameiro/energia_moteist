/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * PepeOnBoard
  
  This example code is in the public domain.
*/

//PepeOnBoard has four LEDs LED1, LED2, LED3 and LED4
//chosing a defined LED maps the board pin automatically

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED1, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
