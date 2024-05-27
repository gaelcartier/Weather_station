#ifndef __I2C_NON_BLOCKING__
#define __I2C_NON_BLOCKING__

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/i2c_slave.h"
#include "hardware/i2c.h"


#define I2C0_SDA_GPIO			4 // pin 6
#define I2C0_SCL_GPIO			5 // pin 7

#define I2C1_SCL_GPIO		    19 // pin 30
#define I2C1_SDA_GPIO		    18 // pin 29

#define I2C0_SLAVE_ADDRESS      42 
#define I2C1_SLAVE_ADDRESS      43

#define I2C_WRITE               0x0
#define I2C_READ                0x1

#define I2C_CTX_DATA_BUFFER_SIZE        32

 
typedef struct _i2c_context_t {
    uint8_t periph_addr;
    uint8_t data[I2C_CTX_DATA_BUFFER_SIZE];
    uint8_t data_index;
    uint8_t data_write_len;
    uint8_t data_read_len;
    uint8_t status;
    void *handler;
} i2c_context_t;


// i2c_context_t i2c0_ctx;
// i2c_context_t i2c1_ctx;

static i2c_context_t i2c_ctx;
static uint in_i2c_irq;

void i2c_nb_handler(i2c_inst_t *i2c, i2c_slave_event_t event);
void i2c0_non_blocking_init( int speed, void* i2c_ctx_handler );
void i2c1_non_blocking_init( int speed, void* i2c_ctx_handler );
void i2c_non_blocking_init( i2c_inst_t *i2c, int speed, void* i2c_ctx_handler );
void i2c_request_data( i2c_inst_t* i2c, uint i2c_addr, uint i2c_target );

#endif