/*
   Blink
   The basic Energia example.

   Turns on the three leds of MoteIST for one second,
   then off for one second, repeatedly.

*/

int leds[3] = {  LED2 };
int ledsnum = sizeof(leds) / sizeof(leds[0]);
int i;

// the setup routine runs once when you press reset:
void setup() {                

    // initialize the digital pin as an output.
    for (i=0; i<ledsnum; i++)
        pinMode(leds[i], OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {

    // loop through the three leds.
    for (i=0; i<ledsnum; i++){
        
        // toogle the led state. aka Blinky blink! =)
        if (digitalRead(leds[i]) == HIGH) // read the led state
            digitalWrite(leds[i],LOW);    // write low state
        else if (digitalRead(leds[i]) == LOW)
            digitalWrite(leds[i],HIGH); 
    }
    
    // wait for 1 second (1000 milliseconds), forcing 
    // a blink frequency of approximately 2Hz.
    delay(1000);
}
