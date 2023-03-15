#include "s21_matrix_oop.hpp"

#include <gtest/gtest.h>

const double EPSILLON = 1e-7;

bool almost_equal(double a, double b) { return abs(a - b) < EPSILLON; }

bool is_matrix_equal(const S21Matrix &m, const double *reference) {
  const double *m_raw = m.GetRaw();
  long n_elements = static_cast<long>(m.GetRows()) * m.GetCols();

  for (long i = 0; i < n_elements; ++i) {
    if (!almost_equal(m_raw[i], reference[i])) {
      return false;
    }
  }

  return true;
}

const double identity_4_by_4[16] = {1, 0, 0, 0, 0, 1, 0, 0,
                                    0, 0, 1, 0, 0, 0, 0, 1};

TEST(Constructor, Default) {
  S21Matrix m;

  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 4);

  EXPECT_TRUE(is_matrix_equal(m, identity_4_by_4));
}
