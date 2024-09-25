# Add pico_stdlib library which aggregates commonly used features


add_library(
    drawing_mode 
    drawing_mode.c 
    drawing_mode.h
)

target_link_libraries(  drawing_mode 
                        hardware_spi
                        hardware_i2c
                        hardware_uart
                        pico_stdlib )

