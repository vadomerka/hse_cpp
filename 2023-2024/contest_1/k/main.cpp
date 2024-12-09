#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int m = 0, sm = 0;
  while (n != 0) {
    if (m <= n) {
      sm = m;
      m = n;
    } else if (sm <= n) {
      sm = n;
    }
    std::cin >> n;
  }
  std::cout << sm;
  return 0;
}
