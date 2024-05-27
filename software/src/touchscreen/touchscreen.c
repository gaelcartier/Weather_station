/*
 * touch_panel.c
 *
 *  Created on: 29 mai 2022
 *      Author: gael
 */

#include "touchscreen.h"

volatile int TOUCHED = false;
volatile touchscreen_status_t touchscreen_status;

static uint abs( int v ){
	return v < 0 ? -v : v;
}

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
	if( touchscreen_new_event() ){
		touchscreen_status.is_watching = true;
		touchscreen_status.duration = 0;
		touchscreen_status.read_initialized = false;
	}
}

void touchscreen_enable_irq() {
	gpio_set_irq_enabled_with_callback( TOUCHSCREEN_I2C_IRQ_GPIO, GPIO_IRQ_EDGE_RISE, true, &touchscreen_irq_callback );
}

void touchscreen_init() {
	touchscreen_status.duration = 0;
	touchscreen_status.is_watching = false;
	touchscreen_status.read_initialized = false;
	touchscreen_status.last_read_duration = 0;
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
	touch_info.y = ( (i2c_data[2] & 0xF) << 8 | i2c_data[3] );
	touch_info.x = TOUCHSCREEN_X - ( (i2c_data[4] & 0xF) << 8 | i2c_data[5] );

	return touch_info;
}

bool touchscreen_new_event(){
	return !touchscreen_status.is_watching && (touchscreen_status.duration > TOUCHSCREEN_DURATION_IS_NEW_EVENT);
}

void touchscreen_print_touch_event( touchscreen_info_t touch_info ){
	switch( touch_info.touch_event ){
		case CONTACT: printf("CONTACT");
			break;
		case PRESS_DOWN: printf("PRESS_DOWN");
			break;
		case LIFT_UP: printf("LIFT UP");
			break;
		case NO_EVENT: printf("NO_EVENT");
			break;
	}
}

touchscreen_action_t touchscreen_set_action_from_infos( touchscreen_info_t first, touchscreen_info_t last ){
	touchscreen_action_t a;
	a.x = first.x;
	a.y = first.y;
	a.x_area = last.x - first.x;
	a.y_area = last.y - first.y;
	a.duration = last.time - first.time;
	if( abs( a.x_area ) < TOUCHSCREEN_MOVE_TRESHOLD && abs( a.y_area ) < TOUCHSCREEN_MOVE_TRESHOLD ) {
		a.gesture = ( a.duration < TOUCHSCREEN_LONG_TRESHOLD ) ? POINT : LONG_POINT;
	}
	else {
		if( abs(a.x_area) > abs(a.y_area) ) a.gesture = ( a.x_area < 0 ) ? MOVE_LEFT : MOVE_RIGHT;
		else a.gesture = ( a.y_area < 0 ) ? MOVE_UP : MOVE_DOWN; 
	}
	return a;
}

void touchscreen_print_gesture( touchscreen_action_t a ){
	switch( a.gesture ){
		case POINT: printf("POINT");
			break;
		case LONG_POINT: printf("LONG_POINT");
			break;
		case MOVE_UP: printf("MOVE_UP");
			break;
		case MOVE_DOWN: printf("MOVE_DOWN");
			break;
		case MOVE_RIGHT: printf("MOVE_RIGHT");
			break;
		case MOVE_LEFT: printf("MOVE_LEFT");
			break;
		default: printf("OTHER");
	}
}
