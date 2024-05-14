/*
 * lcd.h
 *
 *  Created on: 22 févr. 2022
 *      Author: gael
 */

#ifndef LCD_H_
#define LCD_H_

#include "../board.h"

#include "../font/font.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/timer.h"

#include <string.h>

#define LCD_SPI_MISO_GPIO		0 // pin 2
#define LCD_SPI_MOSI_GPIO		3 // pin 5
#define LCD_SPI_SCK_GPIO		2 // pin 4
#define LCD_SPI_CS_GPIO			1 // pin 3


#define LCD_DC_GPIO				6 // pin 8

#define V_SCROLL_DEF		0x33
#define MADCTL				0x36
#define V_SCROLL_START_ADDR	0x37

#define LCD_Y	240
#define LCD_X	320

#define LCD_BLUE    		(0x1F<<0)
#define LCD_LIGHT_BLUE		0x7FF
#define LCD_GREEN 			(0x0F<<5)
#define LCD_LIGHT_GREEN 	(0x3F << 5) | 0xA
#define LCD_RED     		(0x1f<<11)
#define LCD_ORANGE			0xFBE0
#define LCD_YELLOW			0xFFC0
#define LCD_WHITE 			0xFFFF
#define LCD_BLACK 			0

#define FONT_W(tab)			tab[0]
#define FONT_NB_V_L_SMALL	12
#define FONT_NB_V_L_BIG		32
#define FONT_H(tab)			tab[1]
#define FONT_OFF(tab)		tab[2]
#define FONT_QTY(tab)		tab[3]

typedef struct _pixel{
	int x;
	int y;
	uint16_t color;
} pixel;

typedef struct {
	uint16_t top;
	uint16_t bottom;
	uint16_t screen_line;
	uint16_t screen_y;
} lcd_scroll_param_t;


extern lcd_scroll_param_t scrolling;

void lcd_spi_config();

void lcd_init();
void lcd_config(void);

void lcd_write_Cmd(uint8_t cmd);
void lcd_write_Data(uint8_t data);
void lcd_write_Data16(uint16_t data);

void lcd_backlight_off();
void lcd_backlight_on();

void lcd_clear(uint16_t color);

void lcd_set_zone(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2);
void lcd_set_pixel(uint16_t x, uint16_t y, uint16_t color);

void lcd_fill_rect(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t color);
void lcd_rect( uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t color );

void lcd_v_line(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color);
void lcd_h_line(uint16_t x1, uint16_t x2, uint16_t y, uint16_t color);

void lcd_draw_circle(uint16_t cx, uint16_t cy, uint16_t r, uint16_t color);

void lcd_draw_char(char c, uint16_t x, uint16_t y, uint16_t color, fontdatatype* t);
void lcd_draw_string(char* s, uint16_t x, uint16_t y, uint16_t color, fontdatatype* t);
void lcd_print_double( double v, uint16_t x, uint16_t y, uint16_t color, fontdatatype* t );
void lcd_print_int( int v, uint16_t x, uint16_t y, uint16_t color, fontdatatype* t );

void lcd_v_scroll( uint16_t nb_pix );
void lcd_v_scroll_config( uint16_t top_height, uint16_t scroll_area_height ,uint16_t bottom_height );
void lcd_scroll_init( uint16_t top, uint16_t core, uint16_t bottom );
void lcd_reset_scrolling();
void lcd_scroll();

#endif
