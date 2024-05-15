# Add pico_stdlib library which aggregates commonly used features

add_library(
    systick
    systick.c
    systick.h
)

target_link_libraries(  systick
                        pico_stdlib)

