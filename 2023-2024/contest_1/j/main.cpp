#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int s = 0;
  int x = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    s += x;
  }
  std::cout << s;
  return 0;
}
