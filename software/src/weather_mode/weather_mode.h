#ifndef _WEATHER_MODE_H_
#define _WEATHER_MODE_H_ 

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
#include "../station/station.h"

// --- Top zone
#define WEATHER_TOP_GRID_COL                        1
#define WEATHER_TOP_GRID_ROW                        1
#define WEATHER_TOP_GRID_BORDER_COLOR               LCD_WHITE
#define WEATHER_TOP_START                           ((point_t){0,0})
#define WEATHER_TOP_END                             ((point_t){320,30})

// --- Main zone
#define WEATHER_MAIN_GRID_COL                       2
#define WEATHER_MAIN_GRID_ROW                       2
#define WEATHER_MAIN_GRID_BORDER_COLOR              LCD_WHITE
#define WEATHER_MAIN_START                          ((point_t){0,30})
#define WEATHER_MAIN_END                            ((point_t){320,210})

#define WEATHER_TITLE_X_OFFSET                      5
#define WEATHER_TITLE_Y_OFFSET                      5

#define WEATHER_DATA_POS_X(data_zone)               (data_zone.p2.x - (data_zone.p2.x - data_zone.p1.x)/2 - 30)
#define WEATHER_DATA_POS_Y(data_zone)               (data_zone.p2.y - (data_zone.p2.y - data_zone.p1.y)/2)

#define WEATHER_ZONE_TEMP                           0
#define WEATHER_ZONE_HUM                            1
#define WEATHER_ZONE_PRESS                          2
#define WEATHER_ZONE_LIGHT                          3

// --- Bottom zone
#define WEATHER_BOTTOM_GRID_COL                     3
#define WEATHER_BOTTOM_GRID_ROW                     1
#define WEATHER_BOTTOM_GRID_BORDER_COLOR            LCD_WHITE
#define WEATHER_BOTTOM_START                        ((point_t){0,210})
#define WEATHER_BOTTOM_END                          ((point_t){320,240})



typedef struct {
    int temp;
    int hum;
    int pressure;
    int light;
} weather_data_t;

typedef struct {
    char name[32];
    int data;
} weather_grid_content_t;

extern zone_matrix_t weather_main_grid;
extern zone_matrix_t* weather_mode_matrix[];
extern display_if_t weather_mode_if;

void weather_mode_init_if();
void weather_mode_init_matrix();
void weather_mode_draw_grid();
void weather_mode_measure_data();
void weather_mode_update_data_on_screen();
void weather_mode_switch_to_wellcome_mode();

#endif