cmake_minimum_required (VERSION 2.6)
project(Neuron)

set(CMAKE_CXX_FLAGS " -W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (neuron neuron.cpp main.cpp)
add_executable (Final neuron.cpp Network.cpp FinalMain.cpp)
add_executable (unit_test neuron.cpp unit_test.cpp)

target_link_libraries(unit_test gtest gtest_main)
add_test(unit_test unit_test)
