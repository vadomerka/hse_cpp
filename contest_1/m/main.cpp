#include <iostream>

int main() {
  int n;
  std::cin >> n;
  if (n == 0) {
    std::cout << 0;
    return 0;
  }
  int n1 = 1, n2 = 1;
  for (int i = 2; i < n; i++) {
    int tmp = n1 + n2;
    n1 = n2;
    n2 = tmp;
  }
  std::cout << n2;
  return 0;
}
