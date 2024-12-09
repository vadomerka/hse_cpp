#include <iostream>

int f(int n) {
  size_t x = 100;
  size_t y = 0;

  int cost1 = 2;
  int cost2 = 0;
  int cost3 = 2;
  int cost4 = 0;
  // init: 1; working: log2(n) + 1; end: 1 => 2(log2(n) + 1) + 2
  for (size_t outer = 1; outer <= n; outer *= 2) {
    cost1 += 2; // working
    x = x + outer; // cost: 2
    cost2 += 2;
    // std::cout << x << '\t';
    // init: 1; working: n - 2; end: 1 => 2(n - 2) + 2
    for (size_t inner = 2; inner < n; ++inner) {
      cost3 += 2;
      cost4 += 2;
      if (x > y / inner) { // cost: 2
        cost4 += 3;
        y = y + outer / inner; // cost: 3
      } else {
        cost4 += 1;
        --y; // cost: 1?
      }
      // std::cout << y << ' ';
    }
    // std::cout << '\n';
  }
  int ln = std::log2(n);
  // std::cout << cost1 << " " << 2 * (ln + 1) + 2 << '\t';
  // std::cout << cost2 << " " << 2 * (ln + 1) << '\t';
  // std::cout << cost3 << " " << (ln + 1) * (2 * (n - 2)) + 2 << '\t';
  // std::cout << cost4 << " " << (ln + 1) * (2 * (n - 2)) + 3 * (ln + 1) * (n - 2) << '\n';
  // return (cost1 == 2 * (ln + 1) + 2) && (cost2 == 2 * (ln + 1)) &&
  //  (cost3 == (ln + 1) * (2 * (n - 2)) + 2) && (cost4 == (ln + 1) * (2 * (n - 2)) + 3 * (ln + 1) * (n - 2));
  int res = 0;
  // res += 2 * (ln + 1) + 2;
  // res += 2 * (ln + 1);
  // res += (ln + 1) * (2 * (n - 2)) + 2;
  // res = ((ln + 1) * (2 * (n - 2)) + 3 * (ln + 1) * (n - 2));
  res = (7 * n - 10) * (ln + 1) + 4;
  for (int i = 9; i < ln; i++) {
    res -= 2 * (ln - i);
  }
  return (cost1 + cost2 + cost3 + cost4 - res);
}

int main() {
  int max = 0;
  for (int i = 1024; i <= 65536; i *= 2) {
    int res = f(i);
    if (res < max) {
      std::cout << max - res  << " ";
      max = res;
      std::cout << i << " " << res << '\n';
    }
  }
  // f(1024);
  return 0;
}