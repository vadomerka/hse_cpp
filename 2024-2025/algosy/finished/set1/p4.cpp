#include <iostream>
#include <stack>
#include <queue>
#include <vector>

int main() {
  std::stack<int> deadEnd;
  std::vector<int> track1;
  std::vector<std::pair<int, int>> res;
  int track2 = 0;
  int n = 0;
  std::cin >> n;
  int x = 0;
  int k = 0;
  
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    track1.push_back(x);
  }
  for (int i = 0; i < n; i++) {
    deadEnd.push(track1[i]);
    k++;
    if (i == n - 1 || deadEnd.top() < track1[i + 1]) {
      res.push_back({1, k});
      k = 0;
      while (!deadEnd.empty() && (deadEnd.top() - 1 == track2)) {
        k++;
        track2 = deadEnd.top();
        deadEnd.pop();
      }
      if (k == 0) {
        std::cout << 0;
        return 0;
      }
      res.push_back({2, k});
      k = 0;
    }
  }
  for (size_t i = 0; i < res.size(); i++) {
    std::cout << res[i].first << " " << res[i].second << '\n';
  }
  
  return 0;
}