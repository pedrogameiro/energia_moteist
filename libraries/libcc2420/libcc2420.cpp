#include <msp430.h>
#include "stdint.h"
#include "libcc2420.h"
#include "libcc2420_spi.h"
#include "platform-conf.h"


//Global Variables
char receive_buffer[128];
char send_buffer[128];
char statusByte;
static int channel;

//Functions Prototypes
void toggle_leds(char mask);
void activate_switches(void);
void software_delay(void);
void send_command_CC2420(unsigned int n);
void commandStrobe(char strobe);
void transmit_test_packet(char numero);
int cc2420_recv(void *buf, unsigned short bufsize);
void cc2420_set_pan(int panid);
void cc2420_set_channel(int c);
int cc2420_get_channel(void);
void cc2420_send(const char *payload, unsigned short pkt_len);
void cc2420_init(int _channel,int _panid);
void cc2420_set_txpower(uint8_t power);
int cc2420_get_txpower(void);
static void strobe(enum cc2420_register regname);
static uint16_t getreg(enum cc2420_register regname);

/* Are we currently in poll mode? */
static uint8_t volatile poll_mode = 1;
signed char cc2420_last_rssi;
uint8_t cc2420_last_correlation;

/* Conversion map between PA_LEVEL and output power in dBm
   (from table 9 in CC2420 specification).
*/
struct output_config {
  int8_t power;
  uint8_t config;
  uint16_t reg;
};

static const struct output_config output_power[] = {
	  {  0, 31, 0xA0FF }, /* 0xff */
	  { -1, 27, 0xA0FC }, /* 0xfb */
	  { -3, 23, 0xA0F9 }, /* 0xf7 */
	  { -5, 19, 0xA0F6 }, /* 0xf3 */
	  { -7, 15, 0xA0F3 }, /* 0xef */
	  {-10, 11, 0xA0F0 }, /* 0xeb */
	  {-15,  7, 0xA0ED }, /* 0xe7 */
	  {-25,  3, 0xA0EA }, /* 0xe3 */
};
#define OUTPUT_NUM (sizeof(output_power) / sizeof(struct output_config))
#define OUTPUT_POWER_MAX   0
#define OUTPUT_POWER_MIN -25


//routine to toggle specific leds
void toggle_leds(char mask) {
	LED_PORT(OUT) ^= (~mask);
}

