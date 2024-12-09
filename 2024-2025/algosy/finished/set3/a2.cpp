#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

std::ofstream MyFile("a2_merge_time.txt");
std::random_device dev;
std::mt19937 rng(dev());

void insertionSort(std::vector<int> &arr, int left, int right) {
  int n = arr.size();
  for (int i = left + 1; i < right + 1; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void merge(std::vector<int> &arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<int> &arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    if (right - left < 15) {
      insertionSort(arr, left, right);
    } else {
      mergeSort(arr, left, mid);
      mergeSort(arr, mid + 1, right);
      merge(arr, left, mid, right);
    }
  }
}

class ArrayGenerator {
public:
  static std::vector<int> getArray(size_t size, size_t low = 0,
                                   size_t high = 6000) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> unifx(low, high);

    std::vector<int> arr(size, 0);
    for (size_t i = 0; i < arr.size(); i++) {
      arr[i] = unifx(rng);
    }
    return arr;
  }

  static std::vector<int> getRSortedArr(size_t size) {
    std::vector<int> arr(size, 0);
    for (size_t i = arr.size(); i > 0; i--) {
      arr[size - i] = i * 5;
    }
    return arr;
  }

  static std::vector<int> getPSortedArr(size_t size) {
    std::vector<int> arr(size, 0);
    for (size_t i = 0; i < arr.size(); i++) {
      arr[i] = i * 5;
    }

    int high = arr.size() * 0.05;
    std::uniform_int_distribution<int> unifx(0, high);
    int swapNumber = unifx(rng);
    std::uniform_int_distribution<int> randSwap(0, arr.size() - 1);
    for (int i = 0; i < swapNumber; i++) {
      int x = randSwap(rng);
      int y = randSwap(rng);
      std::swap(arr[x], arr[y]);
    }
    return arr;
  }
};

class SortTester {
 public:
  static long long time(std::vector<int> arr, int start = 0, int end = 500) {
    auto tstart = std::chrono::high_resolution_clock::now();
    mergeSort(arr, start, end - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - tstart;
    long long msec =
        std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    return msec;
  }

  static void TestFuns() {
    std::vector<int> inv1 = ArrayGenerator::getArray(10000);
    std::vector<int> inv2 = ArrayGenerator::getRSortedArr(10000);
    std::vector<int> inv3 = ArrayGenerator::getPSortedArr(10000);
    for (size_t i = 500; i <= 10000; i += 100) {
      MyFile << i << ' ';
      std::uniform_int_distribution<int> unifx(0, 10000 - i);
      int start = unifx(rng);
      long long t1 = 0;
      long long t2 = 0;
      long long t3 = 0;
      int cnum = 10;
      for (int j = 0; j < cnum; j++) {
        t1 += time(inv1, start, start + i);
        t2 += time(inv2, start, start + i);
        t3 += time(inv3, start, start + i);
      }
      MyFile << t1 / cnum << ' ';
      MyFile << t2 / cnum << ' ';
      MyFile << t3 / cnum << ' ';
      MyFile << '\n';
    }
  }
};

void printArr(const std::vector<int> &arr) {
  for (size_t i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
}

int main() {
  int n = 0;
  int x = 0;
  std::vector<int> arr;
  std::cin >> n;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x;
    arr.push_back(x);
  }
  mergeSort(arr, 0, n - 1);
  printArr(arr);
  return 0;
}
