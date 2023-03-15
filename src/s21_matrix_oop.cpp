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
