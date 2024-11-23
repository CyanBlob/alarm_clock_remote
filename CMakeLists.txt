# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

add_definitions(-DARDUINO=1)
add_definitions(-DSOC_GPTIMER_SUPPORTED=1)

#set(EXTRA_COMPONENT_DIRS components)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(alarm_clock_remote)
#idf_build_component("main/Adafruit_Protomatter")
#idf_build_component("main/arduino-esp32")
#idf_build_component("main/Adafruit-GFX-Library")
#idf_build_component("main/Adafruit_BusIO")
#idf_build_component("components/mpu6050")

#idf_build_component("main/ESP32-HUB75-MatrixPanel-DMA-3.0.11")
