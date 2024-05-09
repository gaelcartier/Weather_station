/*
 * weather_sensor_bme280.c
 *
 *  Created on: 7 juin 2022
 *      Author: gael
 */


#include "bme280.h"

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;

uint16_t dig_P1;
int16_t dig_P2;
int16_t dig_P3;
int16_t dig_P4;
int16_t dig_P5;
int16_t dig_P6;
int16_t dig_P7;
int16_t dig_P8;
int16_t dig_P9;

uint8_t dig_H1;
int16_t dig_H2;
uint8_t dig_H3;
int16_t dig_H4;
int16_t dig_H5;
int8_t dig_H6;


int32_t t_fine;
bme_280_data_t bme_data;

void BME280_i2c_config() {
	i2c_init( BME_I2C_INST, 100*1000 );

	gpio_set_function( BME_I2C_SCL_GPIO, GPIO_FUNC_I2C );
	gpio_set_function(BME_I2C_SDA_GPIO, GPIO_FUNC_I2C );

	// gpio_pull_up( BME_I2C_SCL_GPIO ); // si nécéssaire ... ( car absent sur le circuit ou disfonctionnement random )
	// gpio_pull_up( BME_I2C_SDA_GPIO );
}

void BME280_config() {
	BME280_init_calib();
	BME280_set_config( BME_FILTER_OFF, BME_t_1s );
	BME280_set_ctrl_hum( BME_OSRS_1X );
	BME280_set_ctrl_meas( BME_OSRS_1X, BME_OSRS_1X, BME_NORMAL_MODE ); // Set normal mode at the end to be able to config other register before
}

void BME280_init() {
	BME280_i2c_config();
	BME280_config();
}

void BME280_init_calib() {

	uint8_t calib_buf[26];
	
	uint8_t calib_1 = BME_CALIB_1;
	i2c_write_blocking( BME_I2C_INST, BME_I2C_ADDR, &calib_1, 1, true); // true : on conserve le contrôle du bus
	i2c_read_blocking( BME_I2C_INST, BME_I2C_ADDR, calib_buf, 26, false ); // false : communication terminée, on rend le bus.

	dig_T1 = BME_CONCAT_BYTES(calib_buf[1], calib_buf[0]);
	dig_T2 = (int16_t)BME_CONCAT_BYTES(calib_buf[3],  calib_buf[2]);
	dig_T3 = (int16_t)BME_CONCAT_BYTES(calib_buf[5],  calib_buf[4]);
	dig_P1 = (int16_t)BME_CONCAT_BYTES(calib_buf[7],  calib_buf[6]);
	dig_P2 = (int16_t)BME_CONCAT_BYTES(calib_buf[9],  calib_buf[8]);
	dig_P3 = (int16_t)BME_CONCAT_BYTES(calib_buf[11], calib_buf[10]);
	dig_P4 = (int16_t)BME_CONCAT_BYTES(calib_buf[13], calib_buf[12]);
	dig_P5 = (int16_t)BME_CONCAT_BYTES(calib_buf[15], calib_buf[14]);
	dig_P6 = (int16_t)BME_CONCAT_BYTES(calib_buf[17], calib_buf[16]);
	dig_P7 = (int16_t)BME_CONCAT_BYTES(calib_buf[19], calib_buf[18]);
	dig_P8 = (int16_t)BME_CONCAT_BYTES(calib_buf[21], calib_buf[20]);
	dig_P9 = (int16_t)BME_CONCAT_BYTES(calib_buf[23], calib_buf[22]);
	dig_H1 = calib_buf[25];

	uint8_t calib_2 = BME_CALIB_2;
	i2c_write_blocking( BME_I2C_INST, BME_I2C_ADDR, &calib_2, 1, true); // true : on conserve le contrôle du bus
	i2c_read_blocking( BME_I2C_INST, BME_I2C_ADDR, calib_buf, 7, false ); // false : communication terminée, on rend le bus.

	dig_H2 = (int16_t)BME_CONCAT_BYTES(calib_buf[1], calib_buf[0]);
	dig_H3 = calib_buf[2];
	dig_H4 = ((int16_t)((int8_t)(calib_buf[3]))*16) | (int16_t)(calib_buf[4] & 0x0F);
	dig_H5 = ((int16_t)((int8_t)(calib_buf[5]))*16) | (int16_t)(calib_buf[4] >> 4);
	dig_H6 = (int8_t)calib_buf[6];
}

void BME280_set_ctrl_hum( uint8_t osrs_hum ) {
	uint8_t hum_conf[2] = { BME_CTRL_HUM,  osrs_hum };
	i2c_write_blocking( BME_I2C_INST, BME_I2C_ADDR, hum_conf, 2, false);
}

void BME280_set_ctrl_meas( uint8_t osrs_t, uint8_t osrs_p, uint8_t mode ) {
	uint8_t ctrl_conf[2] = { BME_CTRL_MEAS, (uint8_t)( (osrs_t << 5) | (osrs_p << 2) | mode ) };
	i2c_write_blocking( BME_I2C_INST, BME_I2C_ADDR, ctrl_conf, 2, false);
}

void BME280_set_config( uint8_t filter,  uint8_t standby_time ) {
	uint8_t config_conf[2] = { BME_CONFIG, (uint8_t)( 0x0 | (filter << 2) | (standby_time << 5) ) };
	i2c_write_blocking( BME_I2C_INST, BME_I2C_ADDR, config_conf, 2, false);
}

void BME280_get_id() {
	uint8_t id_buf;
	uint8_t bme_id = BME_ID;
	i2c_write_blocking( BME_I2C_INST, BME_I2C_ADDR, &bme_id, 1, true); 
	i2c_read_blocking( BME_I2C_INST, BME_I2C_ADDR, &id_buf, 1, false );
	printf("\nid= %d\n", id_buf);
}

void BME280_reset(){
	uint8_t bme_reset[2] = {BME_RESET, BME_RESET_VALUE};
	i2c_write_blocking( BME_I2C_INST, BME_I2C_ADDR, bme_reset, 2, false); 
}

bme_280_data_t BME280_read() {
	bme_280_data_t data;
	uint8_t data_buf[8];
	uint8_t weather_target = BME_PRESS;
	i2c_write_blocking( BME_I2C_INST, BME_I2C_ADDR, &weather_target, 1, true); 
	i2c_read_blocking( BME_I2C_INST, BME_I2C_ADDR, data_buf, 8, false );
	uint32_t tmp_press = ( data_buf[0] << 12) | (data_buf[1] << 4) | ((data_buf[2] >> 4) & 0xF);
	uint32_t tmp_temp = (data_buf[3] << 12) | (data_buf[4] << 4) | ((data_buf[5] >> 4) & 0xF);
	uint16_t tmp_hum = (data_buf[6] << 8) | data_buf[7];
	data.temperature = (float)BME280_compensate_T( (int32_t)tmp_temp );
	data.pressure = ((float)BME280_compensate_P( (int32_t)tmp_press ) )/100.0;
	data.humidity = (float)BME280_compensate_H( (int32_t)tmp_hum );
	return data;
}



/*
 *  From BME280 datasheet
 */

// Returns temperature in DegC, double precision. Output value of “51.23” equals 51.23 DegC.
// t_fine carries fine temperature as global value
double BME280_compensate_T( int32_t adc_T)
{
	double temperature_min = -40;
	double temperature_max = 85;
	double var1, var2, T;
	var1 = (((double)adc_T)/16384.0 - ((double)dig_T1)/1024.0) * ((double)dig_T2);
	var2 = ((((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0) * (((double)adc_T)/131072.0 - ((double) dig_T1)/8192.0)) * ((double)dig_T3);
	t_fine = (int32_t)(var1 + var2);
	T = (var1 + var2) / 5120.0;
	if ( T < temperature_min) {
		T = temperature_min;
	}
	else if ( T > temperature_max) {
		T = temperature_max;
	}
	return T;
}

// Returns pressure in Pa as double. Output value of “96386.2” equals 96386.2 Pa = 963.862 hPa
double BME280_compensate_P( int32_t adc_P) {
	double var1, var2, p;
	var1 = ((double)t_fine/2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2/4.0)+(((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)dig_P1);
	if (var1 == 0.0) {
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576.0 - (double)adc_P;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double)dig_P7)) / 16.0;
	return p;
}

// Returns humidity in %rH as as double. Output value of “46.332” represents 46.332 %rH
double BME280_compensate_H( int32_t adc_H) {
	double var_H;
	var_H = (((double)t_fine) - 76800.0);
	var_H = (adc_H - (((double)dig_H4) * 64.0 + ((double)dig_H5) / 16384.0 * var_H)) * (((double)dig_H2) / 65536.0 * (1.0 + ((double)dig_H6) / 67108864.0 * var_H * (1.0 + ((double)dig_H3) / 67108864.0 * var_H)));
	var_H = var_H * (1.0 - ((double)dig_H1) * var_H / 524288.0);
	if (var_H > 100.0)
		var_H = 100.0;
	else if (var_H < 0.0)
		var_H = 0.0;
	return var_H;
}

