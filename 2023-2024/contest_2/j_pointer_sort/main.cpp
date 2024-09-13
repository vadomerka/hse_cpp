#include <iostream>
#include <vector>

void Sort(int *begin, int *end) {
  for (int *i = begin; i <= end; i++) {
    for (int *j = i + 1; j <= end; j++) {
      if (*i > *j) {
        std::swap(*i, *j);
      }
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  Sort(&a[0], &a[n - 1]);
  for (int i = 0; i < n; i++) {
    std::cout << a[i] << " ";
  }
  return 0;
}
