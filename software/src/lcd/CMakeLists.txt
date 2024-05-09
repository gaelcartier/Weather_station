# Add pico_stdlib library which aggregates commonly used features


add_library(
    lcd 
    lcd.c 
    lcd.h
)

target_link_libraries(  lcd
                        hardware_spi 
                        hardware_timer 
                        pico_stdlib )

