# Blackpill (STM32F411) + STM32Cube + CMake example

Simple blinky example for [WeAct STM32F4x1 MiniF4](https://github.com/WeActTC/MiniSTM32F4x1) (on STM32f411) devboard.

Structure explained:

* Create STM32Cube MX project - ```blackpill_blinky.ioc```
* Generate Makefile project with STM32Cube
* Add ```App``` folder with custom (non-generated) code
* Add CMake files to the root:
  * ```gcc_cm4f.cmake``` - toolchain file to specify compiler triplets and flags for Cortex-M4 MCU
  * ```stm32cube.cmake``` - STM32Cube Makefile parser to extract STM32Cube project defines, include paths and sources
  * ```CMakeLists.txt``` - top level CMake script to build the project
* Build project with ```cmake_build_debug.sh``` script
