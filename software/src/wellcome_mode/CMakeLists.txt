# Add pico_stdlib library which aggregates commonly used features


add_library(
    wellcome_mode 
    wellcome_mode.c 
    wellcome_mode.h
)

target_link_libraries(  wellcome_mode 
                        hardware_spi
                        hardware_i2c
                        hardware_uart
                        pico_stdlib )

