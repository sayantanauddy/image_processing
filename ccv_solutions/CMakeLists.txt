cmake_minimum_required(VERSION 2.8)
project( ccv_solutions )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

# Setting the CMAKE_MODULE_PATH so that find_package works for custom libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Make your header file accessible to the compiler
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory (src)

message("This is ${CMAKE_MODULE_PATH}")


