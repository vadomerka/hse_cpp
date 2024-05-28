#include "rational.h"

#include <numeric>
#include <iostream>

Rational::Rational(int32_t n1) : Rational() {
  numerator_ = n1;
  denominator_ = 1;
}

Rational::Rational(int32_t n1, int32_t n2) : Rational() { 
  SimpleSet(n1, n2); 
}

#pragma region public functions
int32_t Rational::GetNumerator() const { 
  return numerator_; 
}

int32_t Rational::GetDenominator() const { 
  return denominator_; 
}

void Rational::SetNumerator(int32_t n1) { 
  SimpleSet(n1, denominator_); 
}

void Rational::SetDenominator(int32_t n2) {
  SimpleSet(numerator_, n2); 
}
#pragma endregion

#pragma region operators
Rational& Rational::operator*=(const Rational& other)
{
  SimpleSet(numerator_ * other.numerator_, denominator_ * other.denominator_);
  return *this;
}

Rational& Rational::operator/=(const Rational& other)
{
  SimpleSet(numerator_ * other.denominator_, denominator_ * other.numerator_);
  return *this;
}

Rational& Rational::operator+=(const Rational& other)
{
  SimpleSet(numerator_ * other.denominator_ + other.numerator_ * denominator_, denominator_ * other.denominator_);
  return *this;
}

Rational& Rational::operator-=(const Rational& other)
{
  SimpleSet(numerator_ * other.denominator_ - other.numerator_ * denominator_, denominator_ * other.denominator_);
  return *this;
}

Rational& Rational::operator++() {
  SimpleSet(numerator_ + denominator_, denominator_);
  return *this;
}

Rational& Rational::operator--() {
  SimpleSet(numerator_ - denominator_, denominator_);
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy(*this);
  SimpleSet(numerator_ + denominator_, denominator_);
  return copy;
}

Rational Rational::operator--(int) {
  Rational copy(*this);
  SimpleSet(numerator_ - denominator_, denominator_);
  return copy;
}

std::ostream& operator<<(std::ostream& os, const Rational& f) {
  os << f.numerator_;
  if (f.denominator_ != 1) {
    os << '/' << f.denominator_;
  }
  return os;
};

std::istream& operator>>(std::istream& is, Rational& f) {
  std::string str;
  int n = 0;
  int d = 1;
  is >> n;
  if (is.peek() == '/') {
    is.ignore(1);
    is >> d;
  }
  f.numerator_ = n;
  f.SetDenominator(d);
  return is;
};
#pragma endregion

#pragma region private functions
void Rational::SimpleSet(int32_t num, int32_t div) {
  CheckZero(div);
  if (num == 0) {
    numerator_ = 0;
    denominator_ = 1;
    return;
  }
  int32_t nums_gcd = std::gcd(std::abs(num), std::abs(div));
  int sign = (num * div) / std::abs(num * div);
  numerator_ = std::abs(num) / nums_gcd * sign;
  denominator_ = std::abs(div) / nums_gcd;
}

void Rational::CheckZero(int32_t div) {
  if (div == 0) {
    throw RationalDivisionByZero();
  }
}
#pragma endregion