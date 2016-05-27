#include <msp430.h>
#include "stdint.h"
#include "moteist_cc2420.h"

#define LED1 0x7F    //P4.7 (active Low)
#define LED2 0xBF    //P4.6 (active Low)
#define LED3 0xDF    //P4.5 (active Low)
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

//Global Variables
char receive_buffer[128];
char send_buffer[128];
char statusByte;
static int channel;

//Functions Prototypes
void toggle_leds(char mask);
void activate_switches(void);
void software_delay(void);
void CS_down(void);
void CS_up(void);
void send_command_CC2420(unsigned int n);
void commandStrobe(char strobe);
void transmit_test_packet(char numero);
void read_test_packet(void);

void cc2420_set_pan(int panid);
void cc2420_set_channel(int c);
int cc2420_get_channel(void);
int cc2420_send(const char *payload, unsigned short pkt_len);
int init_board();


int example(int _channel,int _panid) {

	unsigned char cont = 0;
	unsigned char p1in;
	unsigned int i;

	init_board();

	commandStrobe(SXOSCON); 			// Start Oscilator

	toggle_leds(LED2);

	receive_buffer[0] = 0;
	send_buffer[0] = 0;

	while (receive_buffer[0] == 0) { //for debug
		cont = cont + 1;  // in case cc2420 does not respond, this gets stuck!
		commandStrobe(SNOP);
	}

	P4OUT &= LED1 & LED2 & LED3;                  // Set P4.5-7 for LED

	commandStrobe(STXCAL); 				// Calibrate the oscillator
	commandStrobe(0); // NOP

	toggle_leds(LED2);
	software_delay();
	toggle_leds(LED2);

	cc2420_set_pan(_panid);
	cc2420_set_channel(_channel);

	software_delay();
	toggle_leds(LED2);

	//wait until CC2420 is ready to transmit
	while (statusByte != 0x46) {
		if (statusByte == 0x42 || statusByte == 0x40) {
			commandStrobe(STXCAL);
		} else if (statusByte == 0x4C || statusByte == 0x48) {
			commandStrobe(SRXON);
		} else if (statusByte == 0x66 || statusByte == 0x62) {
			commandStrobe(SFLUSHTX);
		}
		software_delay();
	}
	toggle_leds(LED2);

	cont = 0;

	//transmission-reception cycle
	//when transmitting, both LED1 and LED3 toggle their state
	//when a packet is received, LED2 toggles its state
	while (1) {

		// Interval between transmissions
		for (i=0; i<6; i++){
			software_delay();
		}

		toggle_leds(LED3);

		commandStrobe(SNOP);

		if (statusByte == 0x66) {  //check for TXFIFO underflow
			commandStrobe(SFLUSHTX);
		}

		transmit_test_packet(cont);
		cont++;

		//test for received packet
		p1in = P1IN;
		if ((p1in & FIFOP) > 0) {
			//read_test_packet();

			commandStrobe(SFLUSHRX);
			toggle_leds(LED2);
		}
	}

	return 0;
}

//routine to toggle specific leds
void toggle_leds(char mask) {
	P4OUT ^= (~mask);
}


int init_board(){

	//WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	P5SEL |= 0x0C;                            // Port select XT2
	P7SEL |= 0x03;                            // Port select XT1

	UCSCTL6 &= ~(XT1OFF + XT2OFF);            // Set XT1 & XT2 On
	UCSCTL6 |= XCAP_3;                        // Internal load cap

	// Loop until XT1,XT2 & DCO stabilizes
	do {
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
		// Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;                     	// Clear fault flags
	} while (SFRIFG1 & OFIFG);          		// Test oscillator fault flag

	UCSCTL6 &= ~XT2DRIVE0;                  // Decrease XT2 Drive according to
											// expected frequency
	UCSCTL4 |= SELA_0 + SELS_5;    // Select SMCLK, ACLK source and DCO source*/

	//configure LEDs and set them ON
	P4DIR |= ~LED1 + ~LED2 + ~LED3;            // Set P4.5-7 to output direction
	P4OUT &= LED1 & LED2 & LED3;                  // Set P4.5-7 for LED

	// Configure Timers and SPI mode in msp430f5438
	UCB3CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB3CTL0 |= UCMST + UCSYNC + UCCKPH + UCMSB;    // 3-pin, 8-bit SPI master
													// Clock polarity high, MSB
	UCB3CTL1 |= UCSSEL_1;                     // SMCLK
	UCB3BR0 = 0x02;                           // /2
	UCB3BR1 = 0;                              //
	UCB3CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**

	activate_switches();

	//configure for cc2420 comunication board on CBC2
	P1DIR &= ~SFD & ~FIFO & ~FIFOP & ~CCA;  	//Set as Inputs

	P1REN |= SFD + FIFO + FIFOP + CCA; 		// set pull resistor
	P1OUT &= ~SFD & ~FIFO & ~FIFOP & ~CCA;  	// set pull-Down
	P9DIR |= RESET + VREGEN;			 // set Reset and VREGEN pins as outputs
	P10DIR |= CS;						// Set as Output
	P10SEL |= CLK + SIMO + SOMI;		// select SPI function instead of GPI/O
	P10DIR &= ~SOMI;                   	// set SOMI as input
	P10OUT &= ~P10MASK;  				//Unsed pins go low

	//Inicialize zigbee CB
	P9OUT |= VREGEN;		//Start the voltage regulator to have 1.8 for core
	P9OUT &= ~RESET;				    //Reset (active Low)
	software_delay();
	P9OUT |= RESET;						//Release reset
	CS_up();
}

