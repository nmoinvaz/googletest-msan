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

project(test CXX)

add_executable(test test.cc)

target_compile_options(test PRIVATE
    -fsanitize=memory
    -stdlib=libc++
    -D_GLIBCXX_USE_CXX11_ABI=0
    -I$ENV{LLVM_BUILD_DIR}/include
    -I$ENV{LLVM_BUILD_DIR}/include/c++/v1
    )

target_link_options(test PRIVATE
    -stdlib=libc++
    -lstdc++
    -L$ENV{LLVM_BUILD_DIR}/lib
    -lc++abi
    -lc++
    -fsanitize=memory
    -fsanitize-memory-track-origins
    -fno-optimize-sibling-calls
    -fno-omit-frame-pointer
    -Wl,-rpath,$ENV{LLVM_BUILD_DIR}/lib
    -g
    )

target_link_libraries(test gtest_main)

add_test(NAME test COMMAND $<TARGET_FILE:test>)