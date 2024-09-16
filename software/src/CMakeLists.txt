# Add pico_stdlib library which aggregates commonly used features

add_subdirectory( font )
add_subdirectory( lcd )
add_subdirectory( touchscreen )
add_subdirectory( bme280 )
add_subdirectory( veml7700 )
add_subdirectory( led_rgb )
add_subdirectory( RN4870 )
add_subdirectory( util )
add_subdirectory( display )
add_subdirectory( station )
add_subdirectory( systick )
add_subdirectory( i2c_non_blocking )
add_subdirectory( callback )
add_subdirectory( buffer_loop )
add_subdirectory( weather_mode )
add_subdirectory( wellcome_mode )

target_link_libraries(  systick
                        i2c_non_blocking
                        callback
                        font
                        lcd
                        touchscreen
                        display
                        bme280
                        veml7700
                        led_rgb
                        RN4870
                        util
                        buffer_loop
                        weather_mode
                        wellcome_mode
                        station
                        pico_stdlib)
