cmake_minimum_required(VERSION 3.20)
project(HttpServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Auto-collect all .cpp files under src/
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(HttpServer ${SOURCES})

# Platform-specific socket libraries
if(WIN32)
    target_link_libraries(HttpServer PRIVATE ws2_32)
elseif(UNIX)
    target_link_libraries(HttpServer PRIVATE pthread)
endif()
