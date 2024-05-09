#include <stdio.h>
#include "pico/stdlib.h"

#include "board.h"
#include "station/station.h"
#include "lcd/lcd.h"
#include "touchscreen/touchscreen.h"
#include "bme280/bme280.h"
#include "veml7700/veml7700.h"
#include "led_rgb/led_rgb.h"
#include "RN4870/RN4870.h"
#include "util/util.h"

#define log( S )        printf("%s%c", S, '\n')


typedef enum _test_t {
    USB,
    LCD,
    LCD_TOUCHSCREEN,
    BME_280,
    VEML_7700,
    BLE,
    LED_RGB,
    METEO,
    OTHER
} test_t;


void blink_led() {
    gpio_init( 25 );
    gpio_set_dir( 25 , GPIO_OUT);
    while (1) {
        gpio_put( 25, 0);
        sleep_ms(250);
        gpio_put( 25, 1);
        sleep_ms(1000);
    }
}

void test_usb() {
    while( 1 ) {
        log( "Hello world !\n" );
        sleep_ms( 1000 );
    }
}

void test_lcd() {
    // while( 1 ) {
    //     lcd_clear( LCD_YELLOW );
    //     log( "yellow" );
    //     sleep_ms(1000);
    //     lcd_clear( LCD_GREEN );
    //     log("green");
    //     sleep_ms(1000);
    //     lcd_clear( LCD_ORANGE );
    //     log("orange");
    //     sleep_ms(1000);
    // }
    lcd_backlight_on();
    lcd_fill_rect( 0, 160, 0, 120, LCD_YELLOW);
    lcd_draw_string( "Weather station", 0, 120, LCD_ORANGE, SmallFont );
}

void test_lcd_touchscreen() {

    touchscreen_init();
    lcd_clear( LCD_BLACK );
    lcd_backlight_on();

    while (true) {
        if( TOUCHED ) {
            // touchscreen_info_t touch_info = touchscreen_read();
            // lcd_fill_rect( touch_info.x-2, touch_info.x+2, touch_info.y-2, touch_info.y+2, LCD_YELLOW );
            // printf("- x : %d, y : %d \n", touch_info.x, touch_info.y);
            printf(">>> Screen touch detected\n");
            TOUCHED = false;
        }
    }
}

void test_bme280() {

    BME280_init();

    while( true ) {
        bme_280_data_t measures = BME280_read();
        printf(" - t° : %f, p : %f, h : %f \n", measures.temperature, measures.pressure, measures.humidity );
        sleep_ms( 1000 );
    }

}

void test_veml7700() {

    VEML7700_init();

    while( true ) {
        veml7700_data_t measures = VEML7700_read();
        printf("- ambiant light : %d, white light : %d \n", measures.ambient_light, measures.white_light );
        sleep_ms( 1000 );
    }

}

void test_led_rgb() {
    led_rgb_init();
    while(1) {
        led_rgb_write_clr( LED_OFF );
        sleep_ms(1000);
        led_rgb_write_clr( LED_RED );
        sleep_ms(1000);
        led_rgb_write_clr( LED_GREEN );
        sleep_ms(1000);
        led_rgb_write_clr( LED_BLUE );
        sleep_ms(1000);
    }
}

void test_ble() {
    RN4870_init();

    int ind = 0;
    int reading = 1;
    int c = '\0';
    char buffer[100] = "";

    while( true ) {

        c = getchar_timeout_us( 1 );
        if( c >= 0 ) {
            uart_putc( BLE_UART_INST, (char)c );
            printf("%c", c);
        }
        // if( c == '\r') {
        //     printf("\n");
        //     // buffer[ind] = '\n';
        //     reading = 0;
        //     ind = 0;
        // }
        // else if( c >= 0 ) {
        //     printf("%c",(char)c);
        //     buffer[ ind ] = (char)c;
        //     ind ++;
        // }

        // if( !reading ) {
        //     RN4870_write( (uint8_t*)buffer );
        //     reading = 1;
        //     for( int i = 0; i < 100; i++ ) buffer[i] = 0;
        // }
        if( BLE_DATA_RECEIVED ) {
            char data[100] = "";
            RN4870_read( (uint8_t*) data );
            printf( "\n%s", data );
        }
    }
}

int main() {
    
    test_t TEST = METEO;

    stdio_init_all();
    station_init();

    switch( TEST ) {
        case USB : test_usb();
            break;
        
        case LCD : test_lcd();
            break;

        case LCD_TOUCHSCREEN : test_lcd_touchscreen();
            break;
        
        case BME_280 : test_bme280();
            break;
        
        case VEML_7700 : test_veml7700();
            break;

        case LED_RGB : test_led_rgb();
            break;

        case BLE : test_ble();
            break;
        
        case METEO : station_main();
        
        default: blink_led(); // run only on pico
            
    }

    return 0;
}