void cc2420_init(int _channel,int _panid){

	//WDTCTL = WDTPW + WDTHOLD;                  // Stop WDT
	P5SEL |= 0x0C;                           	 // Port select XT2
	P7SEL |= 0x03;                           	 // Port select XT1

	UCSCTL6 &= ~(XT1OFF + XT2OFF);           	 // Set XT1 & XT2 On
	UCSCTL6 |= XCAP_3;                       	 // Internal load cap

	// Loop until XT1,XT2 & DCO stabilizes
	do {
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
		// Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;                     	// Clear fault flags
	} while (SFRIFG1 & OFIFG);          		// Test oscillator fault flag

	UCSCTL6 &= ~XT2DRIVE0;               	    // Decrease XT2 Drive according to
												// expected frequency
	UCSCTL4 |= SELA_0 + SELS_5;    				// Select SMCLK, ACLK source and DCO source*/

	//configure LEDs and set them ON
	//LED_PORT(DIR) |= ~LED1_PIN + ~LED2_PIN + ~LED3_PIN;            	  // Set P4.5-7 to output direction
	//LED_PORT(OUT) &= LED1_PIN & LED2_PIN & LED3_PIN;                  // Set P4.5-7 for LED

	// Configure Timers and SPI mode in msp430f5438
	UCB3CTL1 |= UCSWRST;                      		// **Put state machine in reset**
	UCB3CTL0 |= UCMST + UCSYNC + UCCKPH + UCMSB;    // 3-pin, 8-bit SPI master
													// Clock polarity high, MSB
	UCB3CTL1 |= UCSSEL_1;                     // SMCLK
	UCB3BR0 = 0x02;                           // /2
	UCB3BR1 = 0;                              //
	UCB3CTL1 &= ~UCSWRST;                  	  // **Initialize USCI state machine**

	activate_switches();

	//
	/* configure for cc2420 comunication board on CBC2 */
	//

	//Set as Inputs
	CC2420_SFD_PORT(DIR) &= ~CC2420_SFD_PIN;
	CC2420_FIFO_PORT(DIR) &= ~CC2420_FIFO_PIN;
	CC2420_FIFOP_PORT(DIR) &= ~CC2420_FIFOP_PIN;
	CC2420_CCA_PORT(DIR) &= ~CC2420_CCA_PIN;

	// set pull resistor
	CC2420_SFD_PORT(REN) |= CC2420_SFD_PIN;
	CC2420_FIFO_PORT(REN) |= CC2420_FIFO_PIN;
	CC2420_FIFOP_PORT(REN) |= CC2420_FIFOP_PIN;
	CC2420_CCA_PORT(REN) |= CC2420_CCA_PIN;

	// set pull-Down
	CC2420_SFD_PORT(OUT) &= ~CC2420_SFD_PIN;
	CC2420_FIFO_PORT(OUT) &= ~CC2420_FIFO_PIN;
	CC2420_FIFOP_PORT(OUT) &= ~CC2420_FIFOP_PIN;
	CC2420_CCA_PORT(OUT) &= ~CC2420_CCA_PIN;

	// set Reset and VREGEN pins as outputs
	CC2420_RESET_PORT(DIR) |= CC2420_RESET_PIN;
	CC2420_VREGEN_PORT(DIR) |= CC2420_VREGEN_PIN;

	// Set as Output
	CC2420_CS_PORT(DIR) |= CC2420_CS_PIN;

	// select SPI function instead of GPI/O
	CC2420_CLK_PORT(SEL) |= CC2420_CLK_PIN;
	CC2420_SIMO_PORT(SEL) |= CC2420_SIMO_PIN;
	CC2420_SOMI_PORT(SEL) |= CC2420_SOMI_PIN;

	CC2420_SOMI_PORT(DIR) &= ~CC2420_SOMI_PIN;          // set SOMI as input
	P10OUT &= ~P10_UNUSED_MASK;  						//Unsed pins go low

	//Inicialize zigbee CB
	CC2420_VREGEN_PORT(OUT) |= CC2420_VREGEN_PIN;					//Start the voltage regulator to have 1.8 for core

	CC2420_RESET_PORT(OUT) &= ~CC2420_RESET_PIN;				    //Reset (active Low)
	software_delay();
	CC2420_RESET_PORT(OUT) |= CC2420_RESET_PIN;						//Release reset

	CC2420_SPI_DISABLE();

	// Start Oscilator
	commandStrobe(CC2420_SXOSCON);
	//toggle_leds(LED2_PIN);

	receive_buffer[0] = 0;
	send_buffer[0] = 0;

	while (receive_buffer[0] == 0) { //for debug
		// in case cc2420 does not respond, this gets stuck!
		commandStrobe(CC2420_SNOP);
	}

	//LED_PORT(OUT) &= LED1_PIN & LED2_PIN & LED3_PIN;                // Set P4.5-7 for LED

	commandStrobe(CC2420_STXCAL); 						// Calibrate the oscillator
	commandStrobe(0); // NOP


	//toggle_leds(LED2_PIN);
	software_delay();
	//toggle_leds(LED2_PIN);

	cc2420_set_pan(_panid);
	cc2420_set_channel(_channel);

	software_delay();
	//toggle_leds(LED2_PIN);

	//wait until CC2420 is ready to transmit
	while (statusByte != 0x46) {
		if (statusByte == 0x42 || statusByte == 0x40) {
			commandStrobe(CC2420_STXCAL);
		} else if (statusByte == 0x4C || statusByte == 0x48) {
			commandStrobe(CC2420_SRXON);
		} else if (statusByte == 0x66 || statusByte == 0x62) {
			commandStrobe(CC2420_SFLUSHTX);
		}
		software_delay();
	}

	//toggle_leds(LED2_PIN);

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
	UCB1I2CSA = 0x48; 						  // Slave Address is 090h 1001 0000 -> address (7bit, A0=A1=0) + R/!W

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

//routine to send a generic command to CC2420
//the input is the number of bytes to send
//the command is read from send_buffer array
//CC2420 status is stored in statusByte
void send_command_CC2420(unsigned int n) {
	volatile unsigned int i;

	CC2420_SPI_ENABLE();

	for (i = 0; i < n; i++) {

		UCB3TXBUF = send_buffer[i];

		while (!(UCB3IFG & UCTXIFG) || !(UCB3IFG & UCRXIFG));

		receive_buffer[i] = UCB3RXBUF;
	}

	statusByte = receive_buffer[0];

	CC2420_SPI_DISABLE();
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

void cc2420_send(const char *payload, unsigned short pkt_len){

	unsigned int i;
	unsigned int reg_len = 1;
	unsigned int preamble_len = 3;

	commandStrobe(CC2420_SNOP);
	if (statusByte == 0x66) {  //check for TXFIFO underflow
		commandStrobe(CC2420_SFLUSHTX);
	}

	send_buffer[0] = CC2420_TXFIFO;  								//TXFIFO address
	send_buffer[1] = reg_len+preamble_len+pkt_len;		    //packet length

	send_buffer[2] = 0x41;
	send_buffer[3] = 0x88;

	for (i=0; i<pkt_len; i++){
		send_buffer[reg_len + preamble_len + i] = payload[i];
	}

	send_command_CC2420(reg_len + preamble_len + pkt_len);

	commandStrobe(CC2420_STXON);
	//toggle_leds(LED2_PIN);

}


//routine to build and transmit the test packet
void transmit_test_packet(char seq) {


}

void setreg(enum cc2420_register regname, uint16_t value)
{
  CC2420_SPI_ENABLE();
  SPI_WRITE_FAST(regname);
  SPI_WRITE_FAST((uint8_t) (value >> 8));
  SPI_WRITE_FAST((uint8_t) (value & 0xff));
  SPI_WAITFORTx_ENDED();
  SPI_WRITE(0);
  CC2420_SPI_DISABLE();
}

/*---------------------------------------------------------------------------*/
/* Returns the current status */
static uint8_t get_status(void)
{
  uint8_t status;

  CC2420_SPI_ENABLE();
  SPI_WRITE(CC2420_SNOP);
  status = SPI_RXBUF;
  CC2420_SPI_DISABLE();

  return status;
}

void cc2420_set_pan(int panid){

	send_buffer[0] = 0xE8;
	send_buffer[1] = 0x80;

	send_buffer[2] = panid & 0xff;
	send_buffer[3] = panid >> 8;

	send_command_CC2420(4);
}

static void getrxdata(uint8_t *buffer, int count)
{
  uint8_t i;

  CC2420_SPI_ENABLE();
  SPI_WRITE(CC2420_RXFIFO | 0x40);
  (void) SPI_RXBUF;
  for(i = 0; i < count; i++) {
    SPI_READ(buffer[i]);
  }
  CC2420_SPI_DISABLE();
}

/*---------------------------------------------------------------------------*/
/* Sends a strobe */
static void strobe(enum cc2420_register regname)
{
  CC2420_SPI_ENABLE();
  SPI_WRITE(regname);
  CC2420_SPI_DISABLE();
}

static void flushrx(void)
{
  uint8_t dummy;

  getrxdata(&dummy, 1);
  strobe(CC2420_SFLUSHRX);
  strobe(CC2420_SFLUSHRX);
  if(dummy) {
    /* avoid unused variable compiler warning */
  }
}


//routine to build and transmit the test packet
int cc2420_recv(void *buf, unsigned short bufsize) {

	  uint8_t footer[FOOTER_LEN];
	  uint8_t len;

	  if(!CC2420_FIFOP_IS_1) {
	    return 0;
	  }

	  getrxdata(&len, 1);

	  if(len > CC2420_MAX_PACKET_LEN) {
	    /* Oops, we must be out of sync. */
	  } else if(len <= FOOTER_LEN) {
		// To short
	  } else if(len - FOOTER_LEN > bufsize) {
		// To long
	  } else {

	    getrxdata((uint8_t *) buf, len - FOOTER_LEN);
	    getrxdata(footer, FOOTER_LEN);

	    if(footer[1] & FOOTER1_CRC_OK) {
	      cc2420_last_rssi = footer[0] + RSSI_OFFSET;
	      cc2420_last_correlation = footer[1] & FOOTER1_CORRELATION;
	      if(!poll_mode) {
	        /* Not in poll mode: packetbuf should not be accessed in interrupt context.
	         * In poll mode, the last packet RSSI and link quality can be obtained through
	         * RADIO_PARAM_LAST_RSSI and RADIO_PARAM_LAST_LINK_QUALITY */
	        //packetbuf_set_attr(PACKETBUF_ATTR_RSSI, cc2420_last_rssi);
	        //packetbuf_set_attr(PACKETBUF_ATTR_LINK_QUALITY, cc2420_last_correlation);
	      }

	    } else {
	      len = FOOTER_LEN;
	    }

	    if(!poll_mode) {
	      if(CC2420_FIFOP_IS_1) {
	        if(!CC2420_FIFO_IS_1) {
	          /* Clean up in case of FIFO overflow!  This happens for every
	           * full length frame and is signaled by FIFOP = 1 and FIFO =
	           * 0. */
	          flushrx();
	        } else {
	          /* Another packet has been received and needs attention. */
	          //process_poll(&cc2420_process);
	        }
	      }
	    }

		//toggle_leds(LED3_PIN);
		commandStrobe(CC2420_SFLUSHRX);

	    return len - FOOTER_LEN;
	  }

	  flushrx();
	  return 0;
}
/*---------------------------------------------------------------------------*/
/* Reads a register */
static uint16_t getreg(enum cc2420_register regname)
{
  uint16_t value;

  CC2420_SPI_ENABLE();
  SPI_WRITE(regname | 0x40);
  value = (uint8_t)SPI_RXBUF;
  SPI_TXBUF = 0;
  SPI_WAITFOREORx();
  value = SPI_RXBUF << 8;
  SPI_TXBUF = 0;
  SPI_WAITFOREORx();
  value |= SPI_RXBUF;
  CC2420_SPI_DISABLE();

  return value;
}
/*---------------------------------------------------------------------------*/
static void set_txpower(uint8_t level)
{

	uint16_t power = output_power[level].reg;
	uint16_t reg;

	reg = getreg(CC2420_TXCTRL);
	reg = (reg & 0xffe0) | (power & 0x1f); // Only replace the first 5 bits.

	send_buffer[0] = CC2420_TXCTRL;
	send_buffer[1] = reg >> 8;
	send_buffer[2] = reg & 0xff;
	send_buffer[3] = 0;
	send_command_CC2420(4);

}
/*---------------------------------------------------------------------------*/
void cc2420_set_txpower(uint8_t level)
{
  set_txpower(level);
}
/*---------------------------------------------------------------------------*/
int cc2420_get_txpower(void)
{
  int power;
  power = (int)(getreg(CC2420_TXCTRL) & 0x001f);
  return power;
}

