#include "sorted_until.h"
#include <iostream>

int main() {
  int a[]{1, 2, 2, 3, 3, 4, 2, 5, 6};
  for (int i = 0; i < 11; i++) {
    bool res = IsSortedUntil(a, a + 9) == (a + i);
    if (res) {
      std::cout << i;
    }
  }
  return 0;
}
