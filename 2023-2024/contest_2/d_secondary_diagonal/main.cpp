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
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> arr(n);
  for (int i = 0; i < n; i++) {
    arr[i] = std::vector<int>(n);
    for (int j = 0; j < n; j++) {
      arr[i][j] = 0;
    }
  }

  for (int i = 0; i < n; i++) {
    int j = n - i - 1;
    arr[i][j] = 1;
    for (int jj = j + 1; jj < n; jj++) {
      arr[i][jj] = 2;
    }
  }

  PrintArr(arr);

  return 0;
}
