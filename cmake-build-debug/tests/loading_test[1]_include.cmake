if(EXISTS "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/tests/loading_test[1]_tests.cmake")
  include("/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/tests/loading_test[1]_tests.cmake")
else()
  add_test(loading_test_NOT_BUILT loading_test_NOT_BUILT)
endif()
