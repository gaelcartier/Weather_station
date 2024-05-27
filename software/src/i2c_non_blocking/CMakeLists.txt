# Add pico_stdlib library which aggregates commonly used features


add_library(
    i2c_non_blocking 
    i2c_non_blocking.c 
    i2c_non_blocking.h
)

target_link_libraries(  i2c_non_blocking
                        hardware_i2c 
                        pico_stdlib
                        pico_i2c_slave )