/*
 * weather_sensor_bme280.h
 *
 *  Created on: 7 juin 2022
 *      Author: gael
 */

#ifndef _BME280_H_
#define _BME280_H_


#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"


#define BME_I2C_ADDR			0x76 // With SDO on GND
//#define BME_I2C_ADDR			0x77 // With SDO on VDD

#define BME_I2C_INST			i2c1
#define BME_I2C_SCL_GPIO		19 // pin 30
#define BME_I2C_SDA_GPIO		18 // pin 29

#define BME_CONCAT_BYTES(msb, lsb)		(((uint16_t)msb << 8) | (uint16_t)lsb)

#define BME_ID				0xD0
#define BME_RESET			0xE0
#define BME_RESET_VALUE		0xB6

#define BME_STATUS			0xF3

#define BME_HUM				0xFD
#define BME_TEMP			0xFA
#define BME_PRESS			0xF7

#define BME_CONFIG			0xF5
#define BME_CTRL_MEAS		0xF4
#define BME_CTRL_HUM		0xF2

#define BME_CALIB_1			0x88
#define BME_CALIB_2			0xE1

#define BME_SLEEP_MODE		0b00
#define BME_NORMAL_MODE		0b11
#define BME_FORCE_MODE		0b01

#define BME_t_0_25s			0b011
#define BME_t_0_5s			0b100
#define BME_t_1s			0b101

#define BME_FILTER_OFF		0b000
#define BME_FILTER_2		0b001
#define BME_FILTER_4		0b010
#define BME_FILTER_8		0b011
#define BME_FILTER_16		0b100

#define BME_OSRS_1X			0b001		// Oversampling => Réduction du bruit (rapport SNR)
#define BME_OSRS_2X			0b010
#define BME_OSRS_4X			0b011
#define BME_OSRS_8X			0b100
#define BME_OSRS_16X		0b101

#define BME_MAX_TEMP		80.0
#define BME_MIN_TEMP		-40.0

#define BME_MAX_PRESS		1100.0
#define BME_MIN_PRESS		300.0

#define BME_MAX_HUM			100.0
#define BME_MIN_HUM			0.0

#define BME_TEMP_COLD		10
#define BME_TEMP_WARM		25

#define BME_HUM_DRY			25
#define BME_HUM_HUM			70

#define BME_PRESS_NICE		1030
#define BME_PRESS_RAINY		990



typedef struct {
	float pressure;
	float temperature;
	float humidity;
} bme_280_data_t;


extern bme_280_data_t bme_data;

void BME280_i2c_config();
void BME280_config();
void BME280_init();
void BME280_init_calib();

void BME280_set_ctrl_hum( uint8_t osrs_hum );
void BME280_set_ctrl_meas( uint8_t osrs_t, uint8_t osrs_p, uint8_t mode );
void BME280_set_config( uint8_t filter,  uint8_t standby_time );

void BME280_get_id();
void BME280_reset();

bme_280_data_t BME280_read();




/*
 *  From BME280 datasheet
 */

double BME280_compensate_T( int32_t adc_T);
double BME280_compensate_P( int32_t adc_P);
double BME280_compensate_H( int32_t adc_H);


#endif /* SRC_WEATHER_SENSOR_BME280_H_ */
