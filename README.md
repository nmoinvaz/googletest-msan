# googletest-msan

Repository for compiling `googletest` with MSAN instrumented C++ libraries using CMake.

* https://github.com/google/googletest
* https://github.com/google/sanitizers/wiki/MemorySanitizerLibcxxHowTo

CI output should fail on `BadFoo2` test with MSAN output.

```
[ RUN      ] FooTest.BadFoo2
==4520==WARNING: MemorySanitizer: use-of-uninitialized-value
    ...
    #11 0x4a0e5f in FooTest_BadFoo2_Test::TestBody() /home/runner/work/googletest-msan/googletest-msan/test.cc:16:3
    #12 0x5450a9 in void testing::internal::HandleSehExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:2636:10
    #13 0x5450a9 in void testing::internal::HandleExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:2672:14
    #14 0x4d0e92 in testing::Test::Run() /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:2711:5
    #15 0x4d43a3 in testing::TestInfo::Run() /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:2890:11
    #16 0x4d5c38 in testing::TestSuite::Run() /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:3049:30
    #17 0x50dc18 in testing::internal::UnitTestImpl::RunAllTests() /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:5919:44
    #18 0x5474ce in bool testing::internal::HandleSehExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:2636:10
    #19 0x5474ce in bool testing::internal::HandleExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:2672:14
    #20 0x50c784 in testing::UnitTest::Run() /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/src/gtest.cc:5488:10
    #21 0x4a12cb in RUN_ALL_TESTS() /home/runner/work/googletest-msan/googletest-msan/_deps/googletest-src/googletest/include/gtest/gtest.h:2311:46
    #22 0x4a12cb in main /home/runner/work/googletest-msan/googletest-msan/test.cc:21:10
    #23 0x7f8fe69840b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
    #24 0x42398d in _start (/home/runner/work/googletest-msan/googletest-msan/test_foo+0x42398d)
```