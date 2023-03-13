#include <iostream>
#include "s21_matrix_oop.h"

int main() {
  std::cout << "Hello from test.cpp!\n";
  try {
    Time t(1, 2, 3);
    std::cout << t.GetHours() << "\n";
  } catch (const Time::IncorrectTimeException& ex) {
    std::cout << "An exception is caught!\n";
  }

  return 0;
}
