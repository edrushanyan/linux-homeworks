#include <iostream>
#include "complex.h"


   // Addition
   Complex Complex::operator+(const Complex& c) {
     return Complex(a + c.a, b + c.b);
   }

   // Subtraction
   Complex Complex::operator-(const Complex& c) {
     return Complex(a - c.a, b - c.b);
   }

   // Multiplication with constant
   Complex Complex::operator*(const int num) {
     return Complex(a * num , b * num);
   }
