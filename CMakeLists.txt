cmake_minimum_required(VERSION 3.7.1)
project(RayTracer2)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -ljpeg -pthread")

set(SOURCE_FILES main.cpp camera.cpp image.cpp integrator.cpp material.cpp mesh.cpp parser.cpp point_light.cpp ppm.cpp
        ray.cpp scene.cpp sphere.cpp timer.cpp tinyxml2.cpp triangle.cpp jpeg.cpp matrixInverse.cpp ctpl_stl.h hit_record.h
        triangular.h utility.h vector2f.h vector3f.h vector4f.h texture.cpp texture.h rotation.cpp rotation.h transformation.cpp transformation.h)

add_executable(RayTracer2 ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libjpeg.so.8)