/*
 * lcd.h
 *
 *  Created on: 22 févr. 2022
 *      Author: gael
 */

#ifndef _LED_RGB_H_
#define _LED_RGB_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

/*
La led rgb sur ce circuit partage le port SPI_1 avec le lecteur de carte SD. La led n'ayant pas de pin CS, le choix entre
les deux périphériques se fait en utilisant deux pins distincts pour chacun pour les clocks.
*/

#define LED_RGB_SPI_INST			spi1
#define LED_RGB_SPI_MOSI_GPIO		11 // pin 14
#define LED_RGB_SPI_SCK_GPIO		14 // pin 17
#define SD_SPI_SCK_GPIO				10 // pin 13

#define LED_RGB_START_FRAME			0x00000000
#define LED_RGB_STOP_FRAME			0xFFFFFFFF
// #define LED_RGB_CLR( l, r, g, b)	( (uint32_t)( (uint8_t)((0b111 << 5)) | (l & 0x1F) ) << 24 | (uint32_t) ( b << 16 )  | (uint32_t)( g << 8 ) | (uint32_t) r ) // l : "light" -> brightness
#define LED_RGB_CLR( l, r, g, b)	( (uint32_t)( (uint8_t)( (0b111 << 5) | (l & 0x1F) ) ) | (uint32_t) ( b << 16 )  | (uint32_t)( g << 24 ) | (uint32_t)( r << 8 ) ) // l : "light" -> brightness

#define LED_OFF     LED_RGB_CLR( 0, 0, 0, 0 )
#define LED_BLUE    LED_RGB_CLR( 50, 0, 0, 50 )
#define LED_GREEN   LED_RGB_CLR( 50, 0, 50, 0 ) 
#define LED_RED     LED_RGB_CLR( 50, 50, 0, 0 )

/*

FAIRE UNE LIBRAIRIE PROPRE AUX PROTOCOLES SPI ET I2C POUR NE PAS LES INITIALISER 2 FOIS A CHAQUE INIT DES PERIPHERIQUES

*/

void led_rgb_spi_config();
void led_rgb_init();
void led_rgb_write_clr( uint32_t color );
void led_rgb_write_clr_lrgb( uint8_t l, uint8_t r, uint8_t g, uint8_t b );


#endif
