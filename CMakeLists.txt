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
    src/gates/NOR2.cpp
    src/gates/XOR2.cpp
    src/components/HalfAdder.cpp
    src/components/FullAdder.cpp
    src/components/RippleCarryAdder8.cpp
    src/components/MUX2.cpp
    src/cpu/ALU1.cpp
    src/cpu/ALU8.cpp
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

# NOR2 Tests
add_executable(test_nor2
    tests/test_nor2.cpp
)

target_link_libraries(test_nor2 PRIVATE kbyte_core)

add_test(NAME nor2_tests COMMAND test_nor2)

# XOR2 Tests
add_executable(test_xor2
    tests/test_xor2.cpp
)

target_link_libraries(test_xor2 PRIVATE kbyte_core)

add_test(NAME xor2_tests COMMAND test_xor2)

# Half Adder Tests
add_executable(test_half_adder
    tests/test_half_adder.cpp
)

target_link_libraries(test_half_adder PRIVATE kbyte_core)

add_test(NAME half_adder_tests COMMAND test_half_adder)

# Full Adder Tests
add_executable(test_full_adder
    tests/test_full_adder.cpp
)

target_link_libraries(test_full_adder PRIVATE kbyte_core)

add_test(NAME full_adder_tests COMMAND test_full_adder)

# Ripple Carry Adder 8 Tests
add_executable(test_ripple_carry_adder8
    tests/test_ripple_carry_adder8.cpp
)

target_link_libraries(test_ripple_carry_adder8 PRIVATE kbyte_core)

add_test(NAME ripple_carry_adder8_tests COMMAND test_ripple_carry_adder8)

# MUX2 Tests
add_executable(test_mux2
    tests/test_mux2.cpp
)

target_link_libraries(test_mux2 PRIVATE kbyte_core)

add_test(NAME mux2_tests COMMAND test_mux2)

# ALU1 Tests
add_executable(test_alu1
    tests/test_alu1.cpp
)

target_link_libraries(test_alu1 PRIVATE kbyte_core)

add_test(NAME alu1_tests COMMAND test_alu1)

# ALU8 Tests
add_executable(test_alu8
    tests/test_alu8.cpp
)

target_link_libraries(test_alu8 PRIVATE kbyte_core)

add_test(NAME alu8_tests COMMAND test_alu8)