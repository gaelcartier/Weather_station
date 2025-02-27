# Install script for directory: /home/gael/git/Weather_station/software/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/gael/git/Weather_station/software/build/src/font/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/lcd/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/touchscreen/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/bme280/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/veml7700/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/led_rgb/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/RN4870/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/util/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/display/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/station/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/systick/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/i2c_non_blocking/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/callback/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/buffer_loop/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/weather_mode/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/wellcome_mode/cmake_install.cmake")
  include("/home/gael/git/Weather_station/software/build/src/drawing_mode/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/gael/git/Weather_station/software/build/src/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
