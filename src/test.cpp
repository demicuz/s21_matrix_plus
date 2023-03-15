#include "s21_matrix_oop.hpp"

#include <gtest/gtest.h>

namespace {

TEST(Constructor, Default) {
  auto test = S21Matrix();
  EXPECT_EQ(0, 0);
}

}  // namespace
