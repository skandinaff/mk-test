cmake_minimum_required(VERSION 3.22)

project(mk-test)
enable_language(C CXX ASM)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Core MCU flags, CPU, instruction set setup
set(CPU_PARAMETERS
    -mthumb
    -mcpu=cortex-m0plus
)

# Set linker script
set(linker_script_SRC ${CMAKE_SOURCE_DIR}/STM32L011K4Tx_FLASH.ld)
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

# Source files
set(src_core_src_SRCS 
    ${CMAKE_SOURCE_DIR}/Src/main.c
    ${CMAKE_SOURCE_DIR}/Src/uart.c
    ${CMAKE_SOURCE_DIR}/Src/commands.c
)

set(src_core_startup_SRCS 
    ${CMAKE_SOURCE_DIR}/Startup/startup_stm32l011xx.s
    ${CMAKE_SOURCE_DIR}/Drivers/Src/system_stm32l0xx.c)

# Include directories
set(include_DIRS
    ${CMAKE_SOURCE_DIR}/Include
    ${CMAKE_SOURCE_DIR}/Drivers/Include
    # Add other include directories as necessary
)

# Symbols definition
set(symbols_SYMB
    "DEBUG"
    "STM32L011xx"
)

# Executable files
add_executable(${EXECUTABLE} 
    ${src_core_src_SRCS}
    ${src_core_startup_SRCS})

# Include paths for each of the compiler
target_include_directories(${EXECUTABLE} PRIVATE ${include_DIRS})

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:C>:

    >
    $<$<COMPILE_LANGUAGE:CXX>:
        # Additional CXX flags
    >
    $<$<COMPILE_LANGUAGE:ASM>:
        -x assembler-with-cpp
    >
    $<$<CONFIG:Debug>:
        -Og -g3 -ggdb
    >
    $<$<CONFIG:Release>:
        -Os -g0
    >
)

# Setup linker parameters
target_link_options(${EXECUTABLE} PRIVATE
    -T${linker_script_SRC}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -Wl,--end-group
    -Wl,--print-memory-usage
)

# Project symbols
target_compile_definitions(${EXECUTABLE} PRIVATE
    ${symbols_SYMB}
    $<$<CONFIG:Debug>:DEBUG>
)

# Convert output to hex and binary
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
)

# Set a default baud rate
set(UART_BAUD_RATE "9600" CACHE STRING "Default UART baud rate")

# Add the baud rate as a definition to the compiler
add_definitions(-DUART_BAUD_RATE=${UART_BAUD_RATE})

# Set default values for PIN1 and PIN2
set(LED_PIN1 "4" CACHE STRING "Default GPIO pin number for PIN1")
set(LED_PIN2 "5" CACHE STRING "Default GPIO pin number for PIN2")
set(LED_PIN3 "6" CACHE STRING "Default GPIO pin number for PIN3")
set(LED_PIN4 "7" CACHE STRING "Default GPIO pin number for PIN4")

# Add definitions for PIN1 and PIN2
add_definitions(-DPIN1=${LED_PIN1})
add_definitions(-DPIN2=${LED_PIN2})
add_definitions(-DPIN3=${LED_PIN3})
add_definitions(-DPIN3=${LED_PIN4})

message("Exiting ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")
