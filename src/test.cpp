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

const double identity_2_by_3[6] = {1, 0, 0, 0, 1, 0};

TEST(Constructor, Default) {
  S21Matrix m;

  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 4);

  EXPECT_TRUE(is_matrix_equal(m, identity_4_by_4));
}

TEST(Constructor, RowsCols) {
  S21Matrix m(2, 3);

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 3);

  EXPECT_TRUE(is_matrix_equal(m, identity_2_by_3));
}

TEST(Constructor, PreAllocatedMatrix) {
  double *m_raw =
      new double[16]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  S21Matrix m(m_raw, 4, 4);

  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 4);

  EXPECT_TRUE(is_matrix_equal(m, m_raw));
}

TEST(Constructor, Copy) {
  S21Matrix m1(2, 3);
  S21Matrix m2 = m1;

  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 3);

  m1.at(0, 0) = 123;

  EXPECT_TRUE(is_matrix_equal(m2, identity_2_by_3));

  m2.at(0, 0) = 42;
  const double reference[6] = {42, 0, 0, 0, 1, 0};
  EXPECT_TRUE(is_matrix_equal(m2, reference));
}

TEST(Constructor, Move) {
  S21Matrix m1(2, 3);
  S21Matrix m2 = m1;
  S21Matrix m3(std::move(m1));

  EXPECT_EQ(m1.GetRaw(), nullptr);
  EXPECT_NE(m2.GetRaw(), m3.GetRaw());

  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 3);

  EXPECT_EQ(m3.GetRows(), 2);
  EXPECT_EQ(m3.GetCols(), 3);
}

TEST(Operator, Parenthesis) {
  S21Matrix m(2, 3);

  EXPECT_EQ(m(1, 1), 1);
  EXPECT_EQ(m(1, 0), 0);

  m(0, 0) = 123;

  EXPECT_EQ(m(0, 0), 123);
}

TEST(Function, At) {
  S21Matrix m(2, 3);

  EXPECT_EQ(m.at(1, 1), 1);
  EXPECT_EQ(m.at(1, 0), 0);

  m.at(0, 0) = 123;

  EXPECT_EQ(m.at(0, 0), 123);
}

TEST(Function, EqMatrix) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 3);
  S21Matrix m3(4, 3);
  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_FALSE(m1.EqMatrix(m3));

  m2.at(0, 1) = 123;
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(Function, SumMatrix) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 3);

  m1.SumMatrix(m2);
  double reference[6] = {2, 0, 0, 0, 2, 0};
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  S21Matrix m3(3, 3);
  EXPECT_THROW(m1.SumMatrix(m3), std::invalid_argument);
}

TEST(Function, SubMatrix) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 3);

  m1.SubMatrix(m2);
  double reference[6] = {0, 0, 0, 0, 0, 0};
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  S21Matrix m3(3, 3);
  EXPECT_THROW(m1.SubMatrix(m3), std::invalid_argument);
}

TEST(Function, MulNumber) {
  S21Matrix m(2, 3);

  m.MulNumber(42);
  double reference[6] = {42, 0, 0, 0, 42, 0};
  EXPECT_TRUE(is_matrix_equal(m, reference));
}

TEST(Function, MulMatrix) {
  double *m1_raw = new double[6]{2, 3, 4, 5, 6, 7};
  double *m2_raw = new double[6]{3, 7, 11, 13, 23, 0};

  S21Matrix m1(m1_raw, 2, 3);
  S21Matrix m2(m2_raw, 3, 2);

  m1.MulMatrix(m2);
  EXPECT_EQ(m1.GetRows(), 2);
  EXPECT_EQ(m1.GetCols(), 2);

  double reference[4] = {131, 53, 242, 113};
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  EXPECT_THROW(m1.MulMatrix(m2), std::invalid_argument);
}

TEST(Setter, SetRow) {
  S21Matrix m(2, 3);

  m.SetRows(3);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);

  double reference1[9] = {1, 0, 0, 0, 1, 0, 0, 0, 0};
  EXPECT_TRUE(is_matrix_equal(m, reference1));

  m.at(2, 2) = 123;
  reference1[8] = 123;
  EXPECT_TRUE(is_matrix_equal(m, reference1));

  m.SetRows(1);
  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m.GetCols(), 3);

  double reference2[3] = {1, 0, 0};
  EXPECT_TRUE(is_matrix_equal(m, reference2));
}

TEST(Setter, SetCol) {
  S21Matrix m(3, 2);

  m.SetCols(3);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);

  double reference1[9] = {1, 0, 0, 0, 1, 0, 0, 0, 0};
  EXPECT_TRUE(is_matrix_equal(m, reference1));

  m.at(1, 2) = 123;
  reference1[5] = 123;
  EXPECT_TRUE(is_matrix_equal(m, reference1));

  m.SetCols(1);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 1);

  double reference2[3] = {1, 0, 0};
  EXPECT_TRUE(is_matrix_equal(m, reference2));
}
