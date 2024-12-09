#include <iostream>
#include <algorithm>
#include <vector>
#include <set>


void print(std::vector<int> vec, size_t step = 0) {
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << vec[(i + step) % vec.size()] << ' '; 
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> a1;
  int n = 0;
  std::cin >> n;
  int x = 0;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x;
    a1.push_back(x);
  }
  

  int maxc = 0;
  for (size_t i = 0; i < a1.size(); i++) {
    int c = 0;
    for (size_t j = 0; j < a1.size(); j++) {
      c += (a1[j] == a1[(j + i) % a1.size()]) ? 0 : 1;
    }
    maxc = c > maxc ? c : maxc;
  }
  std::set<std::vector<int>> st;
  for (size_t i = 0; i < a1.size(); i++) {
    int c = 0;
    for (size_t j = 0; j < a1.size(); j++) {
      c += (a1[j] == a1[(j + i) % a1.size()]) ? 0 : 1;
    }
    if (c == maxc) {
      std::vector<int> newVec {a1};
      rotate(newVec.begin(), newVec.begin() + i, newVec.end());
      st.insert(newVec);
    }
  }
  std::cout << st.size();

  return 0;
}