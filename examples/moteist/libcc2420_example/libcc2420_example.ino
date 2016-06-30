/*

    libcc2420_example
    A simple send-receive example loop

    In channel 26, with pan address 0x0022, broadcasts
    the value 0x3ff0 and checks for a received packet.

    If two boards are programmed with this example, they
    will transmit and receive from one another.

*/

#include <libcc2420.h>


void transmit_test_packet(int seq){

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

	cc2420_send(pkt, pkt_len); // send the actual packet

}

// Toggles leds value
void toogled(int led){

    int ledstate;

    // read led value
    ledstate = digitalRead(led);

    // toogle value
    if (ledstate == LOW)
        digitalWrite(led,HIGH);
    else
        digitalWrite(led,LOW);
}


// the setup routine runs once when you press reset:
void setup() {

	// Init the chip.
	// Channel = 26; Panaddr = 0x0022
	cc2420_init(26,0x0022);

    // init the led2 as output for debuging.
    pinMode (LED2, OUTPUT);

    // init the led3 as output for debuging.
    pinMode (LED3, OUTPUT);
}


// the loop routine runs over and over again forever:
void loop() {

	unsigned char seq_num = 0;
	char rxbuf[128]; // receive buffer
        int bytes_count;

	/*
	+-------+-----+
	| level | dbm |
	| 0     |  0  |
	| 1     | -1  |
	| 2     | -3  |
	| 3     | -5  |
	| 4     | -7  |
  	| 5     | -10 |
	| 6     | -25 |
	+-------+-----+ */
	cc2420_set_txpower(0); // max tx power.

	//transmission-reception cycle
	//when transmitting, LED2 toggles its state
	//when a packet is received, LED3 toggles its state
	while (1) {

        // wait for a second (1000 milliseconds)
        delay(1000);

        // transmit the test packet
        transmit_test_packet(seq_num++);
        toogled(LED2);

        // check for a received packet in cc2420 the internal buffer.
        // this function does *not* block.
	bytes_count = cc2420_recv(&rxbuf,128);

        // if received bytes > 0, then a message
        // was received. Blink led3.
        if (bytes_count > 0)
            toogled(LED3);

	}

}
