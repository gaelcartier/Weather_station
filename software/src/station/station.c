#include "station.h"

station_state_t station_state;

extern void isr_systick() {
    station_state.systick_counter ++;
    touchscreen_status.duration ++;
}

void station_reset() {
    gpio_init( nRESET_GPIO );
	gpio_set_dir( nRESET_GPIO, GPIO_OUT );
	gpio_put( nRESET_GPIO, 0 );
	sleep_ms( 2 );
	gpio_put( nRESET_GPIO, 1 );
    sleep_ms(2);
}

void station_init_gpio() {
    gpio_init( BLE_ENABLE_GPIO );
    gpio_set_dir( BLE_ENABLE_GPIO, GPIO_OUT );

    gpio_init( LCD_BACKLIGHT_GPIO );
    gpio_set_dir( LCD_BACKLIGHT_GPIO, GPIO_OUT );
}

void station_init() {
    station_reset();
    station_init_gpio();
    // station_disable_ble();
    lcd_backlight_off();
    lcd_init();
    station_state_init();
    systick_init( 124999UL );
    touchscreen_init();
}

void station_state_init() {
    station_state.systick_counter = 0;
    station_state.mode = STATION_WELLCOME;
    station_state.mode_initialized = false;
}

void station_disable_ble() {
    gpio_put( BLE_ENABLE_GPIO, 1 );
}

void station_enable_ble() {
    gpio_put( BLE_ENABLE_GPIO, 0 );
}

void station_init_i2c_sensor() {
	i2c_init( I2C_SENSOR_INST, 100*1000 );

	gpio_set_function( I2C_SENSOR_SCL_GPIO, GPIO_FUNC_I2C );
	gpio_set_function( I2C_SENSOR_SDA_GPIO, GPIO_FUNC_I2C );

	// gpio_pull_up( BME_I2C_SCL_GPIO ); // si nécéssaire ... ( car absent sur le circuit ou disfonctionnement random )
	// gpio_pull_up( BME_I2C_SDA_GPIO );
}

void station_main() {
    
    station_init_i2c_sensor();
    BME280_config();
    VEML7700_config();
    RN4870_init();

    lcd_draw_string( "Station meteo", 50, 0, LCD_ORANGE, BigFont );
    lcd_draw_string( "T", 50, 100, LCD_LIGHT_GREEN, BigFont );
    lcd_draw_string( "P", 120, 100, LCD_LIGHT_GREEN, BigFont );
    lcd_draw_string( "H", 190, 100, LCD_LIGHT_GREEN, BigFont );
    lcd_draw_string( "L", 260, 100, LCD_LIGHT_GREEN, BigFont );
    lcd_backlight_on();
    // station_enable_ble();
    while( true ) {
        bme_280_data_t measures_w = BME280_read();        
        veml7700_data_t measures_l = VEML7700_read();
        printf("- ambiant light : %d, white light : %d \n", measures_l.ambient_light, measures_l.white_light );
        printf(" - t° : %f, p : %f, h : %f \n", measures_w.temperature, measures_w.pressure, measures_w.humidity );
        lcd_fill_rect( 10, 300, 150, 162, LCD_BLACK );
        lcd_print_double( (double)(measures_w.temperature), 35, 150, LCD_YELLOW, SmallFont );
        lcd_print_int( (int)(measures_w.pressure), 110, 150, LCD_YELLOW, SmallFont );
        lcd_print_double( (double)(measures_w.humidity), 180, 150, LCD_YELLOW, SmallFont );
        lcd_print_int( measures_l.ambient_light, 250, 150, LCD_YELLOW, SmallFont );
        sleep_ms( 1000 );
    }
}

void station_run(){
    station_init();
    while(true) {
        switch(station_state.mode){
            case STATION_WELLCOME:
                if(!station_state.mode_initialized){
                    lcd_backlight_on();
                    station_draw_title( STATION_WELLCOME_MODE_TITLE );
                    wellcome_mode_init();
                    station_state.current_matrix = &wellcome_grid;
                    station_state.mode_initialized = true;
                } else {

                }
                break;
            case WEATHER_ALL_GRID: 
                if(!station_state.mode_initialized) {
                    station_init_i2c_sensor();
                    BME280_config();
                    VEML7700_config();
                    lcd_clear(LCD_BLACK);
                    lcd_backlight_on();
                    station_draw_title( STATION_WEATHER_MODE_TITLE );
                    weather_mode_init();
                    station_state.current_matrix = &weather_grid;
                    station_state.mode_initialized = true;
                } else {
                    weather_mode_measure_data();
                    weather_mode_update_data_on_screen();
                    // printf("display data\n");
                    sleep_ms(1000);
                }
                break;
            default: 
                break;
        }
        touchscreen_handler( &station_gesture_handler );
    }
}

void station_draw_title( char* title ){
    lcd_draw_string(title, STATION_TITLE_X, STATION_TITLE_Y, LCD_LIGHT_GREEN, BigFont );
}

void station_change_mode(station_mode_t next_mode){
    station_state.mode = next_mode;
    station_state.mode_initialized = false;
}

void station_gesture_handler( touchscreen_action_t gesture_event ){
    if( gesture_event.gesture != NO_GESTURE ){
        switch(gesture_event.gesture){
            case MOVE_UP: 
                lcd_clear(LCD_LIGHT_BLUE);
                break;
            case MOVE_DOWN: 
                lcd_clear(LCD_LIGHT_GREEN);
                break;
            case MOVE_RIGHT:
                lcd_clear(LCD_ORANGE);
                break;
            case MOVE_LEFT: 
                lcd_clear(LCD_YELLOW);
                break;
            default: {
                zone_t* zone_touched = display_find_zone_from_coordinates( station_state.current_matrix, gesture_event.x, gesture_event.y);
                if(gesture_event.gesture == POINT) zone_touched->point_handler();
                else if(gesture_event.gesture == LONG_POINT) zone_touched->long_point_handler();
                break;
            }
        }
    }
}