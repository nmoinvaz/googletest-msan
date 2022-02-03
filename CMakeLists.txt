cmake_minimum_required(VERSION 3.12)

include(FetchContent)

enable_language(CXX)

# Google test requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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

macro(configure_cxx_msan target)
    target_compile_options(${target} PRIVATE
        -fsanitize=memory
        -stdlib=libc++
        -fno-exceptions
        -I$ENV{LLVM_BUILD_DIR}/include
        -I$ENV{LLVM_BUILD_DIR}/include/c++/v1
        )
    target_link_options(${target} PRIVATE
        -L$ENV{LLVM_BUILD_DIR}/lib
        -Wl,-rpath,$ENV{LLVM_BUILD_DIR}/lib
        -stdlib=libc++
        -lc++abi
        -lc++
        -static
        -fsanitize=memory
        -fsanitize-memory-track-origins
        -fno-optimize-sibling-calls
        -fno-omit-frame-pointer
        -g
        )
endmacro()

configure_cxx_msan(test_foo)
configure_cxx_msan(gtest_main)
configure_cxx_msan(gtest)

target_link_libraries(test_foo gtest gtest_main)

enable_testing()

add_test(NAME test_foo COMMAND $<TARGET_FILE:test_foo>)