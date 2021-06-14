cmake_minimum_required(VERSION 3.17)
project(Navigation)

set(CMAKE_CXX_STANDARD 14)

add_executable(Navigation Core/main.cpp Core/AStar.cc Core/AStar.hh Core/AStarMission.cc Core/AStarMission.hh)