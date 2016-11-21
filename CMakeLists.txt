cmake_minimum_required(VERSION 3.6)
project(openmp)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("Openmp found...!")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else()
    message("Openmp not found...!")
endif()

FIND_PACKAGE(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

FIND_PACKAGE(Boost 1.58.0 COMPONENTS filesystem system program_options REQUIRED)
if (BOOST_FOUND)
    message("Boost library found...!")
else()
    message("Boost library not found...!")
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(Boost_INCLUDE_DIR /usr/local/include/boost)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(SOURCE_FILES main.cpp)
add_executable(openmp ${SOURCE_FILES})
target_link_libraries(openmp ${Boost_LIBRARIES} ${OpenCV_LIBS})
