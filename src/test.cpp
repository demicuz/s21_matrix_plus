#include "s21_matrix_oop.hpp"

#include <iostream>

int main() {
  try {
    S21Matrix m1(2, 3);
    // Testing the copy constructor:
    S21Matrix m2 = m1;
    std::cout << "m1:\n";
    m1.print();
    std::cout << "m2:\n";
    m2.print();
    // Testing the move constructor:
    Entity e1(S21Matrix(2, 3));

  } catch (const std::bad_alloc& ex) {
    std::cout << "ERROR: S21Matrix: " << ex.what() << "\n";
  }

  std::cout << "main() end!\n";
  return 0;
}
