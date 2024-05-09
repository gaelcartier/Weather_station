# Add pico_stdlib library which aggregates commonly used features

add_library(
    font
    font.c
    font.h
)

target_link_libraries(  font
                        pico_stdlib)

