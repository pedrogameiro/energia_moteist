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
#include "Energia.h"

#define NETSTACK_CONF_RADIO   cc2420_driver

//#define MOTEIST1011
//#define MOTEIST0413

#define _BV(x) (1 << x)
#define BV(bitno) _BV(bitno)

/**
 * MCU controlled LEDS;
 */

#define LED_PORT(type)   P4##type
#define LED1_PIN ~BV(7)    // P4.7 (active Low)
#define LED2_PIN ~BV(6)    // P4.6 (active Low)
#define LED3_PIN ~BV(5)    // P4.5 (active Low)

/*
 * SPI bus - CC2420 pin configuration.
 */

#define CC2420_SIMO_PORT(type)   P10##type
#define CC2420_SIMO_PIN BV(1)    //P10.1

#define CC2420_SOMI_PORT(type)   P10##type
#define CC2420_SOMI_PIN BV(2)    //P10.2

#define CC2420_CLK_PORT(type)   P10##type
#define CC2420_CLK_PIN BV(3)     //P10.3

#define CC2420_FIFOP_PORT(type)   P1##type
#define CC2420_FIFOP_PIN          BV(6)

#define CC2420_FIFO_PORT(type)     P1##type
#define CC2420_FIFO_PIN            BV(2)

#define CC2420_SFD_PORT(type)   P1##type
#define CC2420_SFD_PIN BV(1)     // P1.1

#define CC2420_CCA_PORT(type)   P1##type
#define CC2420_CCA_PIN BV(7)     // P1.7

#ifdef MOTEIST1011
#define CC2420_RESET_PORT(type)   P9##type
#define CC2420_RESET_PIN BV(7)   // P9.7

#define CC2420_VREGEN_PORT(type)   P9##type
#define CC2420_VREGEN_PIN BV(6)  // P9.6
#endif
#ifdef MOTEIST0413
#define CC2420_RESET_PORT(type)   P9##type
#define CC2420_RESET_PIN BV(6)   // P9.6

#define CC2420_VREGEN_PORT(type)   P9##type // CBC2_GPIO1
#define CC2420_VREGEN_PIN BV(7)  // P9.6	// CBC2_GPIO1
#endif

///* - Output: SPI Chip Select (CS_N) */
#define CC2420_CS_PORT(type)      P10##type
#define CC2420_CS_PIN             BV(0)

#define P10_UNUSED_MASK 0xF0  //P3.4,5,6,7 Not used for cc2420 Comunication Board


///* Pin status. */
#define CC2420_FIFOP_IS_1 (!!(CC2420_FIFOP_PORT(IN) & CC2420_FIFOP_PIN))
#define CC2420_FIFO_IS_1  (!!(CC2420_FIFO_PORT(IN) & CC2420_FIFO_PIN))

/*
 * Enables/disables CC2420 access to the SPI bus (not the bus).
 * (Chip Select)
 */
#define CC2420_SPI_ENABLE() (CC2420_CS_PORT(OUT) &= ~CC2420_CS_PIN) /* ENABLE CSn (active low) */
#define CC2420_SPI_DISABLE() (CC2420_CS_PORT(OUT) |= CC2420_CS_PIN) /* DISABLE CSn (active low) */

#endif /* PLATFORM_CONF_H_ */
