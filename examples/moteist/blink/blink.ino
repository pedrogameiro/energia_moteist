/*
   Blink
   The basic Energia example.
   Turns on an LED on for one second, then off for one second, repeatedly.
   Change the LED define to blink other LEDs.


   This example code is in the public domain.
*/

int leds[3] = { LED1, LED2, LED3 };
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

    for (i=0; i<ledsnum; i++){
        
        if (digitalRead(leds[i]) == HIGH)
            digitalWrite(leds[i],LOW);
        else 
            digitalWrite(leds[i],HIGH);  
    }
    
    delay(2000);
}
