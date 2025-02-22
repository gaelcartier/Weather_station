/*
 * TOUCHSCREEN.h
 *
 *  Created on: 29 mai 2022
 *      Author: gael
 */

#ifndef _TOUCHSCREEN_H_
#define _TOUCHSCREEN_H_

#include <stdint.h>
#include <stdio.h>

#include "../board.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define TOUCHSCREEN_I2C_SDA_GPIO 4  // pin 6
#define TOUCHSCREEN_I2C_SCL_GPIO 5  // pin 7

#define TOUCHSCREEN_I2C_IRQ_GPIO 8  // pin 11

#define TOUCHSCREEN_I2C_ADDR 0x38
#define TOUCHSCREEN_I2C_INST i2c0

#define TOUCHSCREEN_DEVICE_MODE 0x00
#define TOUCHSCREEN_WORKING_MODE (0x0 | (0b000 << 4))

#define TOUCHSCREEN_CTRL 0x86
#define TOUCHSCREEN_STAY_ACTIVE 0x00
#define TOUCHSCREEN_SWITCH_ACTIVE_MONITOR 0x01

#define TOUCHSCREEN_GEST_ID 0x01

#define TOUCHSCREEN_X1_H 0x03
#define TOUCHSCREEN_X1_L 0x04
#define TOUCHSCREEN_Y1_H 0x05
#define TOUCHSCREEN_Y1_L 0x06
#define TOUCHSCREEN_WEIGHT1 0x07
#define TOUCHSCREEN_MISC1 0x08

#define TOUCHSCREEN_X2_H 0x08
#define TOUCHSCREEN_X2_L 0x0A
#define TOUCHSCREEN_Y2_H 0x0B
#define TOUCHSCREEN_Y2_L 0x0C
#define TOUCHSCREEN_WEIGHT2 0x0D
#define TOUCHSCREEN_MISC2 0x0E

#define TOUCHSCREEN_INTERRUPT_MODE 0xA4
#define TOUCHSCREEN_INTERRUPT_TRIGGER 0x01
#define TOUCHSCREEN_INTERRUPT_POLLING 0x00

#define TOUCH_STAT_WAIT 0x0
#define TOUCH_STAT_INIT 0x1
#define TOUCH_STAT_READ 0x2

#define TOUCHSCREEN_DURATION_IS_NEW_EVENT 100
#define TOUCHSCREEN_MOVE_TRESHOLD 10
#define TOUCHSCREEN_LONG_TRESHOLD 400

#define TOUCHSCREEN_BUFFER_SIZE 1024

#define TOUCHSCREEN_X 320
#define TOUCHSCREEN_Y 240

#define GESTURE_MODE true
#define SIMPLE_TOUCH_MODE false

typedef bool touchscreen_mode_t;

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

typedef struct {
    // bool touched;
    bool is_watching;
    touchscreen_mode_t mode;
    uint32_t duration;
    uint32_t last_read_duration;
    bool read_initialized;
    touchscreen_info_t first_touch;
    // touchscreen_action_t action;
} touchscreen_status_t;

extern volatile int TOUCHED;
extern volatile touchscreen_status_t touchscreen_status;

void touchscreen_i2c_config();
void touchscreen_config();
void touchscreen_init();
void touchscreen_irq_callback(uint8_t gpio, uint32_t events);
void touchscreen_enable_irq();
bool touchscreen_new_event();
void touchscreen_status_reset_watching();
touchscreen_info_t touchscreen_info_init();
touchscreen_info_t touchscreen_read();
void touchscreen_print_touch_event(touchscreen_info_t touch_info);
touchscreen_action_t touchscreen_set_action_from_infos(touchscreen_info_t first,
                                                       touchscreen_info_t last);
void touchscreen_print_gesture(touchscreen_action_t a);
void touchscreen_handler_in_gesture_mode(
    void (*gesture_handler)(touchscreen_action_t));
touchscreen_info_t touchscreen_handler_in_simple_touch_mode();
bool touchscreen_in_gesture_mode();
bool touchscreen_in_simple_touch_mode();
void touchscreen_switch_to_simple_touch_mode();
void touchscreen_switch_to_gesture_mode();

#endif
