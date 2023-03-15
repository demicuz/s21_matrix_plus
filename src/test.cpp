#include "s21_matrix_oop.hpp"

#include <gtest/gtest.h>

namespace {

TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}

TEST(Constructor, Default) {
  auto test = S21Matrix();
  EXPECT_EQ(0, 0);
}

}  // namespace
