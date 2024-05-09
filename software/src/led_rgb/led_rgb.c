
#include "led_rgb.h"


void led_rgb_spi_config() {
	// initialisation de SPI0 à 5MHz => à revoir. AVOIR UNE FREQUENCE COMPATIBLE AVEC LE PROTOCOLE DE LA CARTE SD.
	spi_init( LED_RGB_SPI_INST, 5000*1000 );
	gpio_set_function( LED_RGB_SPI_MOSI_GPIO, GPIO_FUNC_SPI );
}


void led_rgb_init() {
	led_rgb_spi_config();
}

void led_rgb_write_clr( uint32_t color ) {
	if( gpio_get_function( LED_RGB_SPI_SCK_GPIO ) != GPIO_FUNC_SPI ) gpio_set_function( LED_RGB_SPI_SCK_GPIO, GPIO_FUNC_SPI );
	uint32_t cmd[3] = { LED_RGB_START_FRAME, color, LED_RGB_STOP_FRAME };
	spi_write_blocking( LED_RGB_SPI_INST, (uint8_t*)cmd, 12 );
}

void led_rgb_write_clr_lrgb( uint8_t l, uint8_t r, uint8_t g, uint8_t b ) {
	if( gpio_get_function( LED_RGB_SPI_SCK_GPIO ) != GPIO_FUNC_SPI ) gpio_set_function( LED_RGB_SPI_SCK_GPIO, GPIO_FUNC_SPI );
	uint32_t color[3] = { LED_RGB_START_FRAME, LED_RGB_CLR(l, r, g, b), LED_RGB_STOP_FRAME };
	spi_write_blocking( LED_RGB_SPI_INST, (uint8_t*)color, 12 );
}

