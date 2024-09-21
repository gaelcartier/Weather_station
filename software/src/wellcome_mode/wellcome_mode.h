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
#include "../station/station.h"

#define WELLCOME_GRID_COL                4
#define WELLCOME_GRID_ROW                1
#define WELLCOME_GRID_COLOR              LCD_WHITE

#define WELLCOME_TITLE_X_OFFSET          5
#define WELLCOME_TITLE_Y_OFFSET          5


typedef struct {
    char name[32];
    char logo;
} wellcome_grid_content_t;

extern zone_matrix_t wellcome_grid;

void wellcome_mode_init();
void wellcome_mode_draw_grid();

#endif