#ifndef _STATION_H_
#define _STATION_H_

#include <stdio.h>
#include "pico/stdlib.h"


#include "../board.h"

#include "../lcd/lcd.h"
#include "../touchscreen/touchscreen.h"
#include "../bme280/bme280.h"
#include "../veml7700/veml7700.h"
#include "../led_rgb/led_rgb.h"
#include "../RN4870/RN4870.h"
#include "../weather_mode/weather_mode.h"

typedef enum {
    WEATHER_ALL_GRID,
    WEATHER_TEMP_NUM,
    WEATHER_HUM_NUM,
    WEATHER_PRESS_NUM,
    WEATHER_LIGHT_NUM,
    WEATHER_TEMP_GRAPH,
    WEATHER_HUM_GRAPH,
    WEATHER_PRESS_GRAPH,
    WEATHER_LIGHT_GRAPH,
} station_mode_t;

typedef struct {
    station_mode_t mode;
} station_state_t;

extern station_state_t station_state;

void station_reset();
void station_init();
void station_disable_ble();
void station_enable_ble();
void station_main();
void station_init_i2c_sensor();
void station_state_init();

#endif