
#include <SPI.h>

// P2.4 7Segment Display
const int SS = CBC1_8;

/*7 display segment*/
char decode[] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
 
int n =0;

void setup()
{
    pinMode (SS, OUTPUT);
    SPI.begin();

}

void loop()
{
  
    digitalWrite(SS,LOW);
    SPI.transfer(decode[n]); // Second digit of display
    SPI.transfer(decode[++n]);  // First digit of display
    digitalWrite(SS,HIGH); 
    
    delay(1000);
    
    if(n==15)
        n=0;

}




