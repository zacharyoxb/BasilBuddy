# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(BasilBuddy C CXX ASM)

pico_sdk_init()


add_executable(
    BasilBuddy
    src/main.c
)

pico_btstack_make_gatt_header(BasilBuddy PRIVATE "${CMAKE_CURRENT_LIST_DIR}/config/plant_service.gatt")

pico_set_program_name(BasilBuddy "BasilBuddy")
pico_set_program_version(BasilBuddy "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(BasilBuddy 0)
pico_enable_stdio_usb(BasilBuddy 1)

# Add the standard library to the build
target_link_libraries(
    BasilBuddy
    hardware_adc
    hardware_timer
    hardware_gpio
    hardware_sync
    pico_stdlib
    pico_btstack_ble
    pico_btstack_cyw43
    pico_cyw43_arch_none
    
)

target_include_directories(BasilBuddy
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/config
)



pico_add_extra_outputs(BasilBuddy)

