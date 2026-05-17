cmake_minimum_required(VERSION 3.10)
project(d2s1)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME} 
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
