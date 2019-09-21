cmake_minimum_required(VERSION 3.9)
project(manto)

set(CMAKE_CXX_STANDARD 11)

add_executable(manto main.cpp base/Manto.cpp base/Manto.h base/figures/figures3/Figure3.cpp base/figures/figures3/Figure3.h base/figures/figures2/Figure2.cpp base/figures/figures2/Figure2.h base/spaces/spaces2/Vector2.cpp base/spaces/spaces2/Vector2.h base/spaces/spaces3/Vector3.cpp base/spaces/spaces3/Vector3.h base/figures/figures2/Point2.cpp base/figures/figures2/Point2.h base/figures/figures3/Point3.cpp base/figures/figures3/Point3.h base/Tester.cpp base/Tester.h)