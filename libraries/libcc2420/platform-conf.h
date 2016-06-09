/*
 * Copyright (c) 2010, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/**
 * \file
 *         A brief description of what this file is
 * \author
 *         Niclas Finne <nfi@sics.se>
 *         Joakim Eriksson <joakime@sics.se>
 */

#ifndef PLATFORM_CONF_H_
#define PLATFORM_CONF_H_

#include <msp430.h>


#define NETSTACK_CONF_RADIO   cc2420_driver


/*
 * SPI bus configuration for the TMote Sky.
 */

/* SPI input/output registers. */
#define SPI_TXBUF UCB3TXBUF
#define SPI_RXBUF UCB3RXBUF

#define _BV(x) (1 << x)
#define BV(bitno) _BV(bitno)

#define SPI_WAITFOREOTx() do { while (!(UCB3IFG & UCTXIFG)); } while (0)
#define SPI_WAITFOREORx() do { while (!(UCB3IFG & UCRXIFG)); } while (0)




/*
 * SPI bus - CC2420 pin configuration.
 */

#define CS_PIN BV(0) // Chip Select Low P10.0


///* - Input: FIFOP from CC2420 - ATMEGA128 PORT1, PIN6 */
#define CC2420_FIFOP_PORT(type)   P1##type
#define CC2420_FIFOP_PIN          6
///* - Input: FIFO from CC2420 - ATMEGA128 PORT1, PIN2 */
#define CC2420_FIFO_PORT(type)     P1##type
#define CC2420_FIFO_PIN            2

///* - Input: CCA from CC2420 - ATMEGA128 PORT1, PIN7 */
//#define CC2420_CCA_PORT(type)      P##type##1
//#define CC2420_CCA_PIN             7
///* - Input:  SFD from CC2420 - ATMEGA128 PORT1, PIN1 */
//#define CC2420_SFD_PORT(type)      P##type##1
//#define CC2420_SFD_PIN             1
///* - Output: SPI Chip Select (CS_N) - ATMEGA128 PORT10, PIN1 */
//#define CC2420_CS_PORT(type)      P##type##10
//#define CC2420_CS_PIN             1
///* - Output: VREG_EN to CC2420 - ATMEGA128 PORT9, PIN6 */
//#define CC2420_VREG_PORT(type)     P##type##9
//#define CC2420_VREG_PIN            6
///* - Output: RESET_N to CC2420 - ATMEGA128 PORT9, PIN7 */
//#define CC2420_RESET_PORT(type)    P##type##9
//#define CC2420_RESET_PIN           7
//
////#define CC2420_IRQ_VECTOR INT6_vect
//
///* Pin status. */
#define CC2420_FIFOP_IS_1 (!!(CC2420_FIFOP_PORT(IN) & BV(CC2420_FIFOP_PIN)))
#define CC2420_FIFO_IS_1  (!!(CC2420_FIFO_PORT(IN) & BV(CC2420_FIFO_PIN)))
//#define CC2420_CCA_IS_1   (!!(CC2420_CCA_PORT(IN) & BV(CC2420_CCA_PIN)))
//#define CC2420_SFD_IS_1   (!!(CC2420_SFD_PORT(IN) & BV(CC2420_SFD_PIN)))
//
///* The CC2420 reset pin. */
//#define SET_RESET_INACTIVE()   (CC2420_RESET_PORT(ORT) |=  BV(CC2420_RESET_PIN))
//#define SET_RESET_ACTIVE()     (CC2420_RESET_PORT(ORT) &= ~BV(CC2420_RESET_PIN))
//
///* CC2420 voltage regulator enable pin. */
//#define SET_VREG_ACTIVE()       (CC2420_VREG_PORT(ORT) |=  BV(CC2420_VREG_PIN))
//#define SET_VREG_INACTIVE()     (CC2420_VREG_PORT(ORT) &= ~BV(CC2420_VREG_PIN))
//
///* CC2420 rising edge trigger for external interrupt 6 (FIFOP).
// * Enable the external interrupt request for INT6.
// * See Atmega128 datasheet about EICRB Register
// */
//#define CC2420_FIFOP_INT_INIT() do {\
//  EICRB |= 0x30; \
//  CC2420_CLEAR_FIFOP_INT(); \
//} while (0)
//
///* FIFOP on external interrupt 6. */
//#define CC2420_ENABLE_FIFOP_INT()          do { EIMSK |= 0x40; } while (0)
//#define CC2420_DISABLE_FIFOP_INT()         do { EIMSK &= ~0x40; } while (0)
//#define CC2420_CLEAR_FIFOP_INT()           do { EIFR = 0x40; } while (0)

/*
 * Enables/disables CC2420 access to the SPI bus (not the bus).
 * (Chip Select)
 */
#define CC2420_SPI_ENABLE() (P10OUT &= ~CS_PIN) /* ENABLE CSn (active low) */
#define CC2420_SPI_DISABLE() (P10OUT |= CS_PIN) /* DISABLE CSn (active low) */


/**
 *
 *
 *
 */

#define LED1 ~BV(7)    // P4.7 (active Low)
#define LED2 ~BV(6)    // P4.6 (active Low)
#define LED3 ~BV(5)    // P4.5 (active Low)

#define SFD_PIN BV(1)     // P1.1
#define CCA_PIN BV(7)     // P1.7
#define RESET_PIN BV(7)   // P9.7
#define VREGEN_PIN BV(6)  // P9.6

#define SIMO_PIN BV(1)    //P10.1
#define SOMI_PIN BV(2)    //P10.2
#define CLK_PIN BV(3)     //P10.3

#define P10MASK 0xF0  //P3.4,5,6,7 Not used for cc2420 Comunication Board

#endif /* PLATFORM_CONF_H_ */
