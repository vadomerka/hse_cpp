#include <iostream>

bool **DrawSquare(int size, bool **arr, int si = 0, int sj = 0) {
  for (int i = si; i < size + si; i++) {
    for (int j = sj; j < size + sj; j++) {
      if (i == si || j == sj || i == size + si - 1 || j == size + sj - 1) {
        arr[i][j] = true;
      }
    }
  }
  if (size > 1) {
    arr[si + 1][sj + 0] = false;
  }
  if (size > 3 && !arr[si + 3][sj + 1]) {
    arr[si + 2][sj + 1] = true;
    DrawSquare(size - 4, arr, si = si + 2, sj = sj + 2);
  }
  return arr;
}

void PrintArr(int size, bool **arr) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      std::cout << arr[i][j];
    }
    std::cout << "\n";
  }
}

bool **CreateArr(int n) {
  bool **arr = new bool *[n];
  for (int i = 0; i < n; i++) {
    arr[i] = new bool[n];
    for (int j = 0; j < n; j++) {
      arr[i][j] = false;
    }
  }
  return arr;
}

int main() {
  int n = 0;
  std::cin >> n;
  bool **array = CreateArr(n);

  DrawSquare(n, array);
  PrintArr(n, array);

  for (int i = 0; i < n; i++) {
    delete[] array[i];
  }
  delete[] array;
  return 0;
}
