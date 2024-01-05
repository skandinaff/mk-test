cmake_minimum_required(VERSION 3.15)
project(mk-test)

enable_language(ASM C)
set(CMAKE_C_STANDARD 99)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_C_LINK_EXECUTABLE arm-none-eabi-gcc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m0plus -mthumb")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/linker_script.ld")

add_executable(mk-test stc/main.c startup/startup_stm32l011xx.s)
