project(lab1)
cmake_minimum_required(VERSION 2.8)
#set (CMAKE_CXX_STANDARD 11)
#find_package(OpenGL REQUIRED)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
#SET(GCC_COVERAGE_LINK_FLAGS    "-lGL -lGLU -lglut")
#set (CMAKE_SHARED_LINKER_FLAGS "-lGL -lGLU -lglut,--as-needed")

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(lab1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
