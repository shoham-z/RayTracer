cmake_minimum_required(VERSION 3.22)
project(RayTracer)


set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracer main.cpp
        primitives/Vector.cpp
        primitives/Ray.cpp
        primitives/Util.cpp
        primitives/Color.cpp
        primitives/Material.cpp
        primitives/Point.cpp
        primitives/GeoPoint.cpp
        geometries/Sphere.cpp
        geometries/Plane.cpp
        geometries/Triangle.cpp
        geometries/Geometry.cpp
        geometries/Geometries.cpp
        geometries/Intersectable.cpp
        geometries/Tube.cpp
        geometries/Cylinder.cpp
        geometries/Polygon.cpp
        geometries/Ellipsoid.cpp
        complexShapes/Box.cpp
        complexShapes/Cube.cpp
        complexShapes/Pyramid.cpp
        complexShapes/House.cpp
        complexShapes/StreetLamp.cpp
        renderer/Camera.cpp
        renderer/RayTracer.cpp
        renderer/Scene.cpp
        renderer/ImageWriter.cpp
        lights/AmbientLight.cpp
        lights/Light.cpp
        lights/LightSource.cpp
        lights/SpotLight.cpp
        lights/DirectionalLight.cpp
        lights/PointLight.cpp
        Tests/sphereTests.cpp)

target_include_directories(RayTracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
