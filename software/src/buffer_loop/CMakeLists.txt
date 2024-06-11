# Add pico_stdlib library which aggregates commonly used features


add_library(
    buffer_loop 
    buffer_loop.c 
    buffer_loop.h
)

target_link_libraries(  buffer_loop 
                        hardware_spi
                        hardware_i2c
                        hardware_uart
                        pico_stdlib )

