#include "s21_matrix_oop.hpp"

#include <iostream>

int main() {
  try {
    S21Matrix m1(0, 5);
  } catch (const std::exception& ex) {
    std::cerr << "ERROR: " << ex.what() << "\n";
  }

  // S21Matrix m2 = m1;
  // std::cout << "m1:\n";
  // m1.print();
  // std::cout << "m2:\n";
  // m2.print();

  // Entity e1(S21Matrix(2, 3));

  // std::cout << "woohoo\n";
  return 0;
}
