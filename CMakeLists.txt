cmake_minimum_required(VERSION 3.10)

project(evm VERSION 0.1.0)

add_subdirectory(evm_common)

option(EVM_TESTS "Enable testing for EVM" ON)

if(${EVM_TESTS})
    add_subdirectory(tests)
endif()