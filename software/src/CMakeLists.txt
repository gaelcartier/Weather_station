# Add pico_stdlib library which aggregates commonly used features

add_subdirectory( font )
add_subdirectory( lcd )
add_subdirectory( touchscreen )
add_subdirectory( bme280 )
add_subdirectory( veml7700 )
add_subdirectory( led_rgb )
add_subdirectory( RN4870 )
add_subdirectory( util )
add_subdirectory( station )

target_link_libraries(  font
                        lcd
                        touchscreen
                        bme280
                        veml7700
                        led_rgb
                        RN4870
                        util
                        station
                        pico_stdlib)
