#include <cassert>
#include <iostream>

#include "rational.h"

void test01() { 
  Rational r;
  assert(true); 
}

void test02() {
  Rational r;
  assert(r.GetNumerator() == 0 && r.GetDenominator() == 1);
}

void test03() {
  Rational r(2);
  assert(r.GetNumerator() == 2 && r.GetDenominator() == 1);
}

void test04() {
  Rational r(1, 2);
  assert(r.GetNumerator() == 1 && r.GetDenominator() == 2);
}

void test05() {
  Rational r(2, 4);
  assert(r.GetNumerator() == 1 && r.GetDenominator() == 2);
}

void test06() {
  Rational r;
  r.SetNumerator(2);
  r.SetDenominator(4);
  assert(r.GetNumerator() == 1 && r.GetDenominator() == 2);
}

void test07() {
  Rational r = 5;
  bool check1 = r.GetNumerator() == 5 && r.GetDenominator() == 1;
  r.SetDenominator(15);
  bool check2 = r.GetNumerator() == 1 && r.GetDenominator() == 3;
  assert(check1 && check2);
}

void test08() {
  bool check = false;
  try {
    Rational r(1, 0);
  } catch(const RationalDivisionByZero&) {
    check = true;
  }
  assert(check);
}

void test09() {
  Rational r(1, -2);
  assert(r.GetNumerator() == -1 && r.GetDenominator() == 2);
}

void test10() {
  const Rational r1(1, -2);
  const Rational r2(4, 5);
  Rational res = r1 * r2;
  assert(res.GetNumerator() == -2 && res.GetDenominator() == 5);
}

void test11() {
  Rational r1(1, -2);
  assert((r1++).GetNumerator() == 1 && r1.GetDenominator() == 2 && 
         (r1--).GetNumerator() == -1 && r1.GetDenominator() == 2);
}

void test12() {
  Rational r1(1, -2);
  assert((++r1).GetNumerator() == 1 && r1.GetDenominator() == 2 && 
         (--r1).GetNumerator() == -1 && r1.GetDenominator() == 2);
}

void test13() {
  Rational r1(1, 2);
  std::cout << r1 << '\n';
  std::cin >> r1;
  std::cout << r1 << '\n';
}

void RunTests() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  test08();
  test09();
  test10();
  test11();
  test12();
  test13();
  std::cout << "All tests passed";
}

int main() {
  RunTests();
  return 0;
}
