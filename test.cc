#include "gtest/gtest.h"
#include <string>

TEST(FooTest, GoodFoo) {
  std::string foo("foo");
  EXPECT_STREQ("foo", foo.c_str());
}

TEST(FooTest, BadFoo) {
  int uninitialized __attribute((uninitialized));
  EXPECT_GT(uninitialized, 5);
}

TEST(FooTest, BadFoo2) {
  char *m = (char *)malloc(10);
  EXPECT_GT(m[0], 5);
  free(m);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}