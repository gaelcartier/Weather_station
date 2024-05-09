# Add pico_stdlib library which aggregates commonly used features
add_library(
    veml7700
    veml7700.c 
    veml7700.h 
)

target_link_libraries(  veml7700
                        hardware_i2c
                        pico_stdlib)

