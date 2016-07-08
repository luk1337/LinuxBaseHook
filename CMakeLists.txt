cmake_minimum_required(VERSION 3.5)
project(Basehook)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -fpermissive")

set(SOURCE_FILES Main.cpp Draw.cpp NetVarManager.cpp)
add_library(Basehook SHARED ${SOURCE_FILES})