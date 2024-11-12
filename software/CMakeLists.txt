cmake_minimum_required(VERSION 3.13)
project(PiPiNRF)

set(CMAKE_BUILD_TYPE Release)
set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)
include(./lib/RF24/CMakeLists.txt)

pico_sdk_init()

set(TESTER "Tester" "src/tester.cpp")
set(RECEIVER "Receiver" "src/receiver.cpp")
set(TRANSMITTER "Transmitter" "src/transmitter.cpp")
set(EXECUTABLES TESTER RECEIVER TRANSMITTER)

foreach(EXECUTEABLE IN LISTS EXECUTABLES)
    list(GET ${EXECUTEABLE} 0 EXECUTABLE_NAME)
    list(GET ${EXECUTEABLE} 1 SOURCE_CPP)

    add_executable(${EXECUTABLE_NAME}
        ${SOURCE_CPP}
    )
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)

    # Add pico_stdlib library, add more if used
    target_link_libraries(${EXECUTABLE_NAME} 
            pico_stdlib 
            pico_cyw43_arch_none
            hardware_spi
            tinyusb_board
            RF24
        )

    # enable usb output, disable uart output
    pico_enable_stdio_usb(${EXECUTABLE_NAME} 1)
    pico_enable_stdio_uart(${EXECUTABLE_NAME} 0)

    # Need to generate UF2 file for upload to RP2040
    pico_add_extra_outputs(${EXECUTABLE_NAME})
endforeach()