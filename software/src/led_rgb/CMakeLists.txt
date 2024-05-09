# Add pico_stdlib library which aggregates commonly used features


add_library(
    led_rgb 
    led_rgb.c 
    led_rgb.h
)

target_link_libraries(  led_rgb
                        hardware_spi 
                        hardware_timer 
                        pico_stdlib )

