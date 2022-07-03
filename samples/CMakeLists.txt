cmake_minimum_required(VERSION 2.8)
project(sampleCodes)

find_package(OpenGL)
find_package(GLUT)
find_package(OpenCV)

add_executable(opengl_sample opengl.cpp)
target_include_directories(opengl_sample PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})
target_link_libraries(opengl_sample ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(opencv_sample opencv.cpp)
target_include_directories(opencv_sample PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv_sample ${OpenCV_LIBS})
