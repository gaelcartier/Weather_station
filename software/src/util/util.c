#include "util.h"

void gpio_initialize_out( uint gpio, bool state ) {
    gpio_init( gpio );
    gpio_set_dir( gpio, GPIO_OUT );
    gpio_put( gpio, state );
}

void gpio_initialize_in( uint gpio ) {
    gpio_init( gpio );
    gpio_set_dir( gpio, GPIO_IN );
}

void stdin_read( char* buffer ) {
    int ind = 0;
    int reading = 1;
    int c = '\0';

    while( reading ) {
        c = getchar_timeout_us( 1 );
        if( c == '\r') {
            printf("\n");
            buffer[ ind ] = '\0';
            reading = 0;
        }
        else if( c >= 0 ) {
            printf("%c",(char)c);
            buffer[ ind ] = (char)c;
            ind ++;
        }
    }
}