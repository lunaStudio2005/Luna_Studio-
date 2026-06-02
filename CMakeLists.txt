cmake_minimum_required(VERSION 3.20)
project(LunaStudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_executable(engine_app
  engine/src/main.cpp
)

target_link_libraries(engine_app PRIVATE Python3::Python)
