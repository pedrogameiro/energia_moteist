// # vim: foldenable foldmethod=marker foldlevel=0 foldnestmax=10

#ifndef Pins_Energia_h
#define Pins_Energia_h

/* {{{ LICENSE
  ************************************************************************
  *	pins_energia.h
  *
  *	    Energia core files for MSP430F5438 MoteIST++
  *
  *		  Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *     Contribution: Rei VILO
  *
  ***********************************************************************
  Derived from:
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
 }}}*/

// {{{ Defines

#ifndef BV
#define BV(x) (1 << (x))
#endif

// }}}

// {{{ Constants
#if defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__)
// Constants for SPI		        /*  Port / MoteIST Label   */
static const uint8_t SS      = 16;  /*  P3.0  / CB1_SCLKO/CS1  */
static const uint8_t SCK     = 19;  /*  P3.3  / CB1_CSO/SCLK1  */
static const uint8_t MOSI    = 18;  /*  P3.1  / CB1_SIMO1/SDA1 aka SIMO  */
static const uint8_t MISO    = 20;  /*  P3.2  / CB1_SOMI1/SCL1 aka SOMI  */

// Constants for I2C
static const uint8_t TWISDA  = 38;  /*  P10.1 / CB2_SIMO1/SDA1 */
static const uint8_t TWISCL  = 40;  /*  P10.2 / CB2_SOMI1/SCL1 */

										  /* Port / MoteIST Label       */
static const uint8_t DEBUG_UARTRXD = 11;  /* P3.5  / CB1_UCA0(RXD/SOMI) */
static const uint8_t DEBUG_UARTTXD = 13;  /* P3.4  / CB1_UCA0(TXD/SIMO) */
static const uint8_t AUX_UARTRXD = 31;    /* P10.5 / CB2_UCA3(RXD/SOMI) */ 
static const uint8_t AUX_UARTTXD = 33;	  /* P10.4 / CB2_UCA3(TXD/SIMO) */ 
#define TWISDA_SET_MODE (PORT_SELECTION0)
#define TWISCL_SET_MODE (PORT_SELECTION0)
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1| INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1 | OUTPUT)
#define AUX_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define AUX_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define SPISCK_SET_MODE (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
#endif

#define DEBUG_UART_MODULE_OFFSET 0x40
#define AUX_UART_MODULE_OFFSET 0x0
#define SERIAL1_AVAILABLE 1

#if defined(__MSP430_HAS_USCI_A1__)
#define USE_USCI_A1
#endif

// MoteIST++ analogic pins (To be defined)
static const uint8_t A0 = 14;//CB1_ADC
static const uint8_t A1 = 76;//ADC7
static const uint8_t A2 = 77;//ADC6
static const uint8_t A3 = 78;//ADC5
static const uint8_t A4 = 79;//ADC4

// }}}

/* {{{ MSP430F5438a MoteIST++ pin mapping

					 CBC1            						              CBC2
				   +--\/--+                                             +--\/--+
    CB1_NMI_SBWTD01|1    2|CB1_SFD/TA10                  RST_NMI_SBWTDOI|1    2|CB2_INT0 
          CB1_GPIO4|3    4|CB1_FIFO_TA11                       CB2_GPIO2|3    4|CB2_TIMER0 
     	  CB1_GPIO3|5    6|CB1_FIFOP_TA12                    CB2_SELECT2|5    6|CB2_TIMER1
          CB1_GPIO2|7    8|CB1_CCA_RCCLK                     CB2_SELECT1|7    8|CB2_INT1 
           CB_GPIO1|9   10|CB1_RESET                         CB2_SELECT0|9   10|CB2_RESET 
 CB1_UCAO(RXD/SOMI)|11  12|CB1_VREGEN_ACKL                CB2_RXD0/SOMI0|11  12|CB2_GPIO1 
 CB1_UCAO(TXD/SIMO)|13  14|CB1_ADC12CLK/DMAE0             CB2_TXD0/SIMO0|13  14|CB2_ADC 
                   |15  16|CB1_CSn_UCBOSTE/UCAOCLK          	 CB2_VCC|15  16|CB2_SCLK0/CS1 
                   |17  18|CB1_UCBO(SIMO/SDA)               	 CB2_GND|17  18|CB2_SIMO1/SDA1 
CB1_UCB0CLK/UCAOSTE|19  20|CB1_UCBO(SOMI/SCL)              CB2_CS0/SCLK1|19  20|CB2_SOMI1/SCL1 
                   +------+                          			        +------+

								 HIROSE
							   +---\/---+
			                GND|1	  27|HRXD0
					  VCCHIROSE|2	  28|HTXD0
						  HINT3|3     29|PW0
						  HINT2|4     30|PW0
					      HINT1|5     31|PW1
				    	  HINT0|6     32|PW2
							   |7     33|PW3
						   LED3|8     34|PW4
					       LED2|9     35|PW5
						   LED1|10    36|PW6
							   |11    37|ADC7
							   |12    38|ADC6
							   |13    39|ADC5
						    PW7|14    40|ADC4
						  HGPIO|15    41|
					      HSIMO|16    42|
						  HSOMI|17    43|
						  HSCLK|18    44|HGPIO1
						  HRXD1|19    45|THRU1
						  HTXD1|20    46|THRU2
						   HSCL|21    47|THRU3
						   HSDA|22    48|HGPIO2
					       PWM0|23    49|PWM2
						   PWM1|24    50|VCCHIROSE
							   |25    51|GND
							   |26    	|
							   +--------+



 }}} */

