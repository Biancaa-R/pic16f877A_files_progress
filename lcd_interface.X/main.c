#include <xc.h>
#include "clcd_inter.h"

void main() {
    init_clcd();         // Initialize LCD
    clcd_print("Biancaa", 0x80); // Print "Hello" on Line 1
    clcd_print_right_to_left("Biancaa",0xCF);

    while (1) {
        // Keep running indefinitely
    }
}

