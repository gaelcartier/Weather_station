/*
 * TOUCHSCREEN.h
 *
 *  Created on: 29 mai 2022
 *      Author: gael
 */

#ifndef _TOUCHSCREEN_H_
#define _TOUCHSCREEN_H_

#include "../board.h"
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define TOUCHSCREEN_I2C_SDA_GPIO			4 // pin 6
#define TOUCHSCREEN_I2C_SCL_GPIO			5 // pin 7

#define TOUCHSCREEN_I2C_IRQ_GPIO			8 // pin 11

#define TOUCHSCREEN_I2C_ADDR				0x38
#define TOUCHSCREEN_I2C_INST				i2c0

#define TOUCHSCREEN_DEVICE_MODE				0x00
#define TOUCHSCREEN_WORKING_MODE			(0x0 | ( 0b000 << 4))

#define TOUCHSCREEN_CTRL					0x86
#define TOUCHSCREEN_STAY_ACTIVE				0x00
#define TOUCHSCREEN_SWITCH_ACTIVE_MONITOR	0x01

#define TOUCHSCREEN_GEST_ID					0x01

#define TOUCHSCREEN_X1_H					0x03
#define TOUCHSCREEN_X1_L					0x04
#define TOUCHSCREEN_Y1_H					0x05
#define TOUCHSCREEN_Y1_L					0x06
#define TOUCHSCREEN_WEIGHT1					0x07
#define TOUCHSCREEN_MISC1					0x08

#define TOUCHSCREEN_X2_H					0x08
#define TOUCHSCREEN_X2_L					0x0A
#define TOUCHSCREEN_Y2_H					0x0B
#define TOUCHSCREEN_Y2_L					0x0C
#define TOUCHSCREEN_WEIGHT2 				0x0D
#define TOUCHSCREEN_MISC2					0x0E

#define TOUCHSCREEN_INTERRUPT_MODE			0xA4
#define TOUCHSCREEN_INTERRUPT_TRIGGER		0x01
#define TOUCHSCREEN_INTERRUPT_POLLING		0x00

#define TOUCH_STAT_WAIT						0x0
#define TOUCH_STAT_INIT						0x1
#define TOUCH_STAT_READ						0x2

#define TOUCHSCREEN_MOVE_TRESHOLD			10
#define TOUCHSCREEN_LONG_TRESHOLD			400
#define TOUCHSCREEN_BUFFER_SIZE				1024


typedef enum {
	PRESS_DOWN = 0b00,
	LIFT_UP = 0b01,
	CONTACT = 0b10,
	NO_EVENT = 0b11
} touch_event_t;

typedef enum {
	POINT = 0x01,
	LONG_POINT = 0x02,
	MOVE_UP = 0x10,
	MOVE_DOWN = 0x18,
	MOVE_RIGHT = 0x14,
	MOVE_LEFT = 0x1C,
	ZOOM_IN = 0x48,
	ZOOM_OUT = 0x49,
	NO_GESTURE = 0x00
} gesture_t;

typedef struct {
	touch_event_t touch_event;
	uint16_t x;
	uint16_t y;
	uint32_t time;
} touchscreen_info_t;

typedef struct {
	gesture_t gesture;
	uint16_t x;
	uint16_t y;
	int16_t x_area;
	int16_t y_area;
	uint32_t duration;
	void (*handler)(void);
} touchscreen_action_t;

extern volatile int TOUCHED;

void touchscreen_i2c_config();
void touchscreen_config();
void touchscreen_init();
void touchscreen_irq_callback( uint8_t gpio, uint32_t events );
void touchscreen_enable_irq();
touchscreen_info_t touchscreen_read();

#endif 
