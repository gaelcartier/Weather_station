/*
 * touch_panel.c
 *
 *  Created on: 29 mai 2022
 *      Author: gael
 */

#include "touchscreen.h"

volatile int TOUCHED = false;

void touchscreen_i2c_config() {
	i2c_init( TOUCHSCREEN_I2C_INST, 100*1000 );

	gpio_set_function( TOUCHSCREEN_I2C_SCL_GPIO, GPIO_FUNC_I2C );
	gpio_set_function(TOUCHSCREEN_I2C_SDA_GPIO, GPIO_FUNC_I2C );

	gpio_init( TOUCHSCREEN_I2C_IRQ_GPIO );
	gpio_set_dir( TOUCHSCREEN_I2C_IRQ_GPIO, GPIO_IN );
}

void touchscreen_config() {
	uint8_t touchscreen_on[2] = { ( TOUCHSCREEN_DEVICE_MODE | (1 << 7 ) ), TOUCHSCREEN_WORKING_MODE};
	i2c_write_blocking( TOUCHSCREEN_I2C_INST, TOUCHSCREEN_I2C_ADDR, touchscreen_on, 2, false );

	uint8_t touchscreen_ctrl[2] = { ( TOUCHSCREEN_CTRL | (1 << 7 ) ), TOUCHSCREEN_SWITCH_ACTIVE_MONITOR};
	i2c_write_blocking( TOUCHSCREEN_I2C_INST, TOUCHSCREEN_I2C_ADDR, touchscreen_ctrl, 2, false );

	uint8_t touchscreen_irq_mode[2] = { ( TOUCHSCREEN_INTERRUPT_MODE| (1 << 7 ) ), TOUCHSCREEN_INTERRUPT_TRIGGER };
	i2c_write_blocking( TOUCHSCREEN_I2C_INST, TOUCHSCREEN_I2C_ADDR, touchscreen_irq_mode, 2, false );
}

void touchscreen_irq_callback( uint8_t gpio, uint32_t events ) {
	printf("I'm in the touchscreen irq\n");
	TOUCHED = true;
}

void touchscreen_enable_irq() {
	gpio_set_irq_enabled_with_callback( TOUCHSCREEN_I2C_IRQ_GPIO, GPIO_IRQ_EDGE_RISE, true, &touchscreen_irq_callback );
}

void touchscreen_init() {
	touchscreen_i2c_config();
	touchscreen_config();
	touchscreen_enable_irq();
}

touchscreen_info_t touchscreen_read() {
	uint8_t i2c_data[8];
	uint8_t touchscreen_target = TOUCHSCREEN_GEST_ID;
	i2c_write_blocking( TOUCHSCREEN_I2C_INST, TOUCHSCREEN_I2C_ADDR, &touchscreen_target, 1, true); 
	i2c_read_blocking( TOUCHSCREEN_I2C_INST, TOUCHSCREEN_I2C_ADDR, i2c_data, 6, false );

	touchscreen_info_t touch_info;
	touch_info.touch_event = i2c_data[2] >> 6;
	touch_info.time = 0;
	touch_info.x = TOUCHSCREEN_X - ( (i2c_data[2] & 0xF) << 8 | i2c_data[3] );
	touch_info.y = TOUCHSCREEN_Y - ( (i2c_data[4] & 0xF) << 8 | i2c_data[5] );

	return touch_info;
}
