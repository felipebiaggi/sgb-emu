cmake_minimum_required(VERSION 3.5)

project(sgb-emu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(util)
add_subdirectory(cartridge)
add_subdirectory(cpu)
add_subdirectory(bus)
add_subdirectory(executable)
