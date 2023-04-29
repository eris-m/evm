cmake_minimum_required(VERSION 3.10)

project(evm_testing)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        # URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(loading_test loading_test.cpp)
target_link_libraries(loading_test evm_common_shared GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(loading_test)
