cmake_minimum_required(VERSION 3.12)

set(FREERTOS_KERNEL_PATH $ENV{FREERTOS_PATH})

set(PICO_PLATFORM rp2040)
include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)

project(main_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_library(freertos STATIC
            $ENV{FREERTOS_PATH}
            $ENV{FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/port.c
)

target_include_directories(freertos PUBLIC
  .
  $ENV{FREERTOS_PATH}/include
  $ENV{FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040
  $ENV{FREERTOS_PATH}/portable/GCC/ARM_CM0
)

target_link_libraries(freertos
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap3
    pico_stdlib
)

add_executable(
  blink
  blink.c
)

pico_enable_stdio_usb(blink 1)

pico_add_extra_outputs(blink)
target_link_libraries(blink pico_stdlib freertos)
