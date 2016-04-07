// # vim: foldenable foldmethod=marker foldlevel=0 foldnestmax=10

// {{{ Includes

#include "Energia.h"
#include "radio.h"

// }}}

// {{{ Definitions

//#define LED1 0x7F    //P4.7 (active Low)
//#define LED2 0xBF    //P4.6 (active Low)
//#define LED3 0xDF    //P4.5 (active Low)
#define SFD 0x02// P1.1
#define FIFO 0x04// P1.2
#define FIFOP 0x40// P1.6
#define CCA 0x80// P1.7
#define RESET 0x80// P9.7
#define VREGEN 0x40// P9.6

#define CS 0x01 //P10.0 chip select High
#define SIMO 0x02 //P10.1
#define SOMI 0x04 //P10.2
#define CLK 0x08 //P10.3
#define NCS 0xFE //chip select Low
#define P10MASK 0xF0 //P3.4,5,6,7 Not used for cc2420 Comunication Board

//CC2420 Command Strobes & Registers
#define SNOP 0x00 //No Operation (has no other effect than reading out status-bits)
#define SXOSCON 0x01 //Turn on the crystal oscillator (set XOSC16M_PD = 0 and BIAS_PD = 0)
#define STXCAL 0x02 //Enable and calibrate frequency synthesizer for TX; Go from RX / TX to a wait state where only the synthesizer is running.
#define SRXON 0x03 //Enable RX
#define STXON 0x04 //Enable TX after calibration (if not already performed) Start TX in-line encryption if SPI_SEC_MODE ? 0
#define STXONCCA 0x05 //If CCA indicates a clear channel: Enable calibration, then TX. Start in-line encryption if SPI_SEC_MODE ? 0 else do nothing
#define SRFOFF 0x06 //Disable RX/TX and frequency synthesizer
#define SXOSCOFF 0x07 //Turn off the crystal oscillator and RF
#define SFLUSHRX 0x08 //Flush the RX FIFO buffer and reset the demodulator. Always read at least one byte from the RXFIFO before issuing the SFLUSHRX command strobe
#define SFLUSHTX 0x09 //Flush the TX FIFO buffer
#define SACK 0x0A //Send acknowledge frame, with pending field cleared.
#define SACKPEND 0x0B // Send acknowledge frame, with pending field set.
#define SRXDEC 0x0C //Start RXFIFO in-line decryption / authentication (as set by SPI_SEC_MODE)
#define STXENC 0x0D //Start TXFIFO in-line encryption / authentication (as set by SPI_SEC_MODE), without starting TX.
#define SAES 0x0E //AES Stand alone encryption strobe. SPI_SEC_MODE is not required to be 0, but the encryption module must be idle. If not, the strobe is ignored.
//0x0F  Not used
#define MAIN 0x10 // R/W Main Control Register
#define MDMCTRL0 0x11 // R/W Modem Control Register 0
#define MDMCTRL1 0x12 //R/W Modem Control Register 1
#define RSSI 0x13 // R/W RSSI and CCA Status and Control register
#define SYNCWORD 0x14 // R/W Synchronisation word control register
#define TXCTRL 0x15 // R/W Transmit Control Register
#define RXCTRL0 0x16 // R/W Receive Control Register 0
#define RXCTRL1 0x17 // R/W Receive Control Register 1
#define FSCTRL 0x18 // R/W Frequency Synthesizer Control and Status Register
#define SECCTRL0 0x19 //R/W Security Control Register 0
#define SECCTRL1 0x1A // R/W Security Control Register 1
#define BATTMON 0x1B // R/W Battery Monitor Control and Status Register
#define IOCFG0 0x1C // R/W Input / Output Control Register 0
#define IOCFG1 0x1D // R/W Input / Output Control Register 1
#define MANFIDL 0x1E  // R/W Manufacturer ID, Low 16 bits
#define MANFIDH 0x1F // R/W Manufacturer ID, High 16 bits
#define FSMTC 0x20 // R/W Finite State Machine Time Constants
#define MANAND 0x21 // R/W Manual signal AND override register
#define MANOR 0x22 // R/W Manual signal OR override register
#define AGCCTRL 0x23 // R/W AGC Control Register
#define AGCTST0 0x24 // R/W AGC Test Register 0
#define AGCTST1 0x25 // R/W AGC Test Register 1
#define GCTST2 0x26 // R/W AGC Test Register 2
#define FSTST0 0x27 // R/W Frequency Synthesizer Test Register 0
#define FSTST1 0x28 // R/W Frequency Synthesizer Test Register 1
#define FSTST2 0x29 // R/W Frequency Synthesizer Test Register 2
#define FSTST3 0x2A // R/W Frequency Synthesizer Test Register 3
#define RXBPFTST 0x2B // R/W Receiver Bandpass Filter Test Register
#define FSMSTATE 0x2C // R Finite State Machine State Status Register
#define ADCTST 0x2D //R/W ADC Test Register
#define DACTST 0x2E // R/W DAC Test Register
#define TOPTST 0x2F // R/W Top Level Test Register
#define RESERVED 0x30 // R/W Reserved for future use control / status register
//0x31-0x3D Not Used
#define TXFIFO 0x3E // W Transmit FIFO Byte Register
#define RXFIFO 0x3F // R/W Receiver FIFO Byte Register

