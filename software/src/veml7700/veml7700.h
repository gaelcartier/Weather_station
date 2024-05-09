/*
 * light_sensor.h
 * ALS : Ambiant Light Sensor
 *  Created on: 2 juin 2022
 *      Author: gael
 */

#ifndef _VEML7700_H_
#define _VEML7700_H_


#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"


#define VEML7700_I2C_ADDR			0x10
#define VEML7700_I2C_INST			i2c1
#define VEML7700_I2C_SCL_GPIO		19 // pin 30
#define VEML7700_I2C_SDA_GPIO		18 // pin 29

#define VEML7700_CONF				0x00
#define VEML7700_WH					0x01
#define VEML7700_WL					0x02
#define VEML7700_AMBIENT			0x04
#define VEML7700_WHITE				0x05
#define VEML7700_INT				0x06

#define VEML7700_MAX				110000
#define VEML7700_MIN				0

#define VEML7700_OFF					(1 << 0)
#define VEML7700_ON					(0 << 0)
#define VEML7700_INT_ON				(1 << 1)
#define VEML7700_INT_OFF				(0 << 0)
#define VEML7700_GAIN_1_X			( 0b00 << 11 )
#define VEML7700_GAIN_2_X			( 0b01 << 11 )
#define VEML7700_INTEGRATION_100_ms	( 0b0000 << 6 )

#define VEML7700_SUNNY				20000
#define VEML7700_NIGHT				10

#define VEML7700_CALLBACK_GET			0x200
#define VEML7700_CALLBACK_READ			0x201

#define VEML7700_CAN_LIGHT				0x08


typedef struct {
	uint16_t ambient_light;
	uint16_t white_light;
} veml7700_data_t;


void VEML7700_i2c_config();
void VEML7700_config();
void VEML7700_init();
veml7700_data_t VEML7700_read();

#endif 
