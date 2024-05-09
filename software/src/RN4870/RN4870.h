#ifndef _RN4870_H_
#define _RN4870_H_



#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/timer.h"

#include "../util/util.h"

#include <string.h>

#define BLE_UART_INST           uart1
#define BLE_GPIO_UART_TX        24
#define BLE_GPIO_UART_RX        25
#define BLE_GPIO_UART_RTS       23
#define BLE_GPIO_UART_CTS       26

#define BLE_GPIO_ENABLE         29
#define BLE_GPIO_TX_IND         28
#define BLE_GPIO_RX_IND         17
#define BLE_GPIO_STAT_1         27
#define BLE_GPIO_STAT_2         22
#define BLE_GPIO_MODE           21
#define BLE_GPIO_LINK_DROP      20
#define BLE_GPIO_PAIRING_KEY    16

extern uint BLE_DATA_RECEIVED;

void RN4870_uart_config();

void RN4870_init();

void RN4870_write( uint8_t* data );
void RN4870_read( uint8_t* buffer );

void RN4870_enable_tx_irq();
void ble_irq_callback();


#endif
