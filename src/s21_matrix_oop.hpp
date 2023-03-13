#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <vector>

class Time {
 private:
  int hours = 0;
  int minutes = 0;
  int seconds = 0;

 public:
  class IncorrectTimeException {};

  Time() = default;
  Time(int h, int m, int s);

  int GetHours() const;
  int GetMinutes() const;
  int GetSeconds() const;
};

class S21Matrix {
 private:
  unsigned int _rows = 0;
  unsigned int _cols = 0;
  // Could have used std::vector, but that would be too easy!
  double* _matrix = nullptr;

 public:
  S21Matrix() = default;
  S21Matrix(unsigned int rows, unsigned int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  void print();
};

// Needed to test the move constructor of S21Matrix
class Entity {
 public:
  // Takes in lvalues (copy)
  Entity(const S21Matrix& matrix) : _s21mat(matrix){};
  // Takes in rvalues (move)
  Entity(S21Matrix&& matrix) : _s21mat(std::move(matrix)){};

 private:
  S21Matrix _s21mat;
};

#endif
