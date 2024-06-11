#include <stdio.h>
#include "pico/stdlib.h"

#include "board.h"
#include "station/station.h"
#include "lcd/lcd.h"
#include "display/display.h"
#include "touchscreen/touchscreen.h"
#include "bme280/bme280.h"
#include "veml7700/veml7700.h"
#include "led_rgb/led_rgb.h"
#include "RN4870/RN4870.h"
#include "util/util.h"
#include "systick/systick.h"
#include "i2c_non_blocking/i2c_non_blocking.h"

#define log( S )        printf("%s%c", S, '\n')

uint systick_counter; 
extern uint in_i2c_irq;

// extern volatile touchscreen_status_t touchscreen_status;


typedef enum _test_t {
    USB,
    LCD,
    TOUCHSCREEN,
    BME_280,
    VEML_7700,
    BLE,
    LED_RGB,
    DISPLAY,
    SYSTICK,
    I2C_NB,
    CALLBACK,
    METEO,
    OTHER
} test_t;

extern void isr_systick() {
    systick_counter ++;
    touchscreen_status.duration ++;
}

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
    lcd_backlight_on();
    while( 1 ) {
        lcd_clear( LCD_YELLOW );
        log( "yellow" );
        sleep_ms(1000);
        lcd_clear( LCD_LIGHT_GREEN );
        log("green");
        sleep_ms(1000);
        lcd_clear( LCD_ORANGE );
        log("orange");
        sleep_ms(1000);
    }
    lcd_fill_rect( 0, 160, 0, 120, LCD_YELLOW);
    lcd_fill_rect( 300, LCD_X, 200, LCD_Y, LCD_LIGHT_GREEN);
    lcd_draw_string( "Weather station", 0, 120, LCD_ORANGE, SmallFont );
}

void test_touchscreen() {
    systick_counter = 0;
    systick_init( 124999UL );

    touchscreen_init();
    lcd_clear( LCD_BLACK );
    lcd_backlight_on();

    while (true) {
        touchscreen_handler();
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

void test_display(){
    lcd_backlight_on();
    uint col = 7;
    uint row = 13;
    zone_t zone_array[col*row];
    zone_matrix_t zm;
    display_create_zone_matrix( &zm, zone_array, row, col, (point_t){0,20}, (point_t){320,220} );
    for(int i = 0; i<row*col; i++){
        display_draw_zone(zm.z[i], LCD_YELLOW);
    }
}

void test_systick() {
    systick_counter = 0;
    systick_init( 124999UL );
    while(1){
        printf(">>> Counter = %d\n", systick_counter);
        sleep_ms(1000);
    }
}

void test_i2c_nb(){
    i2c_non_blocking_init( TOUCHSCREEN_I2C_INST, 100*1000, i2c_nb_handler );
    while(1){
        i2c_request_data( TOUCHSCREEN_I2C_INST, TOUCHSCREEN_I2C_ADDR, TOUCHSCREEN_GEST_ID);
        sleep_ms(1000);
        printf("in handler() ?\n");
        if( in_i2c_irq ){
            printf(">>> In I2C irq_handler()\n");
            in_i2c_irq = 0;
        }
    }
}

void test_callback(){
    while(1);
}

int main() {
    
    test_t TEST = TOUCHSCREEN;

   stdio_init_all();
   station_init();

    switch( TEST ) {
        case USB : test_usb();
            break;
        
        case LCD : test_lcd();
            break;

        case TOUCHSCREEN : test_touchscreen();
            break;
        
        case BME_280 : test_bme280();
            break;
        
        case VEML_7700 : test_veml7700();
            break;

        case LED_RGB : test_led_rgb();
            break;

        case BLE : test_ble();
            break;

        case DISPLAY: test_display();
            break;
        
        case SYSTICK : test_systick();
            break;

        case I2C_NB : test_i2c_nb();
            break;

        case CALLBACK : test_callback();
            break;
        
        case METEO : station_main();
        
        default: blink_led(); // run only on pico
            
    }

    return 0;
}