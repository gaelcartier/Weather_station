
#include "RN4870.h"

uint BLE_DATA_RECEIVED = 0;

void RN4870_uart_config(){
    gpio_set_function( BLE_GPIO_UART_TX, GPIO_FUNC_UART );
    gpio_set_function( BLE_GPIO_UART_RX, GPIO_FUNC_UART );
    gpio_set_function( BLE_GPIO_UART_RTS, GPIO_FUNC_UART );
    gpio_set_function( BLE_GPIO_UART_CTS, GPIO_FUNC_UART );

    uart_init( BLE_UART_INST, 115200 );
}

void RN4870_init() {
    RN4870_uart_config();

    gpio_initialize_out( BLE_ENABLE_GPIO, 1 );
    gpio_initialize_out( BLE_GPIO_LINK_DROP, 1);
    gpio_initialize_out( BLE_GPIO_MODE, 1);
    gpio_initialize_out( BLE_GPIO_PAIRING_KEY, 1);
    gpio_initialize_out( BLE_GPIO_RX_IND, 1);

    gpio_initialize_in( BLE_GPIO_STAT_1 );
    gpio_initialize_in( BLE_GPIO_STAT_2 );
    gpio_initialize_in( BLE_GPIO_TX_IND );

    RN4870_enable_tx_irq();
}

void RN4870_write( uint8_t* data ) {
    uart_write_blocking( BLE_UART_INST, data, strlen(data) );
    sleep_ms( 100 );
    printf("cmd : %s sent\n", (char*)data );
}

void RN4870_read( uint8_t* buffer ) {
    while ( uart_is_readable( BLE_UART_INST ) ) *buffer++ = (uint8_t) uart_get_hw( BLE_UART_INST )->dr;
    BLE_DATA_RECEIVED = 0;
}

void ble_irq_callback() {
    BLE_DATA_RECEIVED = 1;
}

void RN4870_enable_tx_irq() {
	gpio_set_irq_enabled_with_callback( BLE_GPIO_TX_IND, GPIO_IRQ_EDGE_FALL, true, &ble_irq_callback );
}