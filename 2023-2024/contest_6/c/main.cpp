#include <algorithm>
#include <iostream>
#include <vector>

int main(int, char **) {
  int n = 0;
  std::cin >> n;
  std::vector<int> a(n);
  int x = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::cin >> x;
  std::cout << std::count(a.begin(), a.end(), x);
  return 0;
}
