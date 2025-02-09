#include <iostream>
#include <set>
#include <vector>

int main() {
  int* h1 = new int[1000001];
  int* h2 = new int[1000001];
  std::set<int> an;
  std::vector<int> n1;
  std::vector<int> n2;

  // input
  int n = 0;
  std::cin >> n;
  int x = 0;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x;
    n1.push_back(x);
    h1[x]++;
    if (an.find(x) == an.end()) {
      an.insert(x);
    }
  }
  int m = 0;
  std::cin >> m;
  for (size_t i = 0; i < m; i++) {
    std::cin >> x;
    n2.push_back(x);
    h2[x]++;
    if (an.find(x) == an.end()) {
      an.insert(x);
    }
  }
  n = std::max(n, m);
  while(n1.size() < n) { n1.push_back(0); }
  while(n2.size() < n) { n2.push_back(0); }

  int k = 0;
  // delete unique
  auto it = an.begin();
  while (it != an.end()) {
    int elem = *it;
    it++;
    // std::cout << elem << '\t' << h1[elem] << '\t' << h2[elem] << '\n';
    if (h1[elem] >= 1 && h2[elem] >= 1) {
      k = 1;
    }
    if (!(h1[elem] * h2[elem])) { an.erase(elem); }
    // else { it++; }
  }
  // if all unique -> no answer
  if (!k) {
    std::cout << k << " " << -1 << " " << -1;
    return 0;
  }
  int mk1 = 0, mk2 = 0; 
  int mi1 = 0, mi2 = 0;
  int k1 = 0, k2 = 0;
  // ........u...u...
  // ...u....u.......
  for (size_t i = 0; i < n; i++) {
    if (an.find(n1[i]) == an.end()) { 
      if (mk1 < k1) {
        mi1 = i - k1;
        mk1 = k1;
      }
      k1 = 0;
    } else {
      k1++;
    } 
    if (an.find(n2[i]) == an.end()) { 
      if (mk2 < k2) {
        mi2 = i - k2;
        mk2 = k2;
      }
      k2 = 0;
    } else {
      k2++;
    }
  }
  if (mk1 < k1) {
    mi1 = n - k1;
    mk1 = k1;
  }
  if (mk2 < k2) {
    mi2 = n - k2;
    mk2 = k2;
  }
  // std::cout << mk1 << " " << mi1 << '\n';
  // std::cout << mk2 << " " << mi2 << '\n';
  int mk = std::min(mk1, mk2);
  std::cout << mk << " " << mi1 + 1 << " " << mi2 + 1 << '\n';

  // for (auto elem: an) {
  //   std::cout << elem << '\t' << h1[elem] << '\t' << h2[elem] << '\n';
  // }

  return 0;
}