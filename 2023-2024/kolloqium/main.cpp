#include <iostream>
#include <unordered_set>
#include <algorithm>

#include "Fraction.h"

class MyHashFunction {
public:
    size_t operator()(const Fraction& p) const
    {
      std::string ss = p.ToString();
      return (std::hash<std::string>()(ss));
    }
};


int main() {

  int n = 0;
  std::cin >> n;
  std::unordered_set<Fraction, MyHashFunction> s;
  int num = 0;
  int dev = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> num >> dev;
    s.insert(Fraction(num, dev));
  }

  auto compare = [](const Fraction& f1, const Fraction& f2) {return f1 < f2;};

  while (!s.empty()) {
    auto mit = std::max_element(s.begin(), s.end(), compare);
    std::cout << (*mit).ToString() << " ";
    s.erase(mit);
  }

  return 0;
}
