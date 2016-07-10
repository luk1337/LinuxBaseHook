cmake_minimum_required(VERSION 3.5)
project(Basehook)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fpermissive")

file(GLOB SOURCE_FILES *.cpp)
add_library(Basehook SHARED ${SOURCE_FILES})