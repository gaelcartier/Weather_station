cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project( weather_station )

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_subdirectory( src )

add_executable( weather_station
                src/main.c
)

pico_enable_stdio_usb(weather_station 1)
pico_enable_stdio_uart(weather_station 0)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(  weather_station 
                        i2c_non_blocking 
                        util 
                        callback
                        systick
                        station 
                        weather_mode
                        pico_stdlib 
                        lcd 
                        font 
                        touchscreen 
                        bme280 
                        veml7700 
                        RN4870 
                        buffer_loop
                        display )

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs( weather_station )