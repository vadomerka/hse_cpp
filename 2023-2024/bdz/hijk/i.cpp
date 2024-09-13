#include <functional>
#include <iostream>
#include <map>

int main(int, char **) {
  std::string word;
  std::map<std::string, size_t> m;
  while (std::cin >> word) {
    std::cout << m[word] << ' ';
    m[word] += 1;
  }
}
