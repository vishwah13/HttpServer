cmake_minimum_required(VERSION 3.20)
project(HttpServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build server and client as separate executables
add_executable(Server src/server.cpp src/mainServer.cpp)
add_executable(Client src/client.cpp src/mainClient.cpp)

# Include directories
target_include_directories(Server PRIVATE src)
target_include_directories(Client PRIVATE src)

# Platform-specific socket libraries
if(WIN32)
    target_link_libraries(Server PRIVATE ws2_32)
    target_link_libraries(Client PRIVATE ws2_32)
elseif(UNIX)
    target_link_libraries(Server PRIVATE pthread)
    target_link_libraries(Client PRIVATE pthread)
endif()
