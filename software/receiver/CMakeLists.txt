add_executable(receiver
    src/receiver.cpp
)

target_sources(receiver PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../lib/HID_Handler/DanceInputHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../lib/HID_Handler/usb_descriptors.c
    ${CMAKE_CURRENT_LIST_DIR}/../lib/HID_Handler/callbacks.c
)

target_include_directories(receiver PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../

    ${CMAKE_CURRENT_LIST_DIR}/..//lib/HID_Handler
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(receiver
    pico_stdlib 
    pico_unique_id
    pico_runtime

    hardware_sleep
    hardware_spi

    tinyusb_device
    tinyusb_board

    RF24
)

pico_add_extra_outputs(receiver)