# Add pico_stdlib library which aggregates commonly used features


add_library(
    RN4870 
    RN4870.c 
    RN4870.h
)


target_link_libraries(  RN4870
                        hardware_uart 
                        hardware_timer 
                        pico_stdlib )