/* {{{ MoteIST++ board pins */

// CBC1
static const uint8_t CBC1_1 = 1;
static const uint8_t CBC1_2 = 2;
static const uint8_t CBC1_3 = 3;
static const uint8_t CBC1_4 = 4;
static const uint8_t CBC1_5 = 5;
static const uint8_t CBC1_6 = 6;
static const uint8_t CBC1_7 = 7;
static const uint8_t CBC1_8 = 8;
static const uint8_t CBC1_9 = 9;
static const uint8_t CBC1_10 = 10;
static const uint8_t CBC1_11 = 11;
static const uint8_t CBC1_12 = 12;
static const uint8_t CBC1_13 = 13;
static const uint8_t CBC1_14 = 14;
static const uint8_t CBC1_15 = 15;
//static const uint8_t CBC1_16 = VCC
//static const uint8_t CBC1_17 = GND
static const uint8_t CBC1_18 = 18;
static const uint8_t CBC1_19 = 19;
static const uint8_t CBC1_20 = 20;

// CBC2
static const uint8_t CBC2_1 = 21;
static const uint8_t CBC2_2 = 22;
static const uint8_t CBC2_3 = 23;
static const uint8_t CBC2_4 = 24;
static const uint8_t CBC2_5 = 25;
static const uint8_t CBC2_6 = 26;
static const uint8_t CBC2_7 = 27;
static const uint8_t CBC2_8 = 28;
static const uint8_t CBC2_9 = 29;
static const uint8_t CBC2_10 = 30;
static const uint8_t CBC2_11 = 31;
static const uint8_t CBC2_12 = 32;
static const uint8_t CBC2_13 = 33;
static const uint8_t CBC2_14 = 34;
static const uint8_t CBC2_15 = 35;
//static const uint8_t CBC2_16 = VCC
//static const uint8_t CBC2_17 = GND
static const uint8_t CBC2_18 = 38;
static const uint8_t CBC2_19 = 39;
static const uint8_t CBC2_20 = 40;

