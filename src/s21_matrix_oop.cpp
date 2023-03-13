#include "s21_matrix_oop.h"

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
