#include <cstdint>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

int main(int, char **) {
  int n = 0;
  std::cin >> n;
  std::unordered_map<int, size_t> map;
  int x = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    map[x] += 1;
  }
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    std::cin >> x;
    std::cout << map[x] << '\n';
  }
}
