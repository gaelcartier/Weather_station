#ifndef _STATION_H_
#define _STATION_H_

#include <stdio.h>
#include "pico/stdlib.h"


#include "../board.h"

#include "../lcd/lcd.h"
#include "../touchscreen/touchscreen.h"
#include "../bme280/bme280.h"
#include "../veml7700/veml7700.h"
#include "../led_rgb/led_rgb.h"
#include "../RN4870/RN4870.h"


void station_reset();
void station_init();
void station_disable_ble();
void station_enable_ble();
void station_main();
void station_init_i2c_sensor();

#endif