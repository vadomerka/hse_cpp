#include <cstdint>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

struct Clients {
 public:
  std::unordered_map<std::string, int> clients_;

 public:
  void AddSum(std::string name, int sum) {
    clients_[name] += sum;
  }

  void PrintSum(std::string name) {
    auto it = clients_.find(name);
    if (it == clients_.end()) {
      std::cout << "ERROR" << '\n';
      return;
    }
    std::cout << it->second << '\n';
  }
};

int main(int, char**) {
  int com_number = 0;
  int command = 0;
  std::string name;
  int sum = 0;
  Clients g;
  std::cin >> com_number;
  for (int i = 0; i < com_number; i++) {
    std::cin >> command;
    if (command == 1) {
      std::cin >> name >> sum;
      g.AddSum(name, sum);
    } else if (command == 2) {
      std::cin >> name;
      g.PrintSum(name);
    }
  }
}
