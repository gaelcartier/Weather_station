#include "systick.h"

// extern void isr_systick() {
//     systick_counter ++;
// }

void systick_init( uint32_t reload_value ){
    // systick_counter = 0;
    systick_hw->rvr = reload_value; // /!\ only last 24 bits will be used

    systick_hw->cvr = 0; // Force to clear the systick counter value;

    systick_hw->csr |= ( 1 << 2 ); // Set the systick clock source as processor clock (default = 0 = External reference clock)
    systick_hw->csr |= ( 1 << 1 ); // Enable systick interrupt isr_systick()
    systick_hw->csr |= ( 1 << 0 ); // Enable systick counter
}