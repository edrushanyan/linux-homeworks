#include <iostream>
#include "complex.h"
#include "sort.h"
#include <vector>

using std::vector;
using std::endl;

int main() {
  Complex a(10, 7);
  Complex b(3, 9);

  std::cout << "Addition: " << a + b << endl;
  std::cout << "Subtraction: " << a - b << endl;
  std::cout << "Multiplication with constant: " << a * 3 << endl;
  std::cout << "Absalute value: " << a.abs_value() << endl;
  
  Complex c(6, 11);
  Complex d(14, 3);
  Complex e(21, 19);

  vector<Complex> v = { a, b, c, d, e};
  sort(v);
  std::cout << "Sort result: ";
  for (int i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  return 0;
}
