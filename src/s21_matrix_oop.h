#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

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

#endif
