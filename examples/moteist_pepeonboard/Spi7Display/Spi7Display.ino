
/*

    Spi7Display
    A simple SPI 7 segment display manipulation example.

    The two digit display value will loop from 00 to FF 
    in hexadecimal values, in intervals of 1 second.

*/


#include <SPI.h>

// P2.4 7Segment Display
const int SS = CBC1_8;

// 7 seg. display translation table. The N position
// of this table contains the hex value that will
// draw the said value on the display.
char decode[] = {0x3F, 0x6, 0x5B, 0x4F, 0x66,
                 0x6D, 0x7D, 0x7, 0x7F, 0x67,
                 0x77, 0x7C, 0x39, 0x5E, 0x79,
                 0x71};

// Current number on display.
int num=0;

// Toggles leds value
void toogled(int led){

    int ledstate;

    // read led value
    ledstate = digitalRead(led);

    // toogle value
    if (ledstate == LOW)
        digitalWrite(led,HIGH);
    else
        digitalWrite(led,LOW);
}


// the setup routine runs once when you press reset:
void setup()
{
    // init the SPI slave select pin as output.
    pinMode (SS, OUTPUT);
    // init the led2 as output for debuging.
    pinMode (LED2, OUTPUT);
    
    // init the Serial bus with 9600 baud rate.
    // also for debuging.
    Serial.begin(9600); 

    // init the spi bus.
    SPI.begin();

}


// the loop routine runs over and over again forever:
void loop()
{
  
    // print debug info
    Serial.print("Changing display to "+num);

    digitalWrite(SS,LOW);         // Select SPI slave
    SPI.transfer(decode[num]);    // Second digit of display
    SPI.transfer(decode[num++]);  // First digit of display
    digitalWrite(SS,HIGH);        // Release SPI slave
    
    // toogle led state
    toogled(LED2);
    
    // wait for 1 second (1000 milliseconds)
    delay(1000);
    
    // if overflow, we reached 0xff, reseting to 0x00
    if(num==15)
        num=0;
}




