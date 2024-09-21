#include "wellcome_mode.h"


zone_t wellcome_zone_grid[WELLCOME_GRID_COL*WELLCOME_GRID_ROW];
zone_matrix_t wellcome_grid;

wellcome_grid_content_t weather = {"Weather", 'W',};
wellcome_grid_content_t drawing = {"Drawing", 'D'};
wellcome_grid_content_t game_of_life = {"G.o.L", 'G'};
wellcome_grid_content_t snake = {"Snake", 'S'};

void wellcome_mode_init(){
    display_create_zone_matrix(&wellcome_grid, wellcome_zone_grid, WELLCOME_GRID_ROW, WELLCOME_GRID_COL, (point_t){0,LCD_Y/3}, (point_t){320,2*(LCD_Y/3)});
    wellcome_grid.z[0].content = &weather;
    wellcome_grid.z[0].point_handler = (void*)weather_mode_init;
    wellcome_grid.z[0].long_point_handler = (void*)weather_mode_init;
    wellcome_grid.z[1].content = &drawing;
    wellcome_grid.z[2].content = &game_of_life;
    wellcome_grid.z[3].content = &snake;
    wellcome_mode_draw_grid(WEATHER_ALL_GRID);
}

void wellcome_mode_draw_grid(){
    for(int i = 0; i<WELLCOME_GRID_ROW*WELLCOME_GRID_COL; i++){
        display_draw_zone(wellcome_grid.z[i], WELLCOME_GRID_COLOR);
        wellcome_grid_content_t *content = wellcome_grid.z[i].content;
        lcd_draw_string((char*)(content->name), wellcome_grid.z[i].p1.x+WELLCOME_TITLE_X_OFFSET, wellcome_grid.z[i].p1.y+WELLCOME_TITLE_Y_OFFSET, LCD_YELLOW, SmallFont);
    }
}