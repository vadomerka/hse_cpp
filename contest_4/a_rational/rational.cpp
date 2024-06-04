#include "rational.h"
#include <math.h>
#include <numeric>
// #include <c++/7/numeric>

Rational::Rational(int32_t n1) : Rational() {
  _numerator = n1;
  _denominator = 1;
}

Rational::Rational(int32_t n1, int32_t n2) : Rational() { SimpleSet(n1, n2); }

void Rational::SimpleSet(int32_t num, int32_t dev) {
  int32_t nums_gcd = (std::abs(num), std::abs(dev));
  int sign = (num * dev) / std::abs(num * dev);
  _numerator = std::abs(num) / nums_gcd * sign;
  _denominator = std::abs(dev) / nums_gcd;
}

int32_t Rational::GetNumerator(void) { 
  return _numerator; 
}

int32_t Rational::GetDenominator() { 
  return _denominator; 
}

void Rational::SetNumerator(int32_t n1) { 
  SimpleSet(n1, _denominator); 
}

void Rational::SetDenominator(int32_t n2) { 
  SimpleSet(_numerator, n2); 
}