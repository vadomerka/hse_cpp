#include <iostream>
#include <vector>

void PrintArr(std::vector<std::vector<int>> arr) {
  int n = arr.size();
  int m = arr[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (arr[i][j] == 9) {
        std::cout << "* ";
      } else {
        std::cout << arr[i][j] << " ";
      }
    }
    std::cout << "\n";
  }
}

bool CheckCords(int r, int c, int n, int m) {
  return (0 <= r && r < n && 0 <= c && c < m);
}

std::vector<std::pair<int, int>> GetNeibs(int r, int c) {
  std::vector<std::pair<int, int>> a;
  a.emplace_back(r - 1, c - 1);
  a.emplace_back(r - 1, c);
  a.emplace_back(r - 1, c + 1);
  a.emplace_back(r, c - 1);
  a.emplace_back(r, c);
  a.emplace_back(r, c + 1);
  a.emplace_back(r + 1, c - 1);
  a.emplace_back(r + 1, c);
  a.emplace_back(r + 1, c + 1);
  return a;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> arr(n);
  for (int i = 0; i < n; i++) {
    arr[i] = std::vector<int>(m);
    for (int j = 0; j < m; j++) {
      arr[i][j] = 0;
    }
  }

  int k;
  std::cin >> k;
  int x, y;
  for (int i = 0; i < k; i++) {
    std::cin >> x >> y;
    x--;
    y--;
    arr[x][y] = 9;
    for (auto &&p : GetNeibs(x, y)) {
      if (CheckCords(p.first, p.second, n, m) && !(arr[p.first][p.second] == 9)) {
        arr[p.first][p.second] += 1;
      }
    }
  }

  PrintArr(arr);

  return 0;
}