/// }}}


Radio::Radio(){
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

//routine to toggle specific leds
void Radio::toggle_pin(uint8_t pin){
 int state = digitalRead(pin);
  if (state == LOW)
    digitalWrite(pin,HIGH);
  else if (state == HIGH)
    digitalWrite(pin,LOW);
}

//routine to activate the switches that supply power to the communication boards
void Radio::activate_switches(void){
	P3SEL |= 0x80;                            // P3.7 - SDA - Assign I2C pins
	P5SEL |= 0x10;							  // P5.4 - SCL
                             
	UCB1CTL1 |= UCSWRST;                      // Enable SW reset
  
	UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	UCB1CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK
	UCB1BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  	UCB1BR1 = 0;
  	UCB1I2CSA = 0x48;                         // Slave Address is 090h 1001 0000 -> address (7bit, A0=A1=0) + R/!W
  
  	UCB1CTL1 &= ~UCSWRST;                     // Clear SW reset*/

	while (UCB1CTL1 & UCTXSTP);               // Ensure stop condition got sent
    UCB1CTL1 |= UCTR + UCTXSTT;               // I2C start condition
  	UCB1TXBUF = 0xFF;  	                      // Send init data
  	while(UCB1CTL1 & UCTXSTT);                // Start condition sent?
  	UCB1CTL1 |= UCTXSTP;				      // I2C1 Stop Condition
}

//generic software delay routine
void Radio::software_delay(void){
	volatile unsigned int i;

	for(i=50000;i!=0;i--){};	
}

//routine to lower CC2420 chip select
void Radio::CS_down(void){
	P10OUT &= NCS;
}

//routine to pull CC2420 chip select up
void Radio::CS_up(void){
	P10OUT|=CS;
}

//routine to send a generic command to CC2420 
//the input is the number of bytes to send 
//the command is read from send_buffer array
//CC2420 status is stored in statusByte
void Radio::send_command_CC2420(unsigned int n){
	volatile unsigned int i;

	CS_down();

	for(i=0;i<n;i++){
		UCB3TXBUF = send_buffer[i];
		while (!(UCB3IFG&UCTXIFG) || !(UCB3IFG&UCRXIFG));
		receive_buffer[i]=UCB3RXBUF;
	}
	
	statusByte = receive_buffer[0];
	
	CS_up();
}

//routine to send a command strobe to CC2420
//the input is the strobe to send (one byte only)
void Radio::commandStrobe(char strobe){

	software_delay();
	
	send_buffer[0] = strobe;
	send_command_CC2420(1);
}

//routine to change the channel in which CC2420 operates
void Radio::change_frequency_channel(int channel){
	unsigned int freq, aux;
	unsigned char byte_high, byte_low;
	
	freq = 357 + 5 * (channel - 11);
	
	aux = freq & 0xFF00;
	
	byte_high = aux >> 8;
	byte_low = freq & 0x00FF;
	
	send_buffer[0]=FSCTRL;
	send_buffer[1]=byte_high;
	send_buffer[2]=byte_low;
	send_command_CC2420(3);
}


//routine to build and transmit the test packet
void Radio::transmit_test_packet(char numero){
	int i;
	
	send_buffer[0]=TXFIFO;  //TXFIFO address
    send_buffer[1]=127;		//packet length
    send_buffer[2]=0x41;
    send_buffer[3]=0x88;
    send_buffer[4]=0x01;
    send_buffer[5]=0x22;	//PAN ID low
    send_buffer[6]=0x00;    //PAN ID high      
    send_buffer[7]=0xFF;    //destination address low     
    send_buffer[8]=0xFF;	//destination address high
    send_buffer[9]=0x02;	//source address low
    send_buffer[10]=0x00;	//source address high
    send_buffer[11]=0x3F;                     
    send_buffer[12]=0x06;                     
    send_buffer[13]=numero;
    send_buffer[14]=0x02;                     
    send_buffer[15]=0x00;
    send_buffer[16]=0x01;                     
    send_buffer[17]=0x3E;
    for(i=18;i<128;i++)
        send_buffer[i]=i;
    send_command_CC2420(127);

    commandStrobe(STXON);
}
