# Add pico_stdlib library which aggregates commonly used features


add_library(
    station 
    station.c 
    station.h
)

target_link_libraries(  station
                        display
                        weather_mode
                        hardware_spi
                        hardware_i2c
                        hardware_uart
                        # bme_280
                        # veml7700
                        # RN4870
                        pico_stdlib )

