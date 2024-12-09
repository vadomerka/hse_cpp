// #include <algorithm>
// #include <cmath>
// #include <ios>
#include <iostream>
#include <vector>


int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int n = 0;
  int l = 0;
  std::cin >> l;
  std::cin >> n;
  int x = 0, y = 0;
  std::vector<std::pair<int, int>> times;
  for (int i = 0; i < n; i++) {
    std::cin >> x >> y;
    times.push_back({x, y});
  }

  // int ts[1000001];
  // int k = 0;
  // for (size_t i = 0; i < times.size(); i++) {
  //   while(times[i].first-- > 0) {
  //     ts[k++] = times[i].second;
  //   }
  // }
// 
  // for (size_t i = 0; i < 1000001; i++) {
  //   std::cout << ts[i] << " ";
  // }
  
  return 0;
