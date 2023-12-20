cmake_minimum_required(VERSION 3.10)

project(Conway)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(src)

