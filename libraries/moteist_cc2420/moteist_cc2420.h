// # vim: foldenable foldmethod=marker foldlevel=0 foldnestmax=10

#ifndef cc2420_h
#define cc2420_h

// {{{ License

// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 42):
// Pedro Gameiro wrote this file.  As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
// ----------------------------------------------------------------------------

// }}}

// {{{ Includes

#include "stdint.h"
#include "cc2420_const.h"

// }}}

#define CC2420_MAX_PACKET_LEN      127
#define CC2420_TXPOWER_MAX  31
#define CC2420_TXPOWER_MIN   0

typedef unsigned short rtimer_clock_t;

extern const struct radio_driver cc2420_driver;
/* XXX hack: these will be made as Chameleon packet attributes */
extern rtimer_clock_t cc2420_time_of_arrival, cc2420_time_of_departure;
extern int cc2420_authority_level_of_sender;
extern signed char cc2420_last_rssi;
extern uint8_t cc2420_last_correlation;
extern const struct aes_128_driver cc2420_aes_128_driver;


void cc2420_init();
void cc2420_set_channel(int channel);
int cc2420_get_channel(void);
void cc2420_set_pan(int panid);
int cc2420_recv(void);
int cc2420_send(const char *payload, unsigned short pkt_len);
void cc2420_init(void);
int example(int channel, int panid);



#endif // radio_h
