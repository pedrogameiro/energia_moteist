// # vim: foldenable foldmethod=marker foldlevel=0 foldnestmax=10

#ifndef radio_h
#define radio_h

// {{{ License

// ----------------------------------------------------------------------------
// "THE BEER-WARE LICENSE" (Revision 42):
// Pedro Gameiro wrote this file.  As long as you retain this notice you
// can do whatever you want with this stuff. If we meet some day, and you think
// this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
// ----------------------------------------------------------------------------

// }}}

// {{{ Includes

#include "Energia.h"

// }}}

class Radio
{
  public:
    Radio();
    void transmit_test_packet(char numero);
    void change_frequency_channel(int channel);
    void toggle_pin(uint8_t pin);
  private:
    char receive_buffer[128];
    char send_buffer[128];
    char statusByte;
    void activate_switches(void);
    void software_delay(void);
    void CS_down(void);
    void CS_up(void);
    void send_command_CC2420(unsigned int n);
    void commandStrobe(char strobe);
};

#endif // radio_h
