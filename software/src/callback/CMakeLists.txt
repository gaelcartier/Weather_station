# Add pico_stdlib library which aggregates commonly used features


add_library(
    callback 
    callback.c 
    callback.h
)

target_link_libraries(  callback 
                        pico_stdlib )