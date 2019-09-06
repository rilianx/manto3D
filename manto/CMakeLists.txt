cmake_minimum_required(VERSION 3.9)
project(manto)

set(CMAKE_CXX_STANDARD 11)

add_executable(manto main.cpp base/Manto.cpp base/Manto.h base/Vector.cpp base/Vector.h)