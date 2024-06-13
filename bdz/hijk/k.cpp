#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

int main(int, char **) {
  // std::string a1 = "q";
  // std::string a2 = "asdasdfvacewdaffbaa";
  // if (a2.find(a1) == a2.npos) {
  //   std::cout << a1;
  // }
  int n = 0;
  std::cin >> n;
  std::string word;
  std::vector<std::string> m(n);
  int c = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> word;
    for (int j = 0; j < i; j++) {
      if (m[j].find(word) != m[j].npos) {
        c++;
      }
      if (word.find(m[j]) != word.npos) {
        c++;
      }
    }
    m[i] = word;
  }
  std::cout << c;
}
