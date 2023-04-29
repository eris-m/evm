# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-src"
  "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-build"
  "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/4c470445-3d5d-4a77-bbad-ba282ff5205a/Projects/evm/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