//routine to activate the switches that supply power to the communication boards
void activate_switches(void) {
	P3SEL |= 0x80;                            // P3.7 - SDA - Assign I2C pins
	P5SEL |= 0x10;							  // P5.4 - SCL

	UCB1CTL1 |= UCSWRST;                      // Enable SW reset

	UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	UCB1CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK
	UCB1BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
	UCB1BR1 = 0;
	UCB1I2CSA = 0x48; // Slave Address is 090h 1001 0000 -> address (7bit, A0=A1=0) + R/!W

	UCB1CTL1 &= ~UCSWRST;                     // Clear SW reset*/

	while (UCB1CTL1 & UCTXSTP);               // Ensure stop condition got sent

	UCB1CTL1 |= UCTR + UCTXSTT;               // I2C start condition
	UCB1TXBUF = 0xFF;  	                      // Send init data

	while (UCB1CTL1 & UCTXSTT);                // Start condition sent?

	UCB1CTL1 |= UCTXSTP;				      // I2C1 Stop Condition
}

//generic software delay routine
void software_delay(void) {
	volatile unsigned int i;

	for (i = 50000; i != 0; i--);
	// Empty block

}

//routine to lower CC2420 chip select
void CS_down(void) {
	P10OUT &= NCS;
}

#define CC2420_SPI_ENABLE() CS_down(); /* ENABLE CSn (active low) */

//routine to pull CC2420 chip select up
void CS_up(void) {
	P10OUT |= CS;
}

#define CC2420_SPI_DISABLE() CS_up(); /* ENABLE CSn (active low) */

//routine to send a generic command to CC2420
//the input is the number of bytes to send
//the command is read from send_buffer array
//CC2420 status is stored in statusByte
void send_command_CC2420(unsigned int n) {
	volatile unsigned int i;

	CS_down();

	for (i = 0; i < n; i++) {

		UCB3TXBUF = send_buffer[i];

		while (!(UCB3IFG & UCTXIFG) || !(UCB3IFG & UCRXIFG));

		receive_buffer[i] = UCB3RXBUF;
	}

	statusByte = receive_buffer[0];

	CS_up();
}

//routine to send a command strobe to CC2420
//the input is the strobe to send (one byte only)
void commandStrobe(char strobe) {

	software_delay();

	send_buffer[0] = strobe;
	send_command_CC2420(1);
}

int cc2420_get_channel(void) {

	return channel;
}

//routine to change the channel in which CC2420 operates
void cc2420_set_channel(int c) {

	uint16_t f;

	/*
	 * Subtract the base channel (11), multiply by 5, which is the
	 * channel spacing. 357 is 2405-2048 and 0x4000 is LOCK_THR = 1.
	 */
	channel = c;

	f = 5 * (c - 11) + 357 + 0x4000;

	send_buffer[0] = CC2420_FSCTRL;
	send_buffer[1] = f >> 8;
	send_buffer[2] = f & 0xff;
	send_buffer[3] = 0;
	send_command_CC2420(4);

	commandStrobe(CC2420_SRXON);
}

int cc2420_send(const char *payload, unsigned short pkt_len){

	unsigned int i;
	unsigned int reg_len = 1;
	unsigned int preamble_len = 3;

	send_buffer[0] = TXFIFO;  								//TXFIFO address
	send_buffer[1] = reg_len+preamble_len+pkt_len;	//packet length
	send_buffer[2] = 0x41;
	send_buffer[3] = 0x88;

	for (i=0; i<pkt_len; i++){
		send_buffer[reg_len + preamble_len + i] = payload[i];
	}

	send_command_CC2420(reg_len + preamble_len + pkt_len);

	commandStrobe(STXON);

}


//routine to build and transmit the test packet
void transmit_test_packet(char seq) {

	int pkt_len = 9;
	char pkt[pkt_len];

	pkt[0] = seq;
	pkt[1] = 0x22;		//PAN ID low
	pkt[2] = 0x00;  	//PAN ID high
	pkt[3] = 0xFF;  	//dest addr low
	pkt[4] = 0xFF;		//dest addr high

	pkt[5] = 0x01;		//src addr low
	pkt[6] = 0x00;		//src addr high

	// -- payload -- //
	pkt[7] = 0x3f;
	pkt[8] = 0xf0;

	cc2420_send(pkt,pkt_len);
}


void cc2420_set_pan(int panid){

	send_buffer[0] = 0xE8;
	send_buffer[1] = 0x80;

	send_buffer[2] = panid & 0xff;
	send_buffer[3] = panid >> 8;

	send_command_CC2420(4);
}


//routine to build and transmit the test packet
void read_test_packet(void) {

	int i;

	CS_down();

	UCB3TXBUF = RXFIFO;
	while (!(UCB3IFG & UCTXIFG));

	for (i = 0; i < 127; i++) {

		while(!(UCB3IFG & UCRXIFG));
		receive_buffer[i] = UCB3RXBUF;
	}

	statusByte = receive_buffer[0];

	CS_up();

}
