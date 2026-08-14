# Project Setup=============================
cmake_minimum_required(VERSION 3.16)

project(kbyte LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# ==========================================

# Core Library
add_library(kbyte_core
    src/Node.cpp
    src/Transistor.cpp
)

target_include_directories(kbyte_core PUBLIC src)

# Node Tests
add_executable(test_node
    tests/test_node.cpp
)

target_link_libraries(test_node PRIVATE kbyte_core)

add_test(NAME node_tests COMMAND test_node)

# Transistor Tests
add_executable(test_transistor
    tests/test_transistor.cpp
)

target_link_libraries(test_transistor PRIVATE kbyte_core)

add_test(NAME transistor_tests COMMAND test_transistor)