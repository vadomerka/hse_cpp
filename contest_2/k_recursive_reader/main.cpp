#include <iostream>
#include <string>

void Read(int n) {
  if (n == 0) {
    return;
  }
  int x = 0;
  std::cin >> x;
  Read(n - 1);
  std::cout << " " << x;
}

int main() {
  int n;
  std::cin >> n;
  Read(n);
  return 0;
}