// Hirose
//static const uint8_t HRS_1 = GND
//static const uint8_t HRS_2 = VCC
static const uint8_t HRS_3 = 43;
static const uint8_t HRS_4 = 44;
static const uint8_t HRS_5 = 45;
static const uint8_t HRS_6 = 46;
//static const uint8_t HRS_7 = NOT_CONNECTED
static const uint8_t HRS_8 = 48;
static const uint8_t HRS_9 = 49;
static const uint8_t HRS_10 = 50;
//static const uint8_t HRS_11 = NOT_CONNECTED
//static const uint8_t HRS_12 = NOT_CONNECTED
//static const uint8_t HRS_13 = NOT_CONNECTED
static const uint8_t HRS_14 = 54;
static const uint8_t HRS_15 = 55;
static const uint8_t HRS_16 = 56;
static const uint8_t HRS_17 = 57;
static const uint8_t HRS_18 = 58;
static const uint8_t HRS_19 = 59;
static const uint8_t HRS_20 = 60;
static const uint8_t HRS_21 = 61;
static const uint8_t HRS_22 = 62;
static const uint8_t HRS_23 = 63;
static const uint8_t HRS_24 = 64;
//static const uint8_t HRS_25 = NOT_CONNECTED
//static const uint8_t HRS_26 = NOT_CONNECTED
static const uint8_t HRS_27 = 67;
static const uint8_t HRS_28 = 68;
static const uint8_t HRS_29 = 69;
static const uint8_t HRS_30 = 70;
static const uint8_t HRS_31 = 71;
static const uint8_t HRS_32 = 72;
static const uint8_t HRS_33 = 73;
static const uint8_t HRS_34 = 74;
static const uint8_t HRS_35 = 75;
static const uint8_t HRS_36 = 76;
static const uint8_t HRS_37 = 77;
static const uint8_t HRS_38 = 78;
static const uint8_t HRS_39 = 79;
//static const uint8_t HRS_40 = NOT_CONNECTED
//static const uint8_t HRS_41 = NOT_CONNECTED
//static const uint8_t HRS_42 = NOT_CONNECTED
//static const uint8_t HRS_43 = NOT_CONNECTED
static const uint8_t HRS_44 = 84;
static const uint8_t HRS_45 = 85;
static const uint8_t HRS_46 = 86;
static const uint8_t HRS_47 = 87;
static const uint8_t HRS_48 = 88;
static const uint8_t HRS_49 = 89;
//static const uint8_t HRS_50 = VCC
//static const uint8_t HRS_51 = GND

// }}}

// {{{ Variables for the Programmer
static const uint8_t LED1 = 50;  //HRS_10
static const uint8_t LED2 = 49;  //HRS_9
static const uint8_t LED3 = 48;  //HRS_8

// }}}

// {{{ Arduino main
#ifdef ARDUINO_MAIN

const uint16_t port_to_input[] = {
	NOT_A_PORT,
	(uint16_t) &P1IN,
	(uint16_t) &P2IN,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3IN,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4IN,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5IN,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6IN,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7IN,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8IN,
#endif
#ifdef __MSP430_HAS_PORT9_R__
	(uint16_t) &P9IN,
#endif
#ifdef __MSP430_HAS_PORT10_R__
	(uint16_t) &P10IN,
#endif
#ifdef __MSP430_HAS_PORT11_R__
	(uint16_t) &P11IN,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJIN,
#endif


};

const uint16_t port_to_output[] = {
	NOT_A_PORT,
	(uint16_t) &P1OUT,
	(uint16_t) &P2OUT,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3OUT,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4OUT,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5OUT,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6OUT,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7OUT,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8OUT,
#endif
#ifdef __MSP430_HAS_PORT9_R__
	(uint16_t) &P9OUT,
#endif
#ifdef __MSP430_HAS_PORT10_R__
	(uint16_t) &P10OUT,
#endif
#ifdef __MSP430_HAS_PORT11_R__
	(uint16_t) &P11OUT,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJOUT,
#endif
};

const uint16_t port_to_dir[] = {
	NOT_A_PORT,
	(uint16_t) &P1DIR,
	(uint16_t) &P2DIR,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3DIR,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4DIR,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5DIR,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6DIR,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7DIR,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8DIR,
#endif
#ifdef __MSP430_HAS_PORT9_R__
	(uint16_t) &P9DIR,
#endif
#ifdef __MSP430_HAS_PORT10_R__
	(uint16_t) &P10DIR,
#endif
#ifdef __MSP430_HAS_PORT11_R__
	(uint16_t) &P11DIR,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJDIR,
#endif
};

const uint16_t port_to_ren[] = {
	NOT_A_PORT,
	(uint16_t) &P1REN,
	(uint16_t) &P2REN,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3REN,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4REN,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5REN,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6REN,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7REN,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8REN,
#endif
#ifdef __MSP430_HAS_PORT9_R__
	(uint16_t) &P9REN,
#endif
#ifdef __MSP430_HAS_PORT10_R__
	(uint16_t) &P8REN,
#endif
#ifdef __MSP430_HAS_POR11_R__
	(uint16_t) &P11REN,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJREN,
#endif
};

const uint16_t port_to_sel0[] = {  /* put this PxSEL register under the group of PxSEL0 */
	NOT_A_PORT,
	(uint16_t) &P1SEL,
	(uint16_t) &P2SEL,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3SEL,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4SEL,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5SEL,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6SEL,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7SEL,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8SEL,
#endif
#ifdef __MSP430_HAS_PORT9_R__
	(uint16_t) &P9SEL,
#endif
#ifdef __MSP430_HAS_PORT10_R__
	(uint16_t) &P10SEL,
#endif
#ifdef __MSP430_HAS_PORT11_R__
	(uint16_t) &P11SEL,
#endif
//#ifdef __MSP430_HAS_PORTJ_R__
//	(uint16_t) &PJSEL,
//#endif
};


//const uint16_t port_to_pmap[] = {
//	NOT_A_PORT,	/* PMAP starts at port P1 */
//	NOT_A_PORT,
//	NOT_A_PORT,
//	NOT_A_PORT,
//	(uint16_t) &P4MAP0,
//	NOT_A_PORT,
//	NOT_A_PORT,
//	NOT_A_PORT,
//	NOT_A_PORT,
//};


const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /* dummy */
	NOT_ON_TIMER, /* 1 - CB1_GPIO5 (T0B2) */ /*CBC1*/
	T1A0, 		  /* 2 - CB1_SFD/TA10 */
	NOT_ON_TIMER, /* 3 - CB1_GPIO4 (T0B1) */
	T1A1, 		  /* 4 - CB1_FIFO_TA11 */
	NOT_ON_TIMER, /* 5 - CB1_GPIO3 (T0B0) */
	T1A2, 		  /* 6 - CB1_FIFOP/TA12 */
	NOT_ON_TIMER, /* 7 - CB1_GPIO2 */
	NOT_ON_TIMER, /* 8 - CB1_CCA_RCCLK */
	NOT_ON_TIMER, /* 9 - CB1_GPIO1 */
	NOT_ON_TIMER, /* 10 - CB1_RESET */
	NOT_ON_TIMER, /* 11 - CB1_UCA0(RXD0/SOMI0) */
	NOT_ON_TIMER, /* 12 - CB1_VREGEN_ACKL */
	NOT_ON_TIMER, /* 13 - CB1_UCA0(TXD0/SIMO0) */
	NOT_ON_TIMER, /* 14 - CB1_ADC12CLK/DMAE0 */
	NOT_ON_TIMER, /* 15 - CB1_VCC */
	NOT_ON_TIMER, /* 16 - CB1_CSn_UCBOSTE/UCAOCLK */
	NOT_ON_TIMER, /* 17 - CB1_GND */
	NOT_ON_TIMER, /* 18 - CB1_UCB0(SIMO1/SDA1) */
	NOT_ON_TIMER, /* 19 - CB1_CS0/SCLK1 */
	NOT_ON_TIMER, /* 20 - CB1_UCB0(SOMI1/SCL1) */ 
	NOT_ON_TIMER, /* 21 - CB2_RST_NMI_SBWTDOI */ /*CBC2*/
	NOT_ON_TIMER, /* 22 - CB2_BSLT (T0A0) */
	NOT_ON_TIMER, /* 23 - CB2_TCK */
	NOT_ON_TIMER, /* 24 - CB2_BSLR (T0A1) */
	NOT_ON_TIMER, /* 25 - CB2_GPIO3 */
	NOT_ON_TIMER, /* 26 - CB2_FIFOP_SMCLK */
	NOT_ON_TIMER, /* 27 - CB2_GPIO2 */
	NOT_ON_TIMER, /* 28 - CB2_CCA */
	NOT_ON_TIMER, /* 29 - CB2_GPIO1 */
	NOT_ON_TIMER, /* 30 - CB2_RESET */
	NOT_ON_TIMER, /* 31 - CB2_UCA3(RXD0/SOMI0) */
	NOT_ON_TIMER, /* 32 - CB2_VREGEN */
	NOT_ON_TIMER, /* 33 - CB2_UCA3(TXD0/SIMO0) */
	NOT_ON_TIMER, /* 34 - CB2_SMCLK */
	NOT_ON_TIMER, /* 35 - CB2_VCC */
	NOT_ON_TIMER, /* 36 - CB2_UCB3STE/UCA3CLK */
	NOT_ON_TIMER, /* 37 - CB2_GND */
	NOT_ON_TIMER, /* 38 - CB2_UCB3(SIMO1/SDA1) */
	NOT_ON_TIMER, /* 39 - CB2_UCB3CLK/UCA3STE */
	NOT_ON_TIMER, /* 40 - CB2_UCB3(SOMI1/SCL1) */ 
	NOT_ON_TIMER, /* 41 - GND */  /*HIROSE*/
	NOT_ON_TIMER, /* 42 - VCCHIROSE */
	NOT_ON_TIMER, /* 43 - HINT3 */
	T0A2, 		  /* 44 - HINT2 */ 
	T0A3, 		  /* 45 - HINT1 */
	T0A4, 		  /* 46 - HINT0 */
	NOT_ON_TIMER, /* 47 - NOT CONNECTED */
	T0B5, 		  /* 48 - LED3 (TOB5) */
	T0B6, 		  /* 49 - LED2 (T0B6) */
	NOT_ON_TIMER, /* 50 - LED1 */
	NOT_ON_TIMER, /* 51 - NOT CONNECTED */
	NOT_ON_TIMER, /* 52 - NOT CONNECTED */
	NOT_ON_TIMER, /* 53 - NOT CONNECTED */
	NOT_ON_TIMER, /* 54 - PW7 */
	NOT_ON_TIMER, /* 55 - HGPIO */
	NOT_ON_TIMER, /* 56 - HSIMO */
	NOT_ON_TIMER, /* 57 - HSOMI */
	NOT_ON_TIMER, /* 58 - HSCLK */
	NOT_ON_TIMER, /* 59 - HRXD1 */
	NOT_ON_TIMER, /* 60 - HTXD1 */
	NOT_ON_TIMER, /* 61 - HSCL */
	NOT_ON_TIMER, /* 62 - HSDA */
	T0B3, 		  /* 63 - PWM0 (T0B3) */
	T0B4, 		  /* 64 - PWM1 (T0B4) */
	NOT_ON_TIMER, /* 65 - NOT CONNECTED */
	NOT_ON_TIMER, /* 66 - NOT CONNECTED */
	NOT_ON_TIMER, /* 67 - HRXD0 */
	NOT_ON_TIMER, /* 68 - HTXD0 */
	T0A4, 		  /* 69 - PW0 (T0A4) */
	T0A3, 		  /* 70 - PW1 (T0A3) */
	T0A2, 		  /* 71 - PW2 (T0A2) */
	T0A1, 		  /* 72 - PW3 (T0A1) */
	T0A0, 		  /* 73 - PW4 (T0A0) */
	T1A2, 		  /* 74 - PW5 (T1A2) */
	NOT_ON_TIMER, /* 75 - PW6 */
	NOT_ON_TIMER, /* 76 - ADC7 */
	NOT_ON_TIMER, /* 77 - ADC6 */
	NOT_ON_TIMER, /* 78 - ADC5 */
	NOT_ON_TIMER, /* 79 - ADC4 */
	NOT_ON_TIMER, /* 80 - NOT CONNECTED */
	NOT_ON_TIMER, /* 81 - NOT CONNECTED */
	NOT_ON_TIMER, /* 82 - NOT CONNECTED */
	NOT_ON_TIMER, /* 83 - NOT CONNECTED */
	NOT_ON_TIMER, /* 84 - HGPIO1 */
	NOT_ON_TIMER, /* 85 - THRU1 */
	NOT_ON_TIMER, /* 86 - THRU2 */
	NOT_ON_TIMER, /* 87 - THRU3 */
	NOT_ON_TIMER, /* 88 - HGPIO2 */
	T1A0, 		  /* 89 - PWM2 (T1A0) */
	NOT_ON_TIMER, /* 90 - VCCHIROSE */
	NOT_ON_TIMER, /* 91 - GND */
};




const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN,   /* dummy */
	P4,   		 /* 1 */  /* CBC1 */
	P2,          /* 2 */  
	P4,          /* 3 */
	P2,          /* 4 */
	P4,          /* 5 */
	P2,          /* 6 */
	P2,          /* 7 */
	P2,          /* 8 */
	P3,          /* 9 */
	P2,          /* 10 */
	P3,          /* 11 */
	P2,          /* 12 */
	P3,          /* 13 */
	P2,          /* 14 */
	NOT_A_PIN,    /* 15 */
	P3,          /* 16 */
	NOT_A_PIN,   /* 17 */
	P3,          /* 18 */
	P3,          /* 19 */
	P3,          /* 20 */
	NOT_A_PIN,   /* 21 */  /* CBC2 */
	P1,          /* 22 */
	PJ,   		 /* 23 */
	P1,          /* 24 */
	P10,         /* 25 */
	P1,          /* 26 */
	P11,         /* 27 */
	P1,          /* 28 */
	P11,         /* 29 */
	P9,          /* 30 */
	P10,         /* 31 */
	P9,          /* 32 */
	P10,         /* 33 */
	P11,         /* 34 */
	NOT_A_PIN,   /* 35 */
	P10,         /* 36 */
	NOT_A_PIN,   /* 37 */
	P10,         /* 38 */
	P10,         /* 39 */
	P10,         /* 40 */
	NOT_A_PIN,   /* 1 */   /* HIROSE */
	NOT_A_PIN,   /* 2 */
	P1,          /* 3 */
	P1,          /* 4 */
	P1,          /* 5 */
	P1,          /* 6 */
	NOT_A_PIN,   /* 7 */
	P4,          /* 8 */
	P4,          /* 9 */
	P4,          /* 10 */
	NOT_A_PIN,   /* 11 */
	NOT_A_PIN,   /* 12 */
	NOT_A_PIN,   /* 13 */
	P5,          /* 14 */
	P9,          /* 15 */
	P9,          /* 16 */
	P9,          /* 17 */
	P9,          /* 18 */
	P5,          /* 19 */
	P5,          /* 20 */
	P5,          /* 21 */
	P3,          /* 22 */
	P4,          /* 23 */
	P4,          /* 24 */
	NOT_A_PIN,   /* 25 */
	NOT_A_PIN,   /* 26 */
	P9,          /* 27 */
	P9,          /* 28 */
	P8,          /* 29 */
	P8,          /* 30 */
	P8,          /* 31 */
	P8,          /* 32 */
	P8,          /* 33 */
	P7,          /* 34 */
	P7,          /* 35 */
	P7,          /* 36 */
	P7,          /* 37 */
	P7,          /* 38 */
	P7,          /* 39 */
	NOT_A_PIN,   /* 40 */
	NOT_A_PIN,   /* 41 */
	NOT_A_PIN,   /* 42 */
	NOT_A_PIN,   /* 43 */
	P10,         /* 44 */
	NOT_A_PIN,   /* 45 */
	NOT_A_PIN,   /* 46 */
	NOT_A_PIN,   /* 47 */
	P8,          /* 48 */
	P8,          /* 49 */
	NOT_A_PIN,   /* 50 */
	NOT_A_PIN,	 /* 51*/
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN, /* 0,  pin count starts at 1 */
	BV(2), 	   /* 1 P4.2 */  //CBC_1
	BV(1),     /* 2 P2.1 */
	BV(1),     /* 3 P4.1 */
	BV(2),     /* 4 P2.2 */
	BV(0),     /* 5 P4.0 */
	BV(3),     /* 6 P2.3 */
	BV(0),     /* 7 P2.0 */
	BV(4),     /* 8 P2.4 */
	BV(6),     /* 9 P3.6 */
	BV(5),     /* 10 P2.5 */
	BV(5),     /* 11 P3.5 */
	BV(6),     /* 12 P2.6 */
	BV(4),     /* 13 P3.4 */
	BV(7),     /* 14 P2.7 */
	NOT_A_PIN, /* 15 */
	BV(0),     /* 16 P3.0 */
	NOT_A_PIN, /* 17 */
	BV(1),     /* 18 P3.1 */
	BV(3),     /* 19 P3.3 */
	BV(2),     /* 20 P3.2 */
	NOT_A_PIN, /* 1 */      //CBC_2
	BV(1),     /* 2 P1.1 */
	BV(3),     /* 3 PJ.3 */
	BV(2),     /* 4 P1.2 */
	BV(7),     /* 5 P10.7 */
	BV(6),     /* 6 P1.6 */
	BV(0),     /* 7 P11.0 */
	BV(7),     /* 8 P1.7 */
	BV(1),     /* 9 P11.1 */
	BV(7),     /* 10 P9.7 */
	BV(5),     /* 11 P10.5 */
	BV(6),     /* 12 P9.6 */
	BV(4),     /* 13 P10.4 */
	BV(2),     /* 14 P11.2 */
	NOT_A_PIN, /* 15 */
	BV(0),     /* 16 P10.0 */
	NOT_A_PIN, /* 17 */
	BV(1),     /* 18 P10.1 */
	BV(3),     /* 19 P10.3 */
	BV(2),     /* 20 P10.2 */
	NOT_A_PIN, /* 1 */      //HIROSE
	NOT_A_PIN, /* 2 */
	BV(0),     /* 3 P1.0 */
	BV(3),     /* 4 P1.3 */
	BV(4),     /* 5 P1.4 */
	BV(5),     /* 6 P1.5 */
	NOT_A_PIN, /* 7 */
	BV(5),     /* 8 P4.5 */
	BV(6),     /* 9 P4.6 */
	BV(7),     /* 10 P4.7 */
	NOT_A_PIN, /* 11 */
	NOT_A_PIN, /* 12 */
	NOT_A_PIN, /* 13 */
	BV(5),     /* 14 P5.5 */
	BV(0),     /* 15 P9.0 */
	BV(1),     /* 16 P9.1 */
	BV(2),     /* 17 P9.2 */
	BV(3),     /* 18 P9.3 */
	BV(7),     /* 19 P5.7 */
	BV(6),     /* 20 P5.6 */
	BV(4),     /* 21 P5.4 */
	BV(7),     /* 22 P3.7 */
	BV(3),     /* 23 P4.3 */
	BV(4),     /* 24 P4.4 */
	NOT_A_PIN, /* 25 */
	NOT_A_PIN, /* 26 */
	BV(5),     /* 27 P9.5 */
	BV(4),     /* 28 P9.4 */
	BV(4),     /* 29 P8.4 */
	BV(3),     /* 30 P8.3 */
	BV(2),     /* 31 P8.2 */
	BV(1),     /* 32 P8.1 */
	BV(0),     /* 33 P8.0 */
	BV(3),     /* 34 P7.3 */
	BV(2),     /* 35 P7.2 */
	BV(7),     /* 36 P7.7 */
	BV(6),     /* 37 P7.6 */
	BV(5),     /* 38 P7.5 */
	BV(4),     /* 39 P7.4 */
	NOT_A_PIN, /* 40 */
	NOT_A_PIN, /* 41 */
	NOT_A_PIN, /* 42 */
	NOT_A_PIN, /* 43 */
	BV(6),     /* 44 P10.6 */
	NOT_A_PIN, /* 45 */
	NOT_A_PIN, /* 46 */
	NOT_A_PIN, /* 47 */
	BV(6),     /* 48 P8U.6 */
	BV(5),     /* 49 P8.5 */
	NOT_A_PIN, /* 50 */
	NOT_A_PIN, /* 51 */
};


