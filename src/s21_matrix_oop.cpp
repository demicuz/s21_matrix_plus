#include "s21_matrix_oop.hpp"

#include <iostream>
#include <algorithm>

Time::Time(int h, int m, int s) {
  if (s < 0 || s > 59) {
    throw IncorrectTimeException();
  }
  if (m < 0 || m > 59) {
    throw IncorrectTimeException();
  }
  if (h < 0 || h > 23) {
    throw IncorrectTimeException();
  }

  hours = h;
  minutes = m;
  seconds = s;
}

int Time::GetHours() const { return hours; }

int Time::GetMinutes() const { return minutes; }

int Time::GetSeconds() const { return seconds; }

S21Matrix::S21Matrix() {
  _rows = 4;
  _cols = 4;
  _matrix = new double[16]{};

  for (int i = 0; i != 16; ++i) {
    _matrix[i * _cols + i] = 1;
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0) {
    throw std::invalid_argument("S21Matrix: rows or cols less than zero");
  }
  if (rows == 0 || cols == 0) {
    throw std::invalid_argument("S21Matrix: empty matrix");
  }

  _rows = rows;
  _cols = cols;

  _matrix = new double[static_cast<long>(_rows) * _cols]{};

  int min_dim = std::min(_rows, _cols);
  for (int i = 0; i != min_dim; ++i) {
    _matrix[i * _cols + i] = 1;
  }

  // std::cout << "created!\n";
}

// The caller MUST provide correct matrix, rows and cols
S21Matrix::S21Matrix(const double* matrix, int rows, int cols) {
  if (matrix == nullptr) {
    throw std::invalid_argument("S21Matrix: can't create matrix from nullptr");
  }
  if (rows < 0 || cols < 0) {
    throw std::invalid_argument("S21Matrix: rows or cols less than zero");
  }
  if (rows == 0 || cols == 0) {
    throw std::invalid_argument("S21Matrix: empty matrix");
  }

  _rows = rows;
  _cols = cols;
  _matrix = (double*)matrix;

  // std::cout << "created!\n";
}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) {
  _rows = other._rows;
  _cols = other._cols;

  _matrix = new double[static_cast<long>(_rows) * _cols]{};
  std::copy_n(other._matrix, _rows * _cols, _matrix);

  // std::cout << "copied!\n";
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  _rows = other._rows;
  _cols = other._cols;
  _matrix = other._matrix;

  // other._rows = 0;
  // other._cols = 0;
  other._matrix = nullptr;

  // std::cout << "moved!\n";
}

// Destructor
S21Matrix::~S21Matrix() noexcept {
  delete[] _matrix;
  // std::cout << "destroyed!\n";
}

double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i > _rows - 1 || j > _cols - 1) {
    throw std::out_of_range("S21Matrix: matrix indices out of range");
  }

  return _matrix[i * _cols + j];
}

// Because using operator() for indexing is stupid
// https://stackoverflow.com/q/317450
double& S21Matrix::at(int i, int j) const { return (*this)(i, j); }

int S21Matrix::GetRows() const { return _rows; }

int S21Matrix::GetCols() const { return _cols; }

double* S21Matrix::GetRaw() const { return _matrix; }

void S21Matrix::SetRows(int new_rows) {
  if (new_rows < 1) {
    throw std::out_of_range("S21Matrix: rows can't be set to 0 or less");
  }
  // The compiler will probably optimize this anyway, but just in case
  if (new_rows == _rows) {
    return;
  }

  double* new_matrix = new double[static_cast<long>(new_rows) * _cols]{};
  std::copy_n(_matrix, std::min(new_rows, _rows) * _cols, new_matrix);

  _rows = new_rows;
  delete[] _matrix;
  _matrix = new_matrix;
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols < 1) {
    throw std::out_of_range("S21Matrix: cols can't be set to 0 or less");
  }
  // The compiler will probably optimize this anyway, but just in case
  if (new_cols == _cols) {
    return;
  }

  double* new_matrix = new double[static_cast<long>(_rows) * new_cols]{};

  int cols_to_copy = std::min(new_cols, _cols);

  for (int i = 0; i != _rows; ++i) {
    for (int j = 0; j != cols_to_copy; ++j) {
      new_matrix[i * new_cols + j] = _matrix[i * _cols + j];
    }
  }

  _cols = new_cols;
  delete[] _matrix;
  _matrix = new_matrix;
}

// TODO probably remove this
void S21Matrix::print() const {
  std::cout << "[";
  for (int i = 0; i != _rows; ++i) {
    std::cout << "[";
    for (int j = 0; j != _cols; ++j) {
      std::cout << _matrix[i * _cols + j] << ", ";
    }
    std::cout << "], ";
  }
  std::cout << "]\n";
}
