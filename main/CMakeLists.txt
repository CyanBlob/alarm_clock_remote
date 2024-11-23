idf_component_register(SRCS "main.c"
        "alarm_clock_remote.cpp"
        "espnow_example_main.cpp"
        "wifi_config.cpp"
        "nvs_wrapper.cpp"
        "buzz_task.cpp"
        "accelerometer_task.cpp"
        INCLUDE_DIRS "."
        REQUIRES freertos esp_wifi nvs_flash esp_driver_gpio esp_driver_i2s esp_timer esp_driver_gptimer esp_driver_ledc esp_driver_i2c driver)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11 -fpermissive)
set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3)
