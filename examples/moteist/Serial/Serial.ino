/*

    Serial
    A simple Serial port write example

    The example runs an infinite loop, printing
    a message to both the debug and auxilary serial
    ports. LED1 toogles on every loop.

*/

// the setup routine runs once when you press reset:
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial1.begin(9600);
  
  // set LED1 as an output pin.
  pinMode(LED1, OUTPUT);     
 
}

// the loop routine runs over and over again forever:
void loop() {
  
  // Write message to serial port
  Serial.println("Hello I'm talking to Serial");
  Serial1.println("Hello I'm talking to Serial1");


  // wait 1 second (1000 milliseconds)
  delay(1000);
  // turn off led 1.
  digitalWrite(LED1,LOW);
  // wait another second
  delay(1000);
  // turn on led 1
  digitalWrite(LED1,HIGH);

}

