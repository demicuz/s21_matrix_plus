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

  // Some helper computation functions
  void subMatrix(const double* mat, double* tmp, int row_to_skip,
                 int col_to_skip, int n) const;
  double det(const double* mat, int n) const;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const double matrix[], int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  S21Matrix& operator+=(const S21Matrix& rhs);
  S21Matrix& operator-=(const S21Matrix& rhs);
  S21Matrix& operator*=(const S21Matrix& rhs);
  S21Matrix& operator*=(double rhs);
  S21Matrix operator+(const S21Matrix& rhs) const;
  S21Matrix operator-(const S21Matrix& rhs) const;
  S21Matrix operator*(const S21Matrix& rhs) const;
  S21Matrix operator*(double rhs) const;
  bool operator==(const S21Matrix& rhs) const;
  bool operator!=(const S21Matrix& rhs) const;
  double& operator()(int row, int col) const;

  double& at(int row, int col) const;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  double Determinant() const;
  double Minor(int row, int col) const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

  int GetRows() const;
  int GetCols() const;
  double* GetRaw() const;
  void SetRows(int rows);
  void SetCols(int cols);

  void print() const;
};

#endif
