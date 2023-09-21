#pragma once
#include <iostream>
#include <vector>
#include "complex.h"

using std::vector;

void sort(vector<Complex> v) {
  bool check;
  for (int i = 0; i < v.size() - 1; ++i) {
    check = false;
    for (int j = 0; j < v.size() - i - 1; ++j) {
      if (v[j].abs_value() > v[j + 1].abs_value()) {
        std::swap(v[j], v[j + 1]);
        check = true;
      }
    }
    if (check == false) {
      break;
    }
  }
}
