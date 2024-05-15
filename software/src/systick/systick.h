#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "hardware/structs/systick.h"
#include <stdio.h>
#include "pico/stdlib.h"

// uint systick_counter;

extern void isr_systick();
void systick_init( uint32_t reload_value );

#endif