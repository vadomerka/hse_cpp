#include <iostream>
#include <string>
#include <vector>

int main() {
  int n;
  std::vector<int> v;
  std::string com;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> com;
    if (com == "push") {
      int x = 0;
      std::cin >> x;
      v.push_back(x);
      std::cout << "ok";
    } else if (com == "pop") {
      std::cout << v.back();
      v.pop_back();
    } else if (com == "back") {
      std::cout << v.back();
    } else if (com == "size") {
      std::cout << v.size();
    } else if (com == "clear") {
      v = {};
      std::cout << "ok";
    } else if (com == "exit") {
      std::cout << "bye";
      return 0;
    }
  }

  return 0;
}
