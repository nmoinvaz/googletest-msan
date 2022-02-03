cmake_minimum_required(VERSION 3.12)

include(FetchContent)

enable_language(CXX)

# Google test requires at least C++11
set(CMAKE_CXX_STANDARD 11)

if(NOT DEFINED ENV{LLVM_BUILD_DIR})
    message(FATAL_ERROR "LLVM build directory must be specified")
endif()

# Must set compile and link options before fetching googletest
include_directories(
    $ENV{LLVM_BUILD_DIR}/include
    $ENV{LLVM_BUILD_DIR}/include/c++/v1
    )
add_compile_options(
    -stdlib=libc++
    -fsanitize=memory
    -g
    )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL
    "Use shared (DLL) run-time lib even when Google Test is built as static lib." FORCE)
set(gtest_disable_pthreads ON CACHE BOOL
    "Disable uses of pthreads in gtest." FORCE)

# Fetch Google test source code from official repository
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(test_foo CXX)

add_executable(test_foo test.cc)

target_link_directories(test_foo PRIVATE
    $ENV{LLVM_BUILD_DIR}/lib
    )
target_link_options(test_foo PRIVATE
    -stdlib=libc++
    -lc++abi
    -fsanitize=memory
    -fsanitize-memory-track-origins
    )

target_link_libraries(test_foo gtest gtest_main)

enable_testing()

add_test(NAME test_foo COMMAND $<TARGET_FILE:test_foo>)