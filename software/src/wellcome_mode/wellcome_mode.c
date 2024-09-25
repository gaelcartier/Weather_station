#include "wellcome_mode.h"


zone_t wellcome_zone_grid[WELLCOME_GRID_COL*WELLCOME_GRID_ROW];
zone_matrix_t wellcome_grid = ZONE_MATRIX_INIT;

wellcome_grid_content_t weather = {"Weather", 'W',};
wellcome_grid_content_t drawing = {"Drawing", 'D'};
wellcome_grid_content_t game_of_life = {"G.o.L", 'G'};
wellcome_grid_content_t snake = {"Snake", 'S'};

void wellcome_mode_init(){
    display_create_zone_matrix(&wellcome_grid, wellcome_zone_grid, WELLCOME_GRID_ROW, WELLCOME_GRID_COL, (point_t){0,LCD_Y/3}, (point_t){320,2*(LCD_Y/3)});
    wellcome_grid.z[0].content = &weather;
    wellcome_grid.z[0].point_handler = (void*)wellcome_mode_switch_to_weather_mode;
    wellcome_grid.z[0].long_point_handler = (void*)wellcome_mode_switch_to_weather_mode;
    wellcome_grid.z[1].content = &drawing;
    wellcome_grid.z[1].point_handler = (void*)wellcome_mode_switch_to_drawing_mode;
    wellcome_grid.z[1].long_point_handler = (void*)wellcome_mode_switch_to_drawing_mode;
    wellcome_grid.z[2].content = &game_of_life;
    wellcome_grid.z[3].content = &snake;
    lcd_clear(LCD_BLACK);
    wellcome_mode_draw_grid(WEATHER_ALL_GRID);
}

void wellcome_mode_draw_grid(){
    station_draw_title( STATION_WELLCOME_MODE_TITLE );
    for(int i = 0; i<WELLCOME_GRID_ROW*WELLCOME_GRID_COL; i++){
        display_draw_zone(wellcome_grid.z[i], WELLCOME_GRID_COLOR);
        wellcome_grid_content_t *content = wellcome_grid.z[i].content;
        lcd_draw_string((char*)(content->name), wellcome_grid.z[i].p1.x+WELLCOME_TITLE_X_OFFSET, wellcome_grid.z[i].p1.y+WELLCOME_TITLE_Y_OFFSET, LCD_YELLOW, SmallFont);
    }
}

void wellcome_mode_switch_to_weather_mode(){
    station_change_mode( WEATHER_ALL_GRID );
    weather_mode_init();
    station_update_state_after_mode_switch(&weather_grid);
}

void wellcome_mode_switch_to_drawing_mode() {
    station_change_mode( DRAWING );
    drawing_mode_init();
    station_update_state_after_mode_switch(&drawing_grid);
}