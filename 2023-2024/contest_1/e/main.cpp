#include <iostream>

int main() {
  int n;
  std::cin >> n;
  if (n % 400 == 0) {
    std::cout << "YES";
  } else if (n % 4 == 0 && n % 100 != 0) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
