#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>

class Complex {
public:
  int a, b;
  // Constructor with parameters
  Complex(int a, int b) {
    this->a = a;
    this->b = b;
  }
  // Addition
  Complex operator+(const Complex& c);

  // Subtraction
  Complex operator-(const Complex& c);

  // Multiplication with constant
  Complex operator*(const int num);

  // Absalute value
  double abs_value() {
    return abs(sqrt(a * a + b * b));
  }

  // Overloading ostream operator
  friend std::ostream& operator<<(std::ostream& out, const Complex& c) {
    out << "(" << c.a << ", " << c.b << ")";
    return out;
  }
};
