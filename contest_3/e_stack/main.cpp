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
      std::cout << "ok" << std::endl;
    } else if (com == "pop") {
      std::cout << v.back() << std::endl;
      v.pop_back();
    } else if (com == "back") {
      std::cout << v.back() << std::endl;
    } else if (com == "size") {
      std::cout << v.size() << std::endl;
    } else if (com == "clear") {
      v = {};
      std::cout << "ok" << std::endl;
    } else if (com == "exit") {
      std::cout << "bye" << std::endl;
      return 0;
    }
  }

  return 0;
}
