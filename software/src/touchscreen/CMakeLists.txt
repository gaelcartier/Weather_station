# Add pico_stdlib library which aggregates commonly used features

add_library(
    touchscreen
    touchscreen.c 
    touchscreen.h 
)

target_link_libraries(  touchscreen
                        hardware_i2c
                        hardware_timer 
                        pico_stdlib)

