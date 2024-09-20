#include <iostream>
#include <vector>

struct matrix {
  int value, up_d, down_d;
};

void PrintArr(std::vector<std::vector<matrix>> arr) {
  int n = arr.size();
  int m = arr[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << arr[i][j].value << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<matrix>> arr(n);
  for (int i = 0; i < n; i++) {
    arr[i] = std::vector<matrix>(m);
    for (int j = 0; j < m; j++) {
      arr[i][j] = {0, std::min(m - j - 1, i), std::min(j, n - i - 1)};
    }
  }

  for (int i = 0; i < n; i++) {
    if (i != 0) {
      arr[i][0] = {arr[i - 1][0].value + arr[i][0].up_d + 1, arr[i][0].up_d,
                   arr[i][0].down_d};
    }
    for (int j = 1; j < m; j++) {
      arr[i][j] = {arr[i][j - 1].value + arr[i][j - 1].down_d + arr[i][j].up_d +
                       1,
                   arr[i][j].up_d, arr[i][j].down_d};
    }
  }

  PrintArr(arr);

  return 0;
}
