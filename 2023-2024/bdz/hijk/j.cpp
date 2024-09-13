#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Comparer {
  inline bool operator()(const std::pair<std::string, int>& e1, const std::pair<std::string, int>& e2) {
    return (e1.second > e2.second) || (e1.second == e2.second && e1.first < e2.first);
  }
};

int main(int, char**) {
  std::string word;
  std::unordered_map<std::string, size_t> m;
  // while (std::cin >> word) {
  while (std::cin >> word) {
    m[word]++;
  }

  std::vector<std::pair<std::string, int>> sv(m.begin(), m.end());
  std::sort(sv.begin(), sv.end(), Comparer());
  for (auto el : sv) {
    std::cout << el.first << '\n';
  }
}
