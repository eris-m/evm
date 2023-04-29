cmake_minimum_required(VERSION 3.10)

project(evm_common VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

add_library(evm_common_obj OBJECT 
	inc/evm/instruction.h src/instruction.cpp
	inc/evm/loading.h src/loading.cpp)
target_include_directories(evm_common_obj PUBLIC inc/)

set_property(TARGET evm_common_obj PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(evm_common_shared SHARED $<TARGET_OBJECTS:evm_common_obj>)
target_include_directories(evm_common_shared PUBLIC inc/)
add_library(evm_common_static STATIC $<TARGET_OBJECTS:evm_common_obj>)
target_include_directories(evm_common_static PUBLIC inc/)
