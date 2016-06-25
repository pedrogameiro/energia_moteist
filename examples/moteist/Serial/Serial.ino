
// the setup routine runs once when you press reset:
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial1.begin(9600);
  Serial.begin(9600);
  
  pinMode(LED1, OUTPUT);     
 
}

// the loop routine runs over and over again forever:
void loop() {
  
  Serial1.println("Hello I'm talking to Serial1");
  Serial.println("Hello I'm talking to Serial");


  delay(1000);
  digitalWrite(LED1,LOW);
  delay(1000);
  digitalWrite(LED1,HIGH);

}


