#include "i2c_non_blocking.h"


void i2c_nb_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    in_i2c_irq = 1;
    switch (event) {
        case I2C_SLAVE_RECEIVE: // master has written some data
            i2c_ctx.data[ i2c_ctx.data_index ] = i2c_read_byte_raw( i2c );
            i2c_ctx.data_index ++;
            break;
        case I2C_SLAVE_REQUEST: // master is requesting data
            i2c_write_byte_raw(i2c, i2c_ctx.data[ i2c_ctx.data_index ]);
            i2c_ctx.data_index ++;
            break;
        case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
            i2c_ctx.status = 1;
            break;
        default:
            break;
    }
}

void i2c0_non_blocking_init( int speed, void* i2c_ctx_handler ) {
	gpio_set_function( I2C0_SCL_GPIO, GPIO_FUNC_I2C );
	gpio_set_function( I2C0_SDA_GPIO, GPIO_FUNC_I2C );
	i2c_init( i2c0, speed );
    i2c_slave_init(i2c0, I2C0_SLAVE_ADDRESS, i2c_ctx_handler);
}

void i2c1_non_blocking_init( int speed, void* i2c_ctx_handler ) {
	gpio_set_function( I2C1_SCL_GPIO, GPIO_FUNC_I2C );
	gpio_set_function( I2C1_SDA_GPIO, GPIO_FUNC_I2C );
	i2c_init( i2c1, speed );
    i2c_slave_init(i2c1, I2C1_SLAVE_ADDRESS, i2c_ctx_handler);
}

void i2c_non_blocking_init( i2c_inst_t *i2c, int speed, void* i2c_ctx_handler ){
    if( i2c == i2c0 ) i2c0_non_blocking_init( speed, i2c_ctx_handler );
    else if( i2c == i2c1 ) i2c1_non_blocking_init( speed, i2c_ctx_handler );
}

void i2c_request_data( i2c_inst_t* i2c, uint i2c_addr, uint i2c_target ) {
    uint8_t data[3] = { (i2c_addr | (I2C_WRITE << 7)), (i2c_target | (1 << I2C_IC_DATA_CMD_RESTART_LSB)), (i2c_addr | (I2C_READ << 7)) };
    for(int i=0; i<3; i++) i2c_write_byte_raw(i2c, data[i]);   
}