const uint32_t digital_pin_to_analog_in[] = {
    NOT_ON_ADC,     /*  dummy   */
    NOT_ON_ADC,     /* 1 */ //CBC1
	NOT_ON_ADC,		/* 2 */
	NOT_ON_ADC,		/* 3 */
	NOT_ON_ADC,		/* 4 */
	NOT_ON_ADC,		/* 5 */
	NOT_ON_ADC,		/* 6 */
	NOT_ON_ADC,		/* 7 */
	NOT_ON_ADC,		/* 8 */
	NOT_ON_ADC,		/* 9 */
	NOT_ON_ADC,		/* 10 */
	NOT_ON_ADC,		/* 11 */
	NOT_ON_ADC,		/* 12 */
	NOT_ON_ADC,		/* 13 */
	0,				/* 14 ADC -> A0 */
	NOT_ON_ADC,		/* 15 */
	NOT_ON_ADC,		/* 16 */
	NOT_ON_ADC,		/* 17 */
	NOT_ON_ADC,		/* 18 */
	NOT_ON_ADC,		/* 19 */
	NOT_ON_ADC,		/* 20 */
    NOT_ON_ADC,     /* 1 */ //CBC2
	NOT_ON_ADC,		/* 2 */
	NOT_ON_ADC,		/* 3 */
	NOT_ON_ADC,		/* 4 */
	NOT_ON_ADC,		/* 5 */
	NOT_ON_ADC,		/* 6 */
	NOT_ON_ADC,		/* 7 */
	NOT_ON_ADC,		/* 8 */
	NOT_ON_ADC,		/* 9 */
	NOT_ON_ADC,		/* 10 */
	NOT_ON_ADC,		/* 11 */
	NOT_ON_ADC,		/* 12 */
	NOT_ON_ADC,		/* 13 */
	NOT_ON_ADC,	    /* 14 */
	NOT_ON_ADC,		/* 15 */
	NOT_ON_ADC,		/* 16 */
	NOT_ON_ADC,		/* 17 */
	NOT_ON_ADC,		/* 18 */
	NOT_ON_ADC,		/* 19 */
	NOT_ON_ADC,		/* 20 */
	NOT_ON_ADC,     /* 1 */ //HIROSE
	NOT_ON_ADC,		/* 2 */
	NOT_ON_ADC,		/* 3 */
	NOT_ON_ADC,		/* 4 */
	NOT_ON_ADC,		/* 5 */
	NOT_ON_ADC,		/* 6 */
	NOT_ON_ADC,		/* 7 */
	NOT_ON_ADC,		/* 8 */
	NOT_ON_ADC,		/* 9 */
	NOT_ON_ADC,		/* 10 */
	NOT_ON_ADC,		/* 11 */
	NOT_ON_ADC,		/* 12 */
	NOT_ON_ADC,		/* 13 */
	NOT_ON_ADC,		/* 14 */
	NOT_ON_ADC,		/* 15 */
	NOT_ON_ADC,		/* 16 */
	NOT_ON_ADC,		/* 17 */
	NOT_ON_ADC,		/* 18 */
	NOT_ON_ADC,		/* 19 */
	NOT_ON_ADC,		/* 20 */
	NOT_ON_ADC,		/* 21 */
	NOT_ON_ADC,		/* 22 */
	NOT_ON_ADC,		/* 23 */
	NOT_ON_ADC,		/* 24 */
	NOT_ON_ADC,		/* 25 */
	NOT_ON_ADC,		/* 26 */
	NOT_ON_ADC,		/* 27 */
	NOT_ON_ADC,		/* 28 */
	NOT_ON_ADC,		/* 29 */
	NOT_ON_ADC,		/* 30 */
	NOT_ON_ADC,		/* 31 */
	NOT_ON_ADC,		/* 32 */
	NOT_ON_ADC,		/* 33 */
	NOT_ON_ADC,		/* 34 */
	NOT_ON_ADC,		/* 35 */
	1,			 	/* 36 ADC7 -> A1 */
	2,				/* 37 ADC6 -> A2 */
	3,				/* 38 ADC5 -> A3 */
	4,				/* 39 ADC4 -> A4 */
	NOT_ON_ADC,		/* 40 */
	NOT_ON_ADC,		/* 41 */
	NOT_ON_ADC,		/* 42 */
	NOT_ON_ADC,		/* 43 */
	NOT_ON_ADC,		/* 44 */
	NOT_ON_ADC,		/* 45 */
	NOT_ON_ADC,		/* 46 */
	NOT_ON_ADC,		/* 47 */
	NOT_ON_ADC,		/* 48 */
	NOT_ON_ADC,		/* 49 */
	NOT_ON_ADC,		/* 50 */
	NOT_ON_ADC,		/* 51 */
};	

#endif // #ifdef ARDUINO_MAIN }}}

#endif // #ifndef Pins_Energia_h
