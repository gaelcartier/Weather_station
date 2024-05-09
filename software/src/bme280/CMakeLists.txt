# Add pico_stdlib library which aggregates commonly used features

add_library(
    bme280
    bme280.c 
    bme280.h
)

target_link_libraries(  bme280
                        hardware_i2c
                        pico_stdlib)

