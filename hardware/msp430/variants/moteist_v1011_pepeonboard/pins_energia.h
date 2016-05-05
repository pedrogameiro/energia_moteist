/*
  ************************************************************************
  *	pins_energia.h
  *
  *	Energia core files for MSP430F5438 MoteIST++ w pepeonboard 
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
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
*/



// --------------------PEPE------------------------//


#ifndef Pins_Energia_h
#define Pins_Energia_h
#ifndef BV
#define BV(x) (1 << (x))
#endif

#if defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__)
////constantes para o protocolo SPI		Porto / PEPE Label
//static const uint8_t SS      = 16;  /*  P3.0  / CB1_SCLKO/CS1  */
static const uint8_t SCK     = 19;  /*  P3.3  / CB1_CSO/SCLK1  */
static const uint8_t MOSI    = 18;  /*  P3.1  / CB1_SIMO1/SDA1 aka SIMO  */
static const uint8_t MISO    = 20;  /*  P3.2  / CB1_SOMI1/SCL1 aka SOMI  */
//
////constantes para protocolo I2C
static const uint8_t TWISDA  = 18;  /*  P10.1 / CB2_SIMO1/SDA1 */ /*provavel troca de valor*/
static const uint8_t TWISCL  = 20;  /*  P10.2 / CB2_SOMI1/SCL1 */ /*provavel troca de valor*/
//
//										  /* Porto / PEPE Label */
static const uint8_t DEBUG_UARTRXD = 31;  /* P3.5  / CB1_UCA0(RXD/SOMI) */
static const uint8_t DEBUG_UARTTXD = 33;  /* P3.4  / CB1_UCA0(TXD/SIMO) */
//static const uint8_t AUX_UARTRXD = 11;    /* P10.5 / CB2_UCA3(RXD/SOMI) */ /*provavel troca de valor*/
//static const uint8_t AUX_UARTTXD = 13;	  /* P10.4 / CB2_UCA3(TXD/SIMO) */ /*provavel troca de valor*/
#define TWISDA_SET_MODE (PORT_SELECTION0)
#define TWISCL_SET_MODE (PORT_SELECTION0)
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1 | OUTPUT)
//#define AUX_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
//#define AUX_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define SPISCK_SET_MODE (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
#endif
//
#define DEBUG_UART_MODULE_OFFSET 0x40
//#define AUX_UART_MODULE_OFFSET 0x0
//#define SERIAL1_AVAILABLE 1
//
//#if defined(__MSP430_HAS_USCI_A1__)
//#define USE_USCI_A1
//#endif

/* Pinos analogicos para o pepe */

static const uint8_t A0  = 14 ; /* CBC1: GPIO12    */
static const uint8_t A1  = 34;/* CBC2: GPIO12    */



/*
 Conectores ligados ao pepeonboard  pin mapping

								       CBC1            						  CBC2
							          +--\/--+                                 +--\/--+
                        GPIO 1 (LED1 )|1    2|GPIO 6 (SWITCH2 )            RST |1    2|INT0
                        GPIO2 (LED 2 )|3    4|GPIO 7 (SWITCH3)            GPIO2|3    4|TIMER0
     	      			          SEL2|5    6|TIMER1                       SEL2|5    6|TIMER1                          
     					          SEL1|7    8|INT1                         SEL1|7    8|INT1 
                                  SEL0|9   10|RESET                        SEL0|9   10|RESET
                                   RX |11  12|GPIO 1                         RX|11  12|GPIO 1
                                   TX |13  14|ADC                            TX|13  14|ADC 
                                  VCC |15  16|CS1                           VCC|15  16|CS1
                                   GND|17  18|SIMO                         GND |17  18|SIMO
                                   CS0|19  20|SOMI                         CS0 |19  20|SOMI
                                      +------+                                 +------+

													
*/

/* Pinos baseados no pepeonboard */

//
static const uint8_t CBC1_1=1; /*  GPIO1(LED1)    */
static const uint8_t CBC1_2=2;/*  GPIO6(SWITCH2)    */
static const uint8_t CBC1_3=3;/*  GPIO2(LED2)    */
static const uint8_t CBC1_4=4;/*  GPIO7(SWITCH3)    */
static const uint8_t CBC1_5=5;/*  GPIO3(LED3)    */
static const uint8_t CBC1_6=6;/*  GPIO8(SWITCH4)    */
static const uint8_t CBC1_7=7;/*  GPIO4(LED4)    */
static const uint8_t CBC1_8=8;/*  GPIO9( 7 SEGMENT DISPLAY)    */
static const uint8_t CBC1_9=9;/*  GPIO5(SWITCH 1)    */
static const uint8_t CBC1_10=10;/*  GPIO10(SPEAKER)    */
static const uint8_t CBC1_11=11;/*  TX2    */
static const uint8_t CBC1_12=12;/*  GPIO11    */
static const uint8_t CBC1_13=13;/*  RX2    */
static const uint8_t CBC1_14=14;/*  GPIO12    */
//static const uint8_t CBC1_15=15;  NOT CONNECTED  
static const uint8_t CBC1_16=16;/*  GPIO13    */
//static const uint8_t CBC1_17=17;/*  GND    */
static const uint8_t CBC1_18=18;/*  SPI- MOSI    */
static const uint8_t CBC1_19=19;/*  SPI-CLK    */
static const uint8_t CBC1_20=20;/*  SPI-MISO    */

