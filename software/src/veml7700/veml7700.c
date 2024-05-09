/*
 * light_sensor.c
 *
 *  Created on: 2 juin 2022
 *      Author: gael
 */

#ifndef _SENSOR_C_
#define _SENSOR_C_

#include "veml7700.h"


void VEML7700_i2c_config() {
	i2c_init( VEML7700_I2C_INST, 100*1000 );

	gpio_set_function( VEML7700_I2C_SCL_GPIO, GPIO_FUNC_I2C );
	gpio_set_function( VEML7700_I2C_SDA_GPIO, GPIO_FUNC_I2C );

	// gpio_pull_up( VEML7700_I2C_SCL_GPIO ); // si nécéssaire ... ( car absent sur le circuit ou disfonctionnement random )
	// gpio_pull_up( VEML7700_I2C_SDA_GPIO );
}

void VEML7700_config() {
	uint16_t config_value = 0x0 | VEML7700_GAIN_2_X | VEML7700_INTEGRATION_100_ms | VEML7700_INT_OFF | VEML7700_ON;
	uint8_t config[3] = { VEML7700_CONF, config_value & 0xF, config_value << 8 };
	i2c_write_blocking( VEML7700_I2C_INST, VEML7700_I2C_ADDR, config, 3, false);
}

void VEML7700_init() {
	VEML7700_i2c_config();
	VEML7700_config();
}

veml7700_data_t VEML7700_read() {
	uint8_t data_buf[4];
	veml7700_data_t data;
	uint8_t reg_addr = VEML7700_AMBIENT;
	i2c_write_blocking( VEML7700_I2C_INST, VEML7700_I2C_ADDR, &reg_addr, 1, true); 
	i2c_read_blocking( VEML7700_I2C_INST, VEML7700_I2C_ADDR, data_buf, 4, false );
	data.ambient_light = ( data_buf[0] | (data_buf[1] << 8) );
	data.white_light = ( data_buf[2] | (data_buf[3] << 8) );
	return data;
}


#endif 
