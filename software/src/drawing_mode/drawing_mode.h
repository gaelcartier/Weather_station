#ifndef DRAWING_MODE_
#define DRAWING_MODE_

#include <stdio.h>

#include "../board.h"
#include "../display/display.h"
#include "../lcd/lcd.h"
#include "../station/station.h"
#include "../touchscreen/touchscreen.h"
#include "../weather_mode/weather_mode.h"
#include "pico/stdlib.h"

// --- Top zone
#define DRAWING_MODE_TITLE "Drawing"
#define DRAWING_TOP_COL 1
#define DRAWING_TOP_ROW 1
#define DRAWING_TOP_START ((point_t){0, 0})
#define DRAWING_TOP_END ((point_t){320, 30})
#define DRAWING_TOP_GRID_BORDER_COLOR LCD_WHITE

// --- Drawing zone
#define DRAWING_MAIN_COL 1
#define DRAWING_MAIN_ROW 1
#define DRAWING_MAIN_START (point_t){0, 30}
#define DRAWING_MAIN_END (point_t){320, 210}
#define DRAWING_MAIN_GRID_BORDER_COLOR LCD_WHITE
#define DRAWING_COLOR LCD_YELLOW

// -- Bottom zone
#define DRAWING_BOTTOM_COL 3
#define DRAWING_BOTTOM_ROW 1
#define DRAWING_BOTTOM_START (point_t){0, 210}
#define DRAWING_BOTTOM_END (point_t){320, 240}
#define DRAWING_BOTTOM_GRID_BORDER_COLOR LCD_WHITE
#define DRAWING_BOTTOM_LEFT_BUTTON_TXT "Return"
#define DRAWING_BOTTOM_RIGHT_BUTTON_TXT "Erase"
#define DRAWING_BOTTOM_TXT_X_OFFSET 20
#define DRAWING_BOTTOM_TXT_Y_OFFSET 10

typedef struct drawing_btm_grid_content_t {
    char name[32];
} drawing_btm_grid_content_t;

extern zone_matrix_t drawing_main_grid;
extern zone_matrix_t* drawing_mode_matrix[];
extern display_if_t drawing_mode_if;

void drawing_mode_init_matrix();
void drawing_mode_init_if();
void drawing_mode_draw_grid();
void drawing_mode_draw();
void drawing_mode_erase();
void drawing_mode_switch_to_wellcome_mode();
bool drawing_mode_is_in_drawing_zone(uint16_t x, uint16_t y);

#endif