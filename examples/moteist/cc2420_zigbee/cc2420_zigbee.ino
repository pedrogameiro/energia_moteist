
#include <moteist_cc2420.h>

// the setup routine runs once when you press reset:
void setup() {
	cc2420_init(26,0x0022);
}



// the loop routine runs over and over again forever:
void loop() {

    // Blocks inside
    example();

}
