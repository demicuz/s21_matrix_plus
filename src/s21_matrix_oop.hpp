#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <vector>

class S21Matrix {
 private:
  int _rows = 4;
  int _cols = 4;
  // Could have used std::vector, but that would be too easy!
  // NOTE: storing in a row-major format
  double* _matrix = new double[16]{};

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const double matrix[], int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  double& operator()(int row, int col) const;

  double& at(int i, int j) const;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(double num) noexcept;
  void MulMatrix(const S21Matrix& other);

  int GetRows() const;
  int GetCols() const;
  double* GetRaw() const;
  void SetRows(int rows);
  void SetCols(int cols);

  void print() const;
};

#endif
