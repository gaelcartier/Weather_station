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

// --- Top zone
#define DRAWING_MODE_TITLE                  "Drawing"
#define DRAWING_TOP_COL                     1
#define DRAWING_TOP_ROW                     1
#define DRAWING_TOP_START                   ((point_t){0,0})
#define DRAWING_TOP_END                     ((point_t){320,30})
#define DRAWING_TOP_GRID_BORDER_COLOR       LCD_WHITE

// --- Drawing zone
#define DRAWING_MAIN_COL                    1
#define DRAWING_MAIN_ROW                    1
#define DRAWING_MAIN_START                  (point_t){0,30}
#define DRAWING_MAIN_END                    (point_t){320,210}
#define DRAWING_MAIN_GRID_BORDER_COLOR      LCD_WHITE
#define DRAWING_COLOR                       LCD_YELLOW

// -- Bottom zone
#define DRAWING_BOTTOM_COL                  3
#define DRAWING_BOTTOM_ROW                  1
#define DRAWING_BOTTOM_START                (point_t){0,210}
#define DRAWING_BOTTOM_END                  (point_t){320,240}
#define DRAWING_BOTTOM_GRID_BORDER_COLOR    LCD_WHITE


extern zone_matrix_t drawing_main_grid;
extern zone_matrix_t* drawing_mode_if[];

void drawing_mode_init();
void drawing_mode_draw_grid();
void drawing_mode_draw();

#endif