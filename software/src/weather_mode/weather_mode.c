#include "weather_mode.h"

// --- Top zone
zone_t weather_zone_top[WEATHER_TOP_GRID_COL*WEATHER_TOP_GRID_ROW];
zone_matrix_t weather_top_grid = ZONE_MATRIX_INIT;

// --- Main zone
zone_t weather_zone_main[WEATHER_MAIN_GRID_COL*WEATHER_MAIN_GRID_ROW];
zone_matrix_t weather_main_grid= ZONE_MATRIX_INIT;

weather_grid_content_t temperature = {"Temperature", 0};
weather_grid_content_t humidity = {"Humidity", 0};
weather_grid_content_t pressure = {"Pressure", 0};
weather_grid_content_t light = {"Light", 0};

// --- Bottom zone
zone_t weather_zone_bottom[WEATHER_BOTTOM_GRID_COL*WEATHER_BOTTOM_GRID_ROW];
zone_matrix_t weather_bottom_grid = ZONE_MATRIX_INIT;

// --- WEather mode interface
zone_matrix_t* weather_mode_if[STATION_MATRIX_NUMBER_IN_IF] = {&weather_top_grid, &weather_main_grid, &weather_bottom_grid};

void weather_mode_init(){
    // BME280_init();
    // VEML7700_init();
    display_create_zone_matrix( &weather_main_grid, weather_zone_main, WEATHER_MAIN_GRID_ROW, WEATHER_MAIN_GRID_COL, WEATHER_MAIN_START, WEATHER_MAIN_END );
    weather_main_grid.z[WEATHER_ZONE_TEMP].content = &temperature;
    weather_main_grid.z[WEATHER_ZONE_HUM].content = &humidity;
    weather_main_grid.z[WEATHER_ZONE_PRESS].content = &pressure;
    weather_main_grid.z[WEATHER_ZONE_LIGHT].content = &light;
    weather_main_grid.swipe_left_handler = (void*)weather_mode_switch_to_wellcome_mode;
    weather_main_grid.swipe_right_handler = (void*)weather_mode_switch_to_wellcome_mode;
    display_create_zone_matrix( &weather_top_grid, weather_zone_top, WEATHER_TOP_GRID_ROW, WEATHER_TOP_GRID_COL, WEATHER_TOP_START, WEATHER_TOP_END );
    display_create_zone_matrix( &weather_bottom_grid, weather_zone_bottom, WEATHER_BOTTOM_GRID_ROW, WEATHER_BOTTOM_GRID_COL, WEATHER_BOTTOM_START, WEATHER_BOTTOM_END );
    station_init_i2c_sensor();
    BME280_config();
    VEML7700_config();
    lcd_clear(LCD_BLACK);
    lcd_backlight_on();
    weather_mode_draw_grid();
}

void weather_mode_draw_grid(){
    station_draw_title( STATION_WEATHER_MODE_TITLE );
    for(int i = 0; i<WEATHER_MAIN_GRID_ROW*WEATHER_MAIN_GRID_COL; i++){
        display_draw_zone(weather_main_grid.z[i], WEATHER_MAIN_GRID_BORDER_COLOR);
        weather_grid_content_t *content = weather_main_grid.z[i].content;
        lcd_draw_string((char*)(content->name), weather_main_grid.z[i].p1.x+WEATHER_TITLE_X_OFFSET, weather_main_grid.z[i].p1.y+WEATHER_TITLE_Y_OFFSET, LCD_YELLOW, SmallFont);
    }
    for(int i = 0; i<WEATHER_TOP_GRID_ROW*WEATHER_TOP_GRID_COL; i++){
        display_draw_zone(weather_top_grid.z[i], WEATHER_TOP_GRID_BORDER_COLOR);
    }
    for(int i = 0; i<WEATHER_BOTTOM_GRID_ROW*WEATHER_BOTTOM_GRID_COL; i++){
        display_draw_zone(weather_bottom_grid.z[i], WEATHER_BOTTOM_GRID_BORDER_COLOR);
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
    for(int i = 0; i<WEATHER_MAIN_GRID_ROW*WEATHER_MAIN_GRID_COL; i++) {
        weather_grid_content_t *content = weather_main_grid.z[i].content;
        lcd_fill_rect(WEATHER_DATA_POS_X(weather_main_grid.z[i]), WEATHER_DATA_POS_X(weather_main_grid.z[i])+40, WEATHER_DATA_POS_Y(weather_main_grid.z[i]), WEATHER_DATA_POS_Y(weather_main_grid.z[i])+8, LCD_BLACK);
        lcd_print_int((int)content->data, WEATHER_DATA_POS_X(weather_main_grid.z[i]), WEATHER_DATA_POS_Y(weather_main_grid.z[i]), LCD_LIGHT_BLUE, SmallFont);
        printf(" data : %d\n", content->data);
    }
}

void weather_mode_switch_to_wellcome_mode() {
    station_change_mode(WELLCOME);
    wellcome_mode_init();
    station_update_state_after_mode_switch(wellcome_mode_if);
}

