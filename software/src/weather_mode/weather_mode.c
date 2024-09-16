#include "weather_mode.h"

zone_t weather_zone_grid[WEATHER_GRID_COL*WEATHER_GRID_ROW];
zone_matrix_t weather_grid;

weather_grid_content_t temperature = {"Temperature", 0};
weather_grid_content_t humidity = {"Humidity", 0};
weather_grid_content_t pressure = {"Pressure", 0};
weather_grid_content_t light = {"Light", 0};


void weather_mode_init(){
    // BME280_init();
    // VEML7700_init();
    display_create_zone_matrix( &weather_grid, weather_zone_grid, WEATHER_GRID_ROW, WEATHER_GRID_COL, (point_t){0,20}, (point_t){320,220} );
    weather_grid.z[WEATHER_ZONE_TEMP].content = &temperature;
    weather_grid.z[WEATHER_ZONE_HUM].content = &humidity;
    weather_grid.z[WEATHER_ZONE_PRESS].content = &pressure;
    weather_grid.z[WEATHER_ZONE_LIGHT].content = &light;
    weather_mode_draw_grid();
}

void weather_mode_draw_grid(){
    for(int i = 0; i<WEATHER_GRID_ROW*WEATHER_GRID_COL; i++){
        display_draw_zone(weather_grid.z[i], WEATHER_GRID_COLOR);
        weather_grid_content_t *content = weather_grid.z[i].content;
        lcd_draw_string((char*)(content->name), weather_grid.z[i].p1.x+WEATHER_TITLE_X_OFFSET, weather_grid.z[i].p1.y+WEATHER_TITLE_Y_OFFSET, LCD_YELLOW, SmallFont);
    }
}

void weather_mode_measure_data() {
    veml7700_data_t light_tmp = VEML7700_read();
    bme_280_data_t bme_data = BME280_read();
    temperature.data = (int)bme_data.temperature;
    humidity.data = (int)bme_data.humidity;
    pressure.data = (int)bme_data.pressure;
    light.data = (int)light_tmp.ambient_light;
}

void weather_mode_update_data_on_screen(){
    for(int i = 0; i<WEATHER_GRID_ROW*WEATHER_GRID_COL; i++) {
        weather_grid_content_t *content = weather_grid.z[i].content;
        lcd_fill_rect(WEATHER_DATA_POS_X(weather_grid.z[i]), WEATHER_DATA_POS_X(weather_grid.z[i])+40, WEATHER_DATA_POS_Y(weather_grid.z[i]), WEATHER_DATA_POS_Y(weather_grid.z[i])+8, LCD_BLACK);
        lcd_print_int((int)content->data, WEATHER_DATA_POS_X(weather_grid.z[i]), WEATHER_DATA_POS_Y(weather_grid.z[i]), LCD_LIGHT_BLUE, SmallFont);
        printf(" data : %d\n", content->data);
    }
}

