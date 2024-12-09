#include <iostream>
#include <algorithm>
#include <vector>

int algorithm1(std::vector<int>& A) {
  int c = 0;
  int ind = -1;

  for (int i = 0; i < A.size(); ++i) {
    int c1 = 0;
    for (int j = 0; j < A.size(); ++j) {
      if (A[i] == A[j]) {
        c1 = c1 + 1;
      }
    }
    if (c1 > c) {
      c = c1;
      ind = i;
    }
  }
  if (c > A.size() / 2) {
    return A[ind];
  }
  return 0;
}

int algorithm2(std::vector<int>& A) {
  int c = 1;
  size_t n = A.size();
  int ind = 0;
  for (size_t i = 1; i < n; ++i) {
    if (A[ind] == A[i]) {
      c = c + 1;
    }
    else {
      c = c - 1;
    }
    if (c == 0) {
      ind = i;
      c = 1;
    }
  }
  c = 0;
  for (size_t i = 0; i < n; ++i) {
    if (A[i] == A[ind]) c++;
  }
  if (c > n / 2) return A[ind];
}

int algorithm3(std::vector<int>& A) {
  int n = A.size();
  if (n == 1) {
    return A[0];
  }
  int c = 1;
  std::sort(A.begin(), A.end());
  for (int i = 1; i < n; ++i) {
    if (A[i - 1] == A[i]) {
      c = c + 1;
    } else {
      if (c > n / 2) {
        return A[i - 1];
      }
      c = 1;
    }
  }
  if (c > n / 2) {
    return *(--A.end());
  }
}

int main() {
  std::vector<int> vec = {1, 2, 2, 2};
  std::cout << algorithm1(vec) << '\n';
  std::cout << algorithm2(vec) << '\n';
  std::cout << algorithm3(vec) << '\n';
  return 0;
}
