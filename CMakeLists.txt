cmake_minimum_required(VERSION 3.6)
project(Pokemon_simulation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network")

set(SOURCE_FILES main.cpp state.h pokemon.h util.h graphics.h)
add_executable(Pokemon_simulation ${SOURCE_FILES})