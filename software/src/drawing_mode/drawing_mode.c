#include "drawing_mode.h"

zone_t drawing_zone_grid[DRAWING_GRID_COL*DRAWING_GRID_ROW];
zone_matrix_t drawing_grid = ZONE_MATRIX_INIT;

void drawing_mode_init() {
    display_create_zone_matrix(&drawing_grid, drawing_zone_grid, DRAWING_GRID_ROW, DRAWING_GRID_COL, (point_t){0,20}, (point_t){320,220});
    drawing_grid.z[0].point_handler = (void*)drawing_mode_draw;
    lcd_clear(LCD_BLACK);
    drawing_mode_draw_grid();
    touchscreen_switch_to_simple_touch_mode();
}

void drawing_mode_draw_grid() {
    station_draw_title( DRAWING_MODE_TITLE );
    for(int i = 0; i<DRAWING_GRID_ROW*DRAWING_GRID_COL; i++){
        display_draw_zone(drawing_grid.z[i], DRAWING_GRID_COLOR);
    }
}

void drawing_mode_draw(){
    uint16_t x = touchscreen_status.action.x;
    uint16_t y = touchscreen_status.action.y;
    lcd_fill_rect(x-5, x+5, y-5, y+5, LCD_YELLOW);
}