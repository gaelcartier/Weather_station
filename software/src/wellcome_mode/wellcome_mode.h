#ifndef _WELLCOME_MODE_H_
#define _WELLCOME_MODE_H_

#include <stdio.h>

#include <stdio.h>
#include "pico/stdlib.h"

#include "../board.h"

#include "../lcd/lcd.h"
#include "../display/display.h"
#include "../touchscreen/touchscreen.h"
#include "../weather_mode/weather_mode.h"
#include "../drawing_mode/drawing_mode.h"
#include "../station/station.h"

//--- Top zone
#define WELLCOME_TITLE_X_OFFSET                     5
#define WELLCOME_TITLE_Y_OFFSET                     5

#define WELLCOME_TOP_GRID_COL                       1
#define WELLCOME_TOP_GRID_ROW                       1
#define WELLCOME_TOP_GRID_BORDER_COLOR              LCD_WHITE
#define WELLCOME_TOP_START                          ((point_t){0,0})                
#define WELLCOME_TOP_END                            ((point_t){320,30})

// --- Main zone
#define WELLCOME_MAIN_GRID_COL                      4
#define WELLCOME_MAIN_GRID_ROW                      1
#define WELLCOME_MAIN_GRID_BORDER_COLOR             LCD_WHITE
#define WELLCOME_MAIN_START                         ((point_t){0,30})                
#define WELLCOME_MAIN_END                           ((point_t){320,210})

// --- Bottom zone
#define WELLCOME_BOTTOM_GRID_COL                    3
#define WELLCOME_BOTTOM_GRID_ROW                    1
#define WELLCOME_BOTTOM_GRID_BORDER_COLOR           LCD_WHITE
#define WELLCOME_BOTTOM_START                       ((point_t){0,210})                
#define WELLCOME_BOTTOM_END                         ((point_t){320,240})


typedef struct {
    char name[32];
    char logo;
} wellcome_grid_content_t;

extern zone_matrix_t wellcome_main_grid;
extern zone_matrix_t* wellcome_mode_if[];

void wellcome_mode_init();
void wellcome_mode_draw_grid();
void wellcome_mode_switch_to_weather_mode();
void wellcome_mode_switch_to_drawing_mode();

#endif