#include <iostream>

int GetNOD(int a, int b) {
  while (a && b) {
    if (a > b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  return a + b;
}

int main() {
  int n;
  std::cin >> n;
  int d = 1, x = 0;
  std::cin >> d;
  for (int i = 1; i < n; i++) {
    std::cin >> x;
    if (x != 0) {
      d = GetNOD(d, x);
    }
  }
  std::cout << d;
  return 0;
}
