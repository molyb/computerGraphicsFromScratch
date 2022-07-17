cmake_minimum_required(VERSION 2.8)
project(computerGraphicsFromScratch)

add_subdirectory(samples)

find_package(OpenCV)

add_executable(computerGraphicsFromScratch src/main.cpp src/canvas.cpp src/traceRay.cpp)
target_include_directories(computerGraphicsFromScratch PUBLIC src ${OpenCV_INCLUDE_DIRS})
target_link_libraries(computerGraphicsFromScratch ${OpenCV_LIBS})
