#include <iostream>
#include <queue>
#include <deque>

void print(std::deque<int> q) {
  // for ()
  while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop_front();
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);  // Отключить синхронизацию между iostream и stdio.
  std::cin.tie(nullptr);        // Отключить синхронизацию между std::cin и std::cout.

  std::deque<int> q1;
  std::deque<int> q2;
  int n = 0;
  int x = 0;
  char command = ' ';
  size_t wSum = 0;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> command;
    switch (command) {
    case '+':
      std::cin >> x;
      q2.push_back(x);
      break;
    case '*':
      std::cin >> x;
      q1.push_back(x);
      break;
    case '-':
      if (q1.empty()) {
        q1.push_back(q2.front());
        q2.pop_front();
      }
      std::cout << q1.front() << '\n';
      q1.pop_front();
      break;
    default:
      break;
    }
    wSum = q1.size() + q2.size();
    int midLen = wSum / 2 + wSum % 2;
    if (q1.size() <= q2.size()) {
      while (q1.size() < midLen) {
        q1.push_back(q2.front());
        q2.pop_front();
      }
    } else {
      while (q1.size() > midLen) {
        q2.push_front(q1.back());
        q1.pop_back();
      }
    }
    // print(q1);
    // print(q2);
  }
  return 0;
}