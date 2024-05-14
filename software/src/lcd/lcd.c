/*
 * lcd.c
 *
 *  Created on: 22 févr. 2022
 *      Author: gael
 */

#include "lcd.h"


lcd_scroll_param_t scrolling;

void lcd_backlight_off() {
	gpio_put( LCD_BACKLIGHT_GPIO, 0 );
}

void lcd_backlight_on() {
	gpio_put( LCD_BACKLIGHT_GPIO, 1 );
}

void lcd_spi_config() {
	gpio_set_function( LCD_SPI_MISO_GPIO, GPIO_FUNC_SPI );
	gpio_set_function( LCD_SPI_MOSI_GPIO, GPIO_FUNC_SPI );
	gpio_set_function( LCD_SPI_SCK_GPIO, GPIO_FUNC_SPI );

	gpio_init( LCD_SPI_CS_GPIO );
	gpio_set_dir( LCD_SPI_CS_GPIO, GPIO_OUT );
	//LCS_CS actif bas => initialisation à 0 pour le garder actif (seul sur ce port SPI)
	gpio_put( LCD_SPI_CS_GPIO, 0 );

	//initialisation de SPI0 à 10MHz => à revoir.
	spi_init( spi0, 10000*10000 );
}

void lcd_init(){
	lcd_spi_config();

	gpio_init( LCD_DC_GPIO );
	gpio_set_dir( LCD_DC_GPIO, GPIO_OUT );
	gpio_put( LCD_DC_GPIO, 0 );

	lcd_config();
	lcd_clear( LCD_BLACK );	
}

void lcd_config() {
	lcd_write_Cmd(0x01); //software reset
	sleep_ms( 5 );

	lcd_write_Cmd(0x11);
	sleep_ms( 120 );

 	lcd_write_Cmd(0xCF);
	lcd_write_Data(0x00);
	lcd_write_Data(0x83);
	lcd_write_Data(0X30);

 	lcd_write_Cmd(0xED);
	lcd_write_Data(0x64);
	lcd_write_Data(0x03);
	lcd_write_Data(0X12);
	lcd_write_Data(0X81);

 	lcd_write_Cmd(0xE8);
	lcd_write_Data(0x85);
	lcd_write_Data(0x01);
	lcd_write_Data(0x79);

 	lcd_write_Cmd(0xCB);
	lcd_write_Data(0x39);
	lcd_write_Data(0x2C);
	lcd_write_Data(0x00);
	lcd_write_Data(0x34);
	lcd_write_Data(0x02);

 	lcd_write_Cmd(0xF7);
	lcd_write_Data(0x20);

 	lcd_write_Cmd(0xEA);
	lcd_write_Data(0x00);
	lcd_write_Data(0x00);


 	lcd_write_Cmd(0xC1);    //Power control
	lcd_write_Data(0x11);   //SAP[2:0];BT[3:0]

 	lcd_write_Cmd(0xC5);    //VCM control 1
	lcd_write_Data(0x34);
	lcd_write_Data(0x3D);

 	lcd_write_Cmd(0xC7);    //VCM control 2
	lcd_write_Data(0xC0);

 	lcd_write_Cmd(0x36);    // Memory Access Control
	lcd_write_Data(0x08);

 	lcd_write_Cmd(0x3A);   	 // Pixel format
	lcd_write_Data(0x55);  //16bit

 	lcd_write_Cmd(0xB1);   	   // Frame rate
	lcd_write_Data(0x00);
	lcd_write_Data(0x1D);  //65Hz

 	lcd_write_Cmd(0xB6);    // Display Function Control
	lcd_write_Data(0x0A);
	lcd_write_Data(0xA2);
	lcd_write_Data(0x27);
	lcd_write_Data(0x00);

	lcd_write_Cmd(0xb7); //Entry mode
	lcd_write_Data(0x07);


 	lcd_write_Cmd(0xF2);    // 3Gamma Function Disable
	lcd_write_Data(0x08);

 	lcd_write_Cmd(0x26);    //Gamma curve selected
	lcd_write_Data(0x01);


	lcd_write_Cmd(0xE0); //positive gamma correction
	lcd_write_Data(0x1f);
	lcd_write_Data(0x1a);
	lcd_write_Data(0x18);
	lcd_write_Data(0x0a);
	lcd_write_Data(0x0f);
	lcd_write_Data(0x06);
	lcd_write_Data(0x45);
	lcd_write_Data(0x87);
	lcd_write_Data(0x32);
	lcd_write_Data(0x0a);
	lcd_write_Data(0x07);
	lcd_write_Data(0x02);
	lcd_write_Data(0x07);
	lcd_write_Data(0x05);
	lcd_write_Data(0x00);

	lcd_write_Cmd(0xE1); //negamma correction
	lcd_write_Data(0x00);
	lcd_write_Data(0x25);
	lcd_write_Data(0x27);
	lcd_write_Data(0x05);
	lcd_write_Data(0x10);
	lcd_write_Data(0x09);
	lcd_write_Data(0x3a);
	lcd_write_Data(0x78);
	lcd_write_Data(0x4d);
	lcd_write_Data(0x05);
	lcd_write_Data(0x18);
	lcd_write_Data(0x0d);
	lcd_write_Data(0x38);
	lcd_write_Data(0x3a);
	lcd_write_Data(0x1f);

 	lcd_write_Cmd(0x11);    //Exit Sleep
	sleep_ms( 120 );
 	lcd_write_Cmd(0x29);    //Display on
	sleep_ms( 50 );
}

void lcd_write_Cmd(uint8_t cmd) { // D/CX = 0 -> transfert de commande
	gpio_put( LCD_DC_GPIO, 0 );
	spi_write_blocking( spi0, &cmd, 1 );
}

void lcd_write_Data(uint8_t data){ // D/CX = 1 // transfert de Data
	gpio_put( LCD_DC_GPIO, 1 );
	spi_write_blocking( spi0, &data, 1 );
}


void lcd_draw_char(char c, uint16_t x, uint16_t y, uint16_t color, fontdatatype* t){
	if ( t == SmallFont ) {
		int index = ( (int)c - FONT_OFF(t) ) * FONT_H(t) + 3 + 1;
		for(int i = 0; i < FONT_H(t); i ++){
			uint8_t l = t[index + i];
			for(int j = 0; j < FONT_W(t); j++) {
				if( l & ( 1 << (FONT_W(t)-j-1) ) )	lcd_set_pixel( x+j , y+i, color);
			}
		}
	}
	else if ( t == BigFont ){
		int index = ( (int)c - FONT_OFF(t) ) * 32 + 3 + 1;
		for(int i = 0; i < FONT_H(t); i ++){
			uint8_t l = t[index + 2*i];
			for(int j = 0; j < 8; j++) {
				if( l & ( 1 << (8-j-1) ) )	lcd_set_pixel( x+j , y+i, color);
			}
			l = t[index + 2*i + 1];
			for(int j = 0; j < 8; j++) {
				if( l & ( 1 << (8-j-1) ) )	lcd_set_pixel( x+j+8 , y+i, color);
			}
		}
	}
}

void lcd_draw_string(char* s, uint16_t x, uint16_t y, uint16_t color, fontdatatype* t) {
	int i = 0;
	while( s[i] != '\0' ){
		lcd_draw_char(s[i], x, y, color, t);
		i ++;
		x += FONT_W(t);
	}
}

void lcd_print_int( int v, uint16_t x, uint16_t y, uint16_t color, fontdatatype* t ) {
	char value[25];
	sprintf(value, "%d", v);
	lcd_draw_string( value, x, y, color, t);
}

void lcd_print_double( double v, uint16_t x, uint16_t y, uint16_t color, fontdatatype* t ) {
	char value[25];
	sprintf(value, "%0.2f", (float)v);
	lcd_draw_string( value, x, y, color, t);
}


void lcd_write_Data16(uint16_t data){
	lcd_write_Data( data >> 8 );
	lcd_write_Data( data );
}

void lcd_set_zone(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2) {
	lcd_write_Cmd(0x2A);
	lcd_write_Data16(LCD_Y-y2);
	lcd_write_Data16(LCD_Y-y1);

	lcd_write_Cmd(0x2B);
	lcd_write_Data16(x1);
	lcd_write_Data16(x2);
}

void lcd_clear(uint16_t color){
	lcd_set_zone(0, LCD_X, 0, LCD_Y);
	lcd_write_Cmd(0x2C);
	for(int i = 0; i<LCD_Y; i++){
		for(int j = 0; j<LCD_X; j++) {
			lcd_write_Data16(color);
		}
	}
}

void lcd_set_pixel(uint16_t x, uint16_t y, uint16_t color){
	lcd_set_zone( x, x, y, y );
	lcd_write_Cmd(0x2C);
	lcd_write_Data16(color);
}

void lcd_draw_circle(uint16_t cx, uint16_t cy, uint16_t r ,uint16_t color){
	uint16_t x, y, y_abs, x_abs;
	for(int x = cx-r; x < cx + r; x++){
		y_abs = sqrt( (double)( (r*r) - ( (x - cx)*(x - cx) ) ) );
		y = y_abs + cy;
		if( x > -1 && x < LCD_X && y > -1 && y < LCD_Y) {
			lcd_set_pixel(x,y,color);
		}
		y = -y_abs + cy;
		if( x > -1 && x < LCD_X && y > -1 && y < LCD_Y) {
			lcd_set_pixel(x,y,color);
		}
	}

	for(int y = cy-r; y < cy + r; y++){
		x_abs = sqrt( (double)( (r*r) - ( (y - cy)*(y - cy) ) ) );
		x = x_abs + cx;
		if( x > -1 && x < LCD_X && y > -1 && y < LCD_Y) {
			lcd_set_pixel(x,y,color);
		}
		x = -x_abs + cx;
		if( x > -1 && x < LCD_X && y > -1 && y < LCD_Y) {
			lcd_set_pixel(x,y,color);
		}
	}

}

void lcd_fill_rect(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t color) {
	lcd_set_zone(x1, x2, y1, y2);
	lcd_write_Cmd(0x2C);
	for(int i = 0; i <= (x2 - x1); i++){
		for(int j = 0; j <= (y2 - y1); j++) {
			lcd_write_Data16(color);
		}
	}
}

void lcd_rect( uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t color ) {
	lcd_v_line(x1, y1, y2, color);
	lcd_v_line(x2, y1, y2, color);
	lcd_h_line(x1, x2, y1, color);
	lcd_h_line(x1, x2, y2, color);
}

void lcd_h_line(uint16_t x1, uint16_t x2, uint16_t y, uint16_t color){
	lcd_set_zone(x1, x2, y, y);
	lcd_write_Cmd(0x2C);
	for(int j = 0; j < (x2 - x1); j++) {
		lcd_write_Data16(color);
	}
}

void lcd_v_line(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color){
	if( y1 == y2 ) lcd_set_pixel( y1, x, color );
	else {
		lcd_set_zone( x, x, ( y1 < y2) ? y1 : y2 , ( y1 < y2 ) ? y2 : y1 );
		lcd_write_Cmd(0x2C);
		int L = ( y2 > y1 ) ? y2 - y1 : y1 - y2;
		for(int j = 0; j < L; j++) {
			lcd_write_Data16(color);
		}
	}
}

void lcd_v_scroll_config( uint16_t top_height, uint16_t scroll_area_height ,uint16_t bottom_height ) {
	lcd_write_Cmd(V_SCROLL_DEF);
	lcd_write_Data16( top_height );
	lcd_write_Data16( scroll_area_height );
	lcd_write_Data16( bottom_height );
}

void lcd_scroll_init( uint16_t top, uint16_t core, uint16_t bottom ) {
	scrolling.top = top;
	scrolling.bottom = LCD_Y-bottom-1;
	scrolling.screen_line = scrolling.top;
	scrolling.screen_y = scrolling.bottom;
	lcd_v_scroll_config( scrolling.top-1, core, bottom);
}

void lcd_v_scroll( uint16_t nb_pix ){
	lcd_write_Cmd(V_SCROLL_START_ADDR);
	lcd_write_Data16( nb_pix );
}

void lcd_reset_scrolling() {
	while( scrolling.screen_line != scrolling.top ) {
		lcd_v_scroll( scrolling.screen_line );
		scrolling.screen_line += 1;
		scrolling.screen_y += 1;
	}
}

void lcd_scroll(){
	lcd_v_scroll( scrolling.screen_line );
	scrolling.screen_line = ( scrolling.screen_line == scrolling.bottom ) ? scrolling.top-1 : scrolling.screen_line + 1;
	scrolling.screen_y = ( scrolling.screen_y == scrolling.bottom ) ? scrolling.top-1 : scrolling.screen_y + 1;
}




