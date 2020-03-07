cmake_minimum_required(VERSION 3.15)
project(manto)

set(CMAKE_CXX_STANDARD 14)

# Flags para usar dtrace
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include_directories(base)
include_directories(base/figures/figures2)
include_directories(base/figures/figures3)
include_directories(base/spaces/spaces2)
include_directories(base/spaces/spaces3)
include_directories(base/util/clipper)

add_executable(manto
        base/figures/figures2/Figure2.cpp
        base/figures/figures2/Figure2.h
        base/figures/figures2/Point2.cpp
        base/figures/figures2/Point2.h
        base/figures/figures3/Figure3.cpp
        base/figures/figures3/Figure3.h
        base/figures/figures3/Point3.cpp
        base/figures/figures3/Point3.h
        base/spaces/spaces2/Vector2.cpp
        base/spaces/spaces2/Vector2.h
        base/spaces/spaces3/Vector3.cpp
        base/spaces/spaces3/Vector3.h
        base/Manto.cpp
        base/Manto.h
        base/Tester.cpp
        base/Tester.h
        main.cpp base/util/clipper/clipper.hpp base/util/clipper/clipper.cpp base/figures/figures3/Segment3.cpp base/figures/figures3/Segment3.h base/figures/figures2/Segment2.cpp base/figures/figures2/Segment2.h base/util/Range.cpp base/util/Range.h base/util/RangeContainer.cpp base/util/RangeContainer.h base/figures/figures3/Triangle3.cpp base/figures/figures3/Triangle3.h base/figures/figures2/Triangle2.cpp base/figures/figures2/Triangle2.h base/spaces/spaces2/Line2.cpp base/spaces/spaces2/Line2.h base/figures/figures2/Polygon2.cpp base/figures/figures2/Polygon2.h base/figures/figures3/Polygon3.cpp base/figures/figures3/Polygon3.h)
