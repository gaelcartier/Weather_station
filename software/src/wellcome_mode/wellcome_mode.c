#include "wellcome_mode.h"

// --- Top zone
zone_t wellcome_zone_top[WELLCOME_TOP_GRID_COL*WELLCOME_TOP_GRID_ROW];
zone_matrix_t wellcome_top_grid = ZONE_MATRIX_INIT;

// --- Main zone
zone_t wellcome_zone_main[WELLCOME_MAIN_GRID_COL*WELLCOME_MAIN_GRID_ROW];
zone_matrix_t wellcome_main_grid = ZONE_MATRIX_INIT;

wellcome_grid_content_t weather = {"Weather", 'W',};
wellcome_grid_content_t drawing = {"Drawing", 'D'};
wellcome_grid_content_t game_of_life = {"G.o.L", 'G'};
wellcome_grid_content_t snake = {"Snake", 'S'};

// --- Bottom zone
zone_t wellcome_zone_bottom[WELLCOME_BOTTOM_GRID_COL*WELLCOME_BOTTOM_GRID_ROW];
zone_matrix_t wellcome_bottom_grid = ZONE_MATRIX_INIT;

// --- Wellcome mode interface 
zone_matrix_t* wellcome_mode_matrix[STATION_MATRIX_NUMBER_IN_IF] = {&wellcome_top_grid, &wellcome_main_grid, &wellcome_bottom_grid};
display_if_t wellcome_mode_if = DISPLAY_IF_INIT;

void wellcome_mode_init_if() {
    wellcome_mode_init_matrix();
    wellcome_mode_if.matrix_if = wellcome_mode_matrix;
    wellcome_mode_if.matrix_number = STATION_MATRIX_NUMBER_IN_IF;
    lcd_clear(LCD_BLACK);
    wellcome_mode_draw_grid(WEATHER_ALL_GRID);
}

void wellcome_mode_init_matrix(){
    display_create_zone_matrix(&wellcome_main_grid, wellcome_zone_main, WELLCOME_MAIN_GRID_ROW, WELLCOME_MAIN_GRID_COL, WELLCOME_MAIN_START, WELLCOME_MAIN_END);
    wellcome_main_grid.z[0].content = &weather;
    wellcome_main_grid.z[0].point_handler = (void*)wellcome_mode_switch_to_weather_mode;
    wellcome_main_grid.z[0].long_point_handler = (void*)wellcome_mode_switch_to_weather_mode;
    wellcome_main_grid.z[1].content = &drawing;
    wellcome_main_grid.z[1].point_handler = (void*)wellcome_mode_switch_to_drawing_mode;
    wellcome_main_grid.z[1].long_point_handler = (void*)wellcome_mode_switch_to_drawing_mode;
    wellcome_main_grid.z[2].content = &game_of_life;
    wellcome_main_grid.z[3].content = &snake;
    display_create_zone_matrix(&wellcome_top_grid, wellcome_zone_top, WELLCOME_TOP_GRID_ROW, WELLCOME_TOP_GRID_COL, WELLCOME_TOP_START, WELLCOME_TOP_END);
    display_create_zone_matrix(&wellcome_bottom_grid, wellcome_zone_bottom, WELLCOME_BOTTOM_GRID_ROW, WELLCOME_BOTTOM_GRID_COL, WELLCOME_BOTTOM_START, WELLCOME_BOTTOM_END);
}

void wellcome_mode_draw_grid(){
    station_draw_title( STATION_WELLCOME_MODE_TITLE );
    for(int i = 0; i<WELLCOME_MAIN_GRID_ROW*WELLCOME_MAIN_GRID_COL; i++){
        display_draw_zone(wellcome_main_grid.z[i], WELLCOME_MAIN_GRID_BORDER_COLOR);
        wellcome_grid_content_t *content = wellcome_main_grid.z[i].content;
        lcd_draw_string((char*)(content->name), wellcome_main_grid.z[i].p1.x+WELLCOME_TITLE_X_OFFSET, wellcome_main_grid.z[i].p1.y+WELLCOME_TITLE_Y_OFFSET, LCD_YELLOW, SmallFont);
    }    
    for(int i = 0; i<WELLCOME_TOP_GRID_ROW*WELLCOME_TOP_GRID_COL; i++){
        display_draw_zone(wellcome_top_grid.z[i], WELLCOME_TOP_GRID_BORDER_COLOR);
    }
    for(int i = 0; i<WELLCOME_BOTTOM_GRID_ROW*WELLCOME_BOTTOM_GRID_COL; i++){
        display_draw_zone(wellcome_bottom_grid.z[i], WELLCOME_BOTTOM_GRID_BORDER_COLOR);
    }
}

void wellcome_mode_switch_to_weather_mode(){
    station_change_mode( WEATHER_ALL_GRID );
    weather_mode_init_if();
    station_update_state_after_mode_switch( &weather_mode_if );
}

void wellcome_mode_switch_to_drawing_mode() {
    station_change_mode( DRAWING );
    drawing_mode_init_if();
    station_update_state_after_mode_switch( &drawing_mode_if );
}