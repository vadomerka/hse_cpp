#include <iostream>
#include <vector>

void PrintArr(std::vector<std::vector<int>> arr) {
  int n = arr.size();
  int m = arr[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> arr(n);

  for (int i = 0; i < n; i++) {
    arr[i] = std::vector<int>(m);
    for (int j = 0; j < m; j++) {
      if (i == 0 || j == 0) {
        arr[i][j] = 1;
      } else {
        arr[i][j] = 0;
      }
    }
  }
  int si = 1, sj = 1;
  while (si < n && sj < m) {
    for (int i = si; i < n; i++) {
      arr[i][sj] = arr[i - 1][sj] + arr[i][sj - 1];
    }
    for (int j = sj; j < m; j++) {
      arr[si][j] = arr[si - 1][j] + arr[si][j - 1];
    }
    si++;
    sj++;
  }
  PrintArr(arr);

  return 0;
}
