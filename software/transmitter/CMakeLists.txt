add_executable(transmitter
    src/transmitter.cpp
)

target_include_directories(transmitter PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../
    
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(transmitter
    pico_stdlib 
    pico_unique_id
    pico_runtime

    hardware_sleep
    hardware_spi

    tinyusb_board

    RF24
)

pico_enable_stdio_usb(transmitter 1)
pico_enable_stdio_uart(transmitter 0)

pico_add_extra_outputs(transmitter)