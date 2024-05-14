# Add pico_stdlib library which aggregates commonly used features


add_library(
    display 
    display.c 
    display.h
)

target_link_libraries(  display
                        lcd
                        hardware_spi 
                        hardware_timer 
                        pico_stdlib )