static const uint8_t CBC2_1=21;/* RESET    */
static const uint8_t CBC2_2=22;/*  GPIO18    */
static const uint8_t CBC2_3=23;/*  RTS1   */
static const uint8_t CBC2_4=24;/*  GPIO19    */
static const uint8_t CBC2_5=25;/*  GPIO14    */
static const uint8_t CBC2_6=26;/*  GPIO20    */
static const uint8_t CBC2_7=27;/*  GPIO15    */
static const uint8_t CBC2_8=28;/*  GPIO21    */
static const uint8_t CBC2_9=29;/*  GPIO16    */
static const uint8_t CBC2_10=30;/*  GPIO22    */
static const uint8_t CBC2_11=31;/*  TX1   */
static const uint8_t CBC2_12=32;/*  GPIO23    */
static const uint8_t CBC2_13=33;/*  RX1    */
static const uint8_t CBC2_14=34;/* GPIO24    */
//static const uint8_t CBC2_15=35;/*  3.3V    */
static const uint8_t CBC2_16=36;/*  GPIO25    */
//static const uint8_t CBC2_17=37;/*  GND   */
static const uint8_t CBC2_18=38;/*  I2C-SDA   */
static const uint8_t CBC2_19=39;/*  GPIO17    */
static const uint8_t CBC2_20=40;/* I2C-SCL    */


// Simbolos para o PEPE

//LEDS
static const uint8_t LED1=1;  
static const uint8_t LED2=3;
static const uint8_t LED3=5;
static const uint8_t LED4=7;

//SWITCH
static const uint8_t SWITCH1=9;//INTERRUPTOR 1
static const uint8_t SWITCH2=2;//INTERRUPTOR 2
static const uint8_t SWITCH3=4;//PUSH BUTTON 3
static const uint8_t SWITCH4=6;//PUSH BUTTON 4


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
/* #ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJIN,
#endif */

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
/* #ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJOUT,
#endif */
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
/* #ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJDIR,
#endif */
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
/* #ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJREN,
#endif */
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
/* #ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJSEL,
#endif */
};


/* const uint16_t port_to_pmap[] = { */
	/* NOT_A_PORT,	 *//* PMAP starts at port P1 */
/* 	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &P4MAP0,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
}; */


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
	
};

	

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN,        /* dummy */
	P4,               /* 1 CBC1_1 */
	P2,               /* 2 CBC1_2 */
	P4,              /* 3  CBC1_3*/
	P2,              /* 4 CBC1_4 */
	P4,             /* 5  CBC1_5*/
	P2,              /* 6  CBC1_6*/
	P2,            /* 7 CBC1_7 */
	P2,           /* 8 CBC1_8*/
	P3,           /* 9 CBC1_9*/
	P2,           /* 10 CBC1_10 */
	P3,          /* 11 CBC1_11*/
	P2,          /* 12 CBC1_12*/
	P3,          /* 13 CBC1_13*/
	P2,          /* 14 CBC1_14*/
	NOT_A_PIN,   /* 15 CBC1_15*/
	P3,          /* 16 CBC1_16*/
	NOT_A_PIN,   /* 17 CBC1_17*/
	P3,          /* 18 CBC1_18*/
	P3,          /* 19 CBC1_19*/
	P3,         /* 20 CBC1_20*/
	NOT_A_PIN,  /* 21 CBC2_1*/
	P1,           /* 22 CBC2_2*/
	PJ,           /* 23 CBC2_3*/
	P1,          /* 24 CBC2_4*/
	P10,         /* 25 CBC2_5*/
	P1,         /* 26 CBC2_6*/
	P11 ,       /* 27 CBC2_7*/
	P1,         /* 28 CBC2_8*/
	P11,        /* 29 CBC2_9*/
	P9,         /* 30 CBC2_10*/
	P10,        /* 31 CBC2_11*/
	P9,         /* 32 CBC2_12*/
	P10,         /* 33CBC2_13 */
	P11,         /* 34 CBC2_14*/
	NOT_A_PIN,   /* 35 CBC2_15*/
	P10,        /* 36 CBC2_16*/
	NOT_A_PIN,  /* 37 CBC2_17*/
	P10,       /* 38 CBC2_18*/
	P10,      /* 39 CBC2_19*/
	P10,      /* 40 CBC2_20*/
};

//PEPE  mascara consoante o porto

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN, /* 0,  pin count starts at 1 */     
	BV(2), /* 1  P4.2 */ 
	BV(1),     /* 2 P2.1 */
	BV(1),     /*3 P4.1 */
	BV(2),     /* 4 P2.2*/
	BV(0),     /* 5 P4.0 */
	BV(3),     /* 6 P2.3 */
	BV(0),     /* 7 P2.0 */
	BV(4),     /* 8 P2.4 */
	BV(6),     /* 9 P3.6*/
	BV(5),     /* 10 P2.5 */
	BV(5),     /* 11 P3.5 */
	BV(6),     /* 12 P2.6 */
	BV(4),     /* 13 P3.4 */ 
	BV(7),     /* 14 P2.7 */
	NOT_A_PIN, /* 15 NOT A PIN */
	BV(0),      /* 16 P3.0 */
	NOT_A_PIN,     /*17  NOT A PIN */
	BV(1),      /* 18 P3.1 */
	BV(3),      /* 19 P3.3 */
	BV(2),      /* 20 P3.2 */
	NOT_A_PIN,  /* 21 NOT A PIN*/
	BV(1),      /* 22 P1.1 */
	BV(3),     /* 23  PJ.3 */
	BV(2),     /* 24 P1.2 */
	BV(7),     /* 25 P10.7 */
	BV(6),     /* 26 P1.6 */
	BV(0),     /* 27 P11.0 */
	BV(7),     /* 28 P1.7 */
	BV(1),     /* 29 P11.1*/
	BV(7),     /* 30 P9.7*/
	BV(5),     /* 31 P10.5 */
	BV(6),     /* 32 P9.6 */
	BV(4),     /* 33 P10.4 */
	BV(2),     /* 34 P11.2 */
	NOT_A_PIN,   /* 35 3.3V */
	BV(0),     /* 36 P10.0 */
	NOT_A_PIN,     /* 37 GND */
	BV(1),     /* 38 P10.1*/
	BV(3),     /* 39 P10.3 */
	BV(2),     /* 40 P10.2 */ //
	
	
	
};


// DUVIDA NESTE VER SO ESTE 


const uint32_t digital_pin_to_analog_in[] = {
      	
	NOT_ON_ADC, /* dummy */
	NOT_ON_ADC, /* 1 - CB1_RST_NMI_SBWTDOI */
	NOT_ON_ADC, /* 2 - CB1_INT0 */
	NOT_ON_ADC, /* 3 - CB1_GPIO2 */
	NOT_ON_ADC, /* 4 - CB1_TIMER0 */
	NOT_ON_ADC, /* 5 - CB1_SELECT2 */
	NOT_ON_ADC, /* 6 - CB1_TIMER1 */
	NOT_ON_ADC, /* 7 - CB1_SELECT1 */
	NOT_ON_ADC, /* 8 - CB1_INT1 */
	NOT_ON_ADC, /* 9 - CB_SELECT0 */
	NOT_ON_ADC, /* 10 - CB1_RESET */
	NOT_ON_ADC, /* 11 - CB1_RXD0/SOMI0 */
	NOT_ON_ADC, /* 12 - CB1_GPIO1 */
	NOT_ON_ADC, /* 13 - CB1_TXD0/SIMO0 */
	0,            /* 14 - CB1_ADC */ //A0
	NOT_ON_ADC, /* 15 -  CB1_VCC */
	NOT_ON_ADC, /* 16 - CB1_SCLK0/CS1 */
	NOT_ON_ADC, /* 17 - CB1_GND */
	NOT_ON_ADC, /* 18 - CB1_SIMO1/SDA1 */
	NOT_ON_ADC, /* 19 - CB1_CS0/SCLK1 */
	NOT_ON_ADC, /* 20 - CB1_SOMI1/SCL1 */
	NOT_ON_ADC, /* 21 - CB2_RST_NMI_SBWTDOI */
	NOT_ON_ADC, /* 22 - CB2_INT0 */
	NOT_ON_ADC, /* 23 - CB2_GPIO2 */
	NOT_ON_ADC, /* 24 - CB2_TIMER0 */
	NOT_ON_ADC, /* 25 - CB2_SELECT2 */
	NOT_ON_ADC, /* 26 - CB2_TIMER1 */ //DUVIDA
	NOT_ON_ADC, /* 27 - CB2_SELECT1 */
	NOT_ON_ADC, /* 28 - CB2_INT1 */
	NOT_ON_ADC, /* 29 - CB2_SELECT0 */
	NOT_ON_ADC, /* 30 - CB2_RESET */
	NOT_ON_ADC, /* 31 - CB2_RXD0/SOMI0 */
	NOT_ON_ADC, /* 32 - CB2_GPIO1 */
	NOT_ON_ADC, /* 33 - CB2_TXD0/SIMO0 */
	NOT_ON_ADC ,          /* 34 - CB2_ADC */ //A1  
	NOT_ON_ADC, /* 35 - CB2_VCC */
	NOT_ON_ADC, /* 36 - CB2_SCLK0/CS1 */
	NOT_ON_ADC, /* 37 - CB2_GND */
	NOT_ON_ADC, /* 38 - CB2_SIMO1/SDA1*/
	NOT_ON_ADC, /* 39 - CS0/SCLK1 */
	NOT_ON_ADC, /* 40 - SOMI1/SCL1 */
	
	
};

#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
