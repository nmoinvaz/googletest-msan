#include "gtest/gtest.h"
#include <string>

TEST(FooTest, GoodFoo) {
  std::string foo("foo");
  EXPECT_STREQ("foo", foo.c_str());
}

TEST(FooTest, BadFoo) {
  int uninitialized;
  EXPECT_GT(uninitialized, 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}