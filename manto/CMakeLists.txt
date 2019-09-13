cmake_minimum_required(VERSION 3.9)
project(manto)

set(CMAKE_CXX_STANDARD 11)

add_executable(manto main.cpp base/Manto.cpp base/Manto.h base/space/Vector.cpp base/space/Vector.h base/figures/Point.cpp base/figures/Point.h base/figures/Figure.cpp base/figures/Figure.h base/space/Line.cpp base/space/Line.h base/space/Plane.cpp base/space/Plane.h)