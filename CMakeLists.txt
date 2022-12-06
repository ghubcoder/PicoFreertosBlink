cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
set(FREERTOS_KERNEL_PATH $ENV{FREERTOS_KERNEL_PATH})

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(main_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_library(freertos STATIC
  ${FREERTOS_KERNEL_PATH}
  ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/port.c
)

target_include_directories(freertos PUBLIC
  .
  ${FREERTOS_KERNEL_PATH}/include
  ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/include
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
