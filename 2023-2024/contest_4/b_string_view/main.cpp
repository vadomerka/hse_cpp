#define CATCH_CONFIG_MAIN
// #include "catch.hpp"
#include <cassert>
#include <iostream>
#include "string_view.h"
#include "string_view.h"

void Equal(const StringView& actual, const char* expected, size_t n) {
  assert(actual.Data() == expected);
  assert(actual.Size() == n);
  assert(actual.Length() == n);
  assert(actual.Empty() == (n == 0));
  for (size_t i = 0; i < n; ++i) {
    assert(actual[i] == expected[i]);
  }
}

void test01() {
  const StringView sv;
  Equal(sv, nullptr, 0);
}

void test02() {
  const char* str = "aba";
  const StringView sv = str;
  Equal(sv, str, 3);
}

void test03() {
  const char* str = "abacaba";
  const StringView sv(str + 2, 4);
  Equal(sv, str + 2, 4);
}

void test04() {
  const char* str = "abacaba";
  const StringView sv(str + 2, 4);
  const auto copy = sv;
  Equal(sv, str + 2, 4);
  Equal(copy, str + 2, 4);
}

void test05() {
  static_assert(!std::is_assignable_v<decltype(std::declval<StringView&>().Front()), char>);
  static_assert(!std::is_assignable_v<decltype(std::declval<StringView&>().Back()), char>);
  static_assert(!std::is_assignable_v<decltype(std::declval<StringView&>()[0]), char>);

  const StringView sv = "abcdef";

  assert(sv.Front() == 'a');
  assert(sv.Back() == 'f');
  assert(sv[1] == 'b');
}

void test06() {
  const char* str = "some_test_string";
  StringView sv = str;

  sv.RemovePrefix(5);
  Equal(sv, str + 5, 11);

  sv.RemovePrefix(0);
  Equal(sv, str + 5, 11);

  sv.RemovePrefix(4);
  Equal(sv, str + 9, 7);

  sv.RemovePrefix(7);
  Equal(sv, str + 16, 0);
}

void test07() {
  const char* str = "some_test_string";
  StringView sv = str;

  sv.RemoveSuffix(5);
  Equal(sv, str, 11);

  sv.RemoveSuffix(0);
  Equal(sv, str, 11);

  sv.RemoveSuffix(4);
  Equal(sv, str, 7);

  sv.RemoveSuffix(7);
  Equal(sv, str, 0);
}

void test08() {
  const char* str = "some_test_string";
  StringView sv = str;

  Equal(sv.Substr(0, 5), str, 5);
  Equal(sv, str, 16);

  Equal(sv.Substr(0, 16), str, 16);
  Equal(sv, str, 16);

  Equal(sv.Substr(2, 7), str + 2, 7);
  Equal(sv, str, 16);

  Equal(sv.Substr(7, 9), str + 7, 9);
  Equal(sv, str, 16);
}

void test09() {
  const char* str = "some_test_string";
  StringView sv = str;

  sv.Substr(2, 7).Swap(sv);
  Equal(sv, str + 2, 7);
}

int main() {
  std::cout << "t1";
  test01();
  std::cout << "t2";
  test02();
  std::cout << "t3";
  test03();
  std::cout << "t4";
  test04();
  std::cout << "t5";
  test05();
  std::cout << "t6";
  test06();
  std::cout << "t7";
  test07();
  std::cout << "t8";
  test08();
  std::cout << "t9";
  test09();
  std::cout << "all done";
  return 0;
}