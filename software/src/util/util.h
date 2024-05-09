#ifndef _UTIL_H_
#define _UTIL_H_

#include "../board.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"

#include <string.h>

void gpio_initialize_out( uint gpio, bool state );
void gpio_initialize_in( uint gpio );
void stdin_read( char* buffer );

#endif
