#include "drawing_mode.h"

// --- Top zone
zone_t drawing_zone_top[DRAWING_TOP_COL*DRAWING_TOP_ROW];
zone_matrix_t drawing_top_grid = ZONE_MATRIX_INIT;

// --- Drawing zone
zone_t drawing_zone_main[DRAWING_MAIN_COL*DRAWING_MAIN_ROW];
zone_matrix_t drawing_main_grid = ZONE_MATRIX_INIT;

// --- Bottom zone
zone_t drawing_zone_bottom[DRAWING_BOTTOM_COL*DRAWING_BOTTOM_ROW];
zone_matrix_t drawing_bottom_grid = ZONE_MATRIX_INIT;

// --- Drawing mode interface
zone_matrix_t* drawing_mode_if[3] = {&drawing_top_grid, &drawing_main_grid, &drawing_bottom_grid};


void drawing_mode_init() {
    display_create_zone_matrix(&drawing_top_grid, drawing_zone_top, DRAWING_TOP_ROW, DRAWING_TOP_COL, DRAWING_TOP_START, DRAWING_TOP_END);
    display_create_zone_matrix(&drawing_bottom_grid, drawing_zone_bottom, DRAWING_BOTTOM_ROW, DRAWING_BOTTOM_COL, DRAWING_BOTTOM_START, DRAWING_BOTTOM_END);
    display_create_zone_matrix(&drawing_main_grid, drawing_zone_main, DRAWING_MAIN_ROW, DRAWING_MAIN_COL, DRAWING_MAIN_START, DRAWING_MAIN_END);
    drawing_main_grid.z[0].point_handler = (void*)drawing_mode_draw;
    lcd_clear(LCD_BLACK);
    drawing_mode_draw_grid();
    touchscreen_switch_to_simple_touch_mode();
}

void drawing_mode_draw_grid() {
    station_draw_title( DRAWING_MODE_TITLE );
    for(int i = 0; i<DRAWING_MAIN_ROW*DRAWING_MAIN_COL; i++){
        display_draw_zone(drawing_main_grid.z[i], DRAWING_MAIN_GRID_BORDER_COLOR);
    }
    for(int i = 0; i<DRAWING_TOP_ROW*DRAWING_TOP_COL; i++){
        display_draw_zone(drawing_top_grid.z[i], DRAWING_TOP_GRID_BORDER_COLOR);
    }
    for(int i = 0; i<DRAWING_BOTTOM_ROW*DRAWING_BOTTOM_COL; i++){
        display_draw_zone(drawing_bottom_grid.z[i], DRAWING_BOTTOM_GRID_BORDER_COLOR);
    }
    
}


void drawing_mode_draw(){
    touchscreen_info_t touch_info = touchscreen_handler_in_simple_touch_mode();
    if( touch_info.touch_event != NO_EVENT ){
        uint16_t x = touch_info.x;
        uint16_t y = touch_info.y;
        if( x-2 > drawing_main_grid.start.x && x+2 < drawing_main_grid.end.x && y-2 > drawing_main_grid.start.y && y+2 < drawing_main_grid.end.y ) 
            lcd_fill_rect( touch_info.x-2, touch_info.x+2, touch_info.y-2, touch_info.y+2, LCD_YELLOW);
    }
}