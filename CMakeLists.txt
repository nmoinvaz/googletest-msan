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
    -fsanitize-memory-track-origins
    -g
    )
link_directories($ENV{LLVM_BUILD_DIR}/lib)

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

add_library(xc++abi STATIC IMPORTED)
set_property(TARGET xc++abi PROPERTY
    IMPORTED_LOCATION $ENV{LLVM_BUILD_DIR}/lib/libc++abi.a)
add_library(xc++ STATIC IMPORTED)
set_property(TARGET xc++ PROPERTY
    IMPORTED_LOCATION $ENV{LLVM_BUILD_DIR}/lib/libc++.a)

target_link_options(test_foo PRIVATE
    -stdlib=libc++
    -L$ENV{LLVM_BUILD_DIR}/lib
    -Wl,-rpath,$ENV{LLVM_BUILD_DIR}/lib
    -lc++abi
    -lc++
    -fsanitize=memory
    -fsanitize-memory-track-origins
    -fno-optimize-sibling-calls
    -fno-omit-frame-pointer
    -g
    )

target_link_libraries(test_foo gtest gtest_main)

enable_testing()

add_test(NAME test_foo COMMAND $<TARGET_FILE:test_foo>)