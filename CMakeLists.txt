#-- Misc -----------------------------------------------------------------------
set(CMAKE_TOOLCHAIN_FILE gcc_cm4f.cmake)
enable_language(ASM)
cmake_minimum_required(VERSION 3.8.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include("stm32cube.cmake")

#-- Project config -------------------------------------------------------------
project(${STM32_PROJECT}) # Project name

#-- Defines --------------------------------------------------------------------
add_definitions(${STM32_DEFINES})

#-- Project paths --------------------------------------------------------------
set(APP_PATH App)

#-- Include dirs ---------------------------------------------------------------
include_directories(${APP_PATH})
include_directories(${STM32_INCLUDES})

#-- Sources --------------------------------------------------------------------
file(GLOB_RECURSE APP_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${APP_PATH}/*.c)

#-- Libs -----------------------------------------------------------------------
add_library(stm32 ${STM32_LIB_SOURCES})

#-- Linker script --------------------------------------------------------------
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/${STM32_LDSCRIPT} -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map,--cref,--print-memory-usage,--gc-sections")

#-- Project linking ------------------------------------------------------------
add_executable(${PROJECT_NAME}.elf ${STM32_CORE_SOURCES} ${APP_SRC})
target_link_libraries(${PROJECT_NAME}.elf stm32)

#-- Custom commands ------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} "-Oihex" ${PROJECT_NAME}.elf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} "-Obinary" ${PROJECT_NAME}.elf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJDUMP} "-DS" ${PROJECT_NAME}.elf > ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.dasm
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf)
