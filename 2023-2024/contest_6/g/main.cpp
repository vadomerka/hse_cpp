#include <ios>
#include <iostream>
#include <unordered_map>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::unordered_map<std::string, std::string> dic;
  std::string w1;
  std::string w2;

  dic.reserve(n * 2);

  for (int i = 0; i < n; ++i) {
    std::cin >> w1 >> w2;

    dic[w1] = std::move(w2);
    dic[dic[w1]] = w1;
  }

  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    std::cin >> w1;
    std::cout << dic[w1] << "\n";
  }

  return 0;
}