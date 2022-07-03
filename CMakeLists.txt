cmake_minimum_required(VERSION 3.20)
project(AEDAGrafos)

set(CMAKE_CXX_STANDARD 14)

add_executable(AEDAGrafos main.cpp Reader.cpp Reader.h Stop.cpp Stop.h Line.cpp Line.h Graph.cpp Graph.h Coordinate.cpp Coordinate.h DistancePath.cpp DistancePath.h Menu.h Menu.cpp)
