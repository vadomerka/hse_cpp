#include <iostream>
#include <queue>

void Move(int h, int s, int e, std::queue<int> *poles) {
  if (poles[s].empty()) {
    return;
  }
  if (h == 1) {
    poles[s].pop();
    poles[e].push(h);
    std::cout << h << " " << s + 1 << " " << e + 1 << std::endl;
  } else {
    Move(h - 1, s, 3 - s - e, poles);
    poles[s].pop();
    poles[e].push(h);
    std::cout << h << " " << s + 1 << " " << e + 1 << std::endl;
    Move(h - 1, 3 - s - e, e, poles);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::queue<int> poles[3];
  for (int i = 0; i < n; i++) {
    poles[0].push(n - i);
  }
  Move(n, 0, 2, poles);
  return 0;
}
