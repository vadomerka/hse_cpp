#include <cstdint>
#include <iostream>
#include <map>

int main() {
  std::map<std::string, std::map<std::string, int64_t>> db;

  std::string buyer;
  std::string product;
  int64_t number = 0;

  while (std::cin >> buyer >> product >> number) {
    db[buyer][product] += number;
  }

  for (const auto& c1 : db) {
    std::cout << c1.first << ":\n";
    for (const auto& p1 : c1.second) {
      std::cout << p1.first << " " << p1.second << '\n';
    }
  }
  return 0;
}