#ifndef _STATION_H_
#define _STATION_H_

#include <stdio.h>
#include "pico/stdlib.h"


#include "../board.h"

#include "../lcd/lcd.h"
#include "../display/display.h"
#include "../touchscreen/touchscreen.h"
#include "../bme280/bme280.h"
#include "../veml7700/veml7700.h"
#include "../led_rgb/led_rgb.h"
#include "../RN4870/RN4870.h"
#include "../weather_mode/weather_mode.h"
#include "../wellcome_mode/wellcome_mode.h"
#include "../systick/systick.h"

#define STATION_MATRIX_NUMBER_IN_IF         3
#define STATION_TITLE_X                     2 
#define STATION_TITLE_Y                     2
#define STATION_WEATHER_MODE_TITLE          "Weather"
#define STATION_WELLCOME_MODE_TITLE         "Wellcome"      

typedef enum {
    WELLCOME,
    DRAWING,
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
    zone_matrix_t* current_matrix;
    display_if_t* current_if;
    bool mode_initialized;
    uint systick_counter;
} station_state_t;

extern station_state_t station_state;

void station_reset();
void station_init();
void station_disable_ble();
void station_enable_ble();
void station_reset_systick_counter();
void station_main();
void station_init_i2c_sensor();
void station_state_init();
void station_run();
void station_draw_title( char* title );
void station_gesture_handler( touchscreen_action_t geture_event );
void station_change_mode(station_mode_t next_mode);
void station_update_state_after_mode_switch( display_if_t* new_if );

#endif