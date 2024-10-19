#ifndef _BUFFER_LOOP_
#define _BUFFER_LOOP_


#include "../board.h"
#include "../lcd/lcd.h"
#include "../font/font.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/timer.h"

#include <string.h>

typedef struct _buffer_loop_t {
    uint16_t write_index;
    uint16_t read_index;
	uint16_t buffer_size;
	uint8_t element_size;
	void* buffer;
} buffer_loop_t;


void buffer_loop_init(buffer_loop_t *b, void* buffer, uint8_t element_size, uint16_t buffer_size);
bool buffer_loop_is_empty(buffer_loop_t b);
void buffer_loop_write_index_up(buffer_loop_t* b);
void buffer_loop_read_index_up(buffer_loop_t* b);
bool buffer_loop_is_full(buffer_loop_t b);
void buffer_loop_push(buffer_loop_t* b, void* v);
void buffer_loop_pop(buffer_loop_t* b, void* dest);
int buffer_loop_element_count( buffer_loop_t b );
void buffer_loop_clear(buffer_loop_t* b);

#endif