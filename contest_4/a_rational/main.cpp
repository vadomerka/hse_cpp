
/*
Необходимо реализовать класс для работы с рациональными числами Rational.

Рациональное число представляется двумя взаимно простыми целыми числами -
числителем и положительным знаменателем. Этот инвариант необходимо поддерживать
при выполнении любых операций над объектами класса Rational. Публичный интерфейс
класса должен включать:

- Конструктор по умолчанию, который инициализирует число нулем;
- Неявный конструктор преобразования от целых чисел (должен работать следующий код
Rational x = 5;). Не забудьте добавить комментарий // NOLINT (см. замечания);
- Конструктор от двух целых чисел (числитель и знаменатель). При этом не
гарантируется, что числа взаимно простые и ненулевые (об этом далее); 
- Методы GetNumerator() и GetDenominator(), возвращающие числитель и знаменатель
соответственно; 
- Методы SetNumerator(int) и SetDenominator(int), устанавливающие числитель и знаменатель в требуемые значения; 
- Бинарные арифметические операции (+, -, /, *) и их присваивающие версии (+=, -=, /=, *=); 
- Унарные операции (+, -), а также префиксные и постфиксные инкременты и декременты (++, --); 
- Операции сравнения; Операции ввода из потока и вывода в поток (>>, <<);
*/

#include <cassert>
#include <iostream>

#include "rational.h"
#include "rational_exceptions.h"

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

void RunTests() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  std::cout << "All tests passed";
}

int main() {
  RunTests();
  throw TestClass("my message");
  return 0;
}
