/*
*/

#include <libcc2420.h>

// the setup routine runs once when you press reset:
void setup() {

	// Init the chip.
	// Channel = 26; Panaddr = 0x0022
	cc2420_init(26,0x0022);
}

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

	cc2420_send(pkt, pkt_len);

}


// the loop routine runs over and over again forever:
void loop() {

	unsigned char seq_num = 0;
	char rxbuf[128];

	/*
	+-------+-----+
	| level | dbm |
	| 0     | 0   |
	| 1     | -1  |
	| 2     | -3  |
	| 3     | -5  |
	| 4     | -7  |
	| 5     | -10 |
	| 15    | -25 |
	+-------+-----+ */
	cc2420_set_txpower(0);

	//transmission-reception cycle
	//when transmitting, LED2 toggles its state
	//when a packet is received, LED3 toggles its state
	while (1) {

		delay(1000);

		transmit_test_packet(seq_num++);
		cc2420_recv(&rxbuf,128);

	}

}
