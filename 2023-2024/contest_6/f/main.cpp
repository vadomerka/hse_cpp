#include <functional>
#include <iostream>
#include <queue>
#include <string_view>
#include <vector>

double Cost(std::priority_queue<int, std::vector<int>, std::greater<int>> &qq) {
  double res = 0;
  for (; qq.size() > 1;) {
    int m1 = qq.top();
    qq.pop();
    int m2 = qq.top();
    qq.pop();
    qq.push(m1 + m2);
    res += 0.05 * (m1 + m2);
  }
  return res;
}

int main(int, char **) {
  int n = 0;
  std::cin >> n;

  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  int x = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    pq.push(x);
  }
  std::cout << Cost(pq);
}
