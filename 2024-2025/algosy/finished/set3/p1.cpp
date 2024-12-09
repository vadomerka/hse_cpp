#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

void printArr(const std::vector<int> &arr, int start=0) {
  for (size_t i = start; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
}

void heapify(std::vector<int> &A, int i) { //  — восстановление свойств max–кучи для элемента, стоящего по индексу i
  while((i > 1) && A[i / 2] < A[i]) {
    std::swap(A[i / 2], A[i]);
    i = i / 2;
  }
}

void sink(std::vector<int> &A, int k, int N) {
  while (2 * k <= N) {
    int j = 2 * k;
    if ((j < N) && (A[j] < A[j + 1])) ++j;
    if (!(A[k] < A[j])) break;
    std::swap(A[k], A[j]);
    k = j;
  }
}

void buildMaxHeap(std::vector<int> &A) { //  — построение max–кучи из исходного целочисленного массива.
  int N = A.size() - 1;  // AAAAAAAAAAAAAAAAA
  for (int k = N / 2; k >= 1; --k) {
    sink(A, k, N);
  }
}

void heapSort(std::vector<int> &A) { // — сортировка по неубыванию.
  int N = A.size() - 1;  // AAAAAAAAAAAAAAAAA
  buildMaxHeap(A);

  while(N > 1) {
    std::swap(A[1], A[N]);
    --N;
    sink(A, 1, N);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;
  std::vector<int> arr {0};
  int x = 0;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x;
    arr.push_back(x);
  }
  
  heapSort(arr);
  printArr(arr, 1);
  return 0;
}
