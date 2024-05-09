# Add pico_stdlib library which aggregates commonly used features


add_library(
    station 
    station.c 
    station.h
)

target_link_libraries(  station 
                        hardware_spi
                        hardware_i2c
                        hardware_uart
                        pico_stdlib )

