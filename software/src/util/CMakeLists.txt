# Add pico_stdlib library which aggregates commonly used features


add_library(
    util 
    util.c 
    util.h
)

target_link_libraries(  util
                        hardware_timer 
                        pico_stdlib )