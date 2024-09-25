#ifndef DRAWING_MODE_
#define DRAWING_MODE_ 

#include <stdio.h>

#include <stdio.h>
#include "pico/stdlib.h"

#include "../board.h"

#include "../lcd/lcd.h"
#include "../display/display.h"
#include "../touchscreen/touchscreen.h"
#include "../weather_mode/weather_mode.h"
#include "../station/station.h"

#define DRAWING_GRID_COL            1
#define DRAWING_GRID_ROW            1

#define DRAWING_GRID_COLOR          LCD_WHITE      
#define DRAWING_MODE_TITLE          "Drawing"

extern zone_matrix_t drawing_grid;

void drawing_mode_init();
void drawing_mode_draw_grid();
void drawing_mode_draw();

#endif