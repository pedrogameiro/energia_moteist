/*
  DigitalReadSerial with on-board Pushbutton
  Reads a digital input on pin 4(SWITCH3) or 6(SWITCH4), prints the result to the serial monitor 
 
  Hardware Required:
  * PepeOnBoard
  
  This example code is in the public domain.
 */

//  PepeOnBoard Switch 3( pin4 ) and Switch 4 (pin 6) has a pushbutton attached to it.
int pushButton1 = SWITCH3;
int pushButton2 = SWITCH4;
int switch1 = SWITCH1;
int switch2 = SWITCH2;
int counter;
int control;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  // make the on-board pushbutton's pin an input pullup:
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  counter = 0;
  control = 0;
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState1 = digitalRead(pushButton1);
  int buttonState2 = digitalRead(pushButton2);
  int switchState1 = digitalRead(switch1);
  int switchState2 = digitalRead(switch2);
  
  if(switchState1 == HIGH){
    digitalWrite(LED1,HIGH);
    delay(500);
    resetLED();
    delay(500);
  }
  else if(switchState2 == HIGH){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    delay(500);
    resetLED();
    delay(500);
  }
  else if(buttonState1==HIGH){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,HIGH);
    delay(500);
    resetLED();
    delay(500);
  }
  else if(buttonState2==HIGH){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,HIGH);
    delay(500);
   resetLED();
    delay(500);
  }
  else if(switchState1==LOW && switchState2==LOW && buttonState1==LOW && buttonState2==LOW){
    if(counter==0){
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      delay(100);
    }
    else if(counter==1){
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      delay(100);
    }
    else if(counter==2){
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,LOW);
      delay(100);
    }
    else if(counter==3){
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,HIGH);
      delay(100);
    }
  }
  
  if(control==0){
    counter++;
    if(counter==3)
      control=1;
  }
  else if(control==1){
    counter--;
    if(counter==0)
      control=0;
  }
}

void resetLED(){
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
}



