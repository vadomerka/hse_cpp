#include <array>
#include <iostream>
#include <type_traits>
#include <cassert>

#include "rational.h"

#include "matrix.h"

template <class T, size_t N>
Rational F(Matrix<T, N, N> m1, Matrix<T, N, N> m2) {
  return Trace(GetTransposed(m2) * m1);
}

int main() {
  Matrix<Rational, 2, 2> h1 {-1, -2, -2, 1};
  Matrix<Rational, 2, 2> h2 {1, 2, 1, -2};
  Matrix<Rational, 2, 2> h3 {1, 0, 2, 1};
  Matrix<Rational, 2, 2> e1 {-1, -2, -2, 1};
  Rational c = -(F(h3, e1)/F(e1, e1));
  Matrix<Rational, 2, 2> e2 = h2 + c * e1;
  Matrix<Rational, 2, 2> e3 {1, 0, 2, 1};
  std::cout << Trace<Rational, 2>(e1);
  return 0;
}