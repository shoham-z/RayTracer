cmake_minimum_required(VERSION 3.22)
project(RayTracer)


set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracer main.cpp
        primitives/Vector.cpp
        primitives/Ray.cpp
        geometries/Sphere.cpp
        geometries/Geometry.cpp
        geometries/Intersectable.cpp
        primitives/Point.cpp)

target_include_directories(RayTracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
