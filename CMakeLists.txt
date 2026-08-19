# Project Setup=============================
cmake_minimum_required(VERSION 3.16)

project(kbyte LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# ==========================================

# Core Library
add_library(kbyte_core
    src/circuits/Node.cpp
    src/circuits/Transistor.cpp
    src/circuits/Circuit.cpp
    src/gates/Inverter.cpp
    src/gates/NAND2.cpp
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

# Inverter Tests
add_executable(test_inverter
    tests/test_inverter.cpp
)

target_link_libraries(test_inverter PRIVATE kbyte_core)

add_test(NAME inverter_tests COMMAND test_inverter)

# NAND2 Tests
add_executable(test_nand2
    tests/test_nand2.cpp
)

target_link_libraries(test_nand2 PRIVATE kbyte_core)

add_test(NAME nand2_tests COMMAND test_nand2)