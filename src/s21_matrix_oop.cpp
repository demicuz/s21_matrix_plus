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

  // TODO where do I catch the exception?
  try {
    _matrix = new double[static_cast<long>(_rows) * _cols]{};
  } catch (const std::bad_alloc& e) {
    std::cerr << "ERROR: S21Matrix: " << e.what() << "\n";
  }

  int min_dim = std::min(_rows, _cols);
  for (int i = 0; i != min_dim; ++i) {
    _matrix[i * _cols + i] = 1;
  }

  std::cout << "created!\n";
}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) {
  _rows = other._rows;
  _cols = other._cols;

  try {
    _matrix = new double[static_cast<long>(_rows) * _cols]{};
  } catch (const std::bad_alloc& e) {
    std::cerr << "ERROR: S21Matrix: " << e.what() << "\n";
  }

  std::copy_n(other._matrix, _rows * _cols, _matrix);

  std::cout << "copied!\n";
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  _rows = other._rows;
  _cols = other._cols;
  _matrix = other._matrix;

  // other._rows = 0;
  // other._cols = 0;
  other._matrix = nullptr;

  std::cout << "moved!\n";
}

S21Matrix::~S21Matrix() {
  delete[] _matrix;
  std::cout << "destroyed!\n";
}

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
