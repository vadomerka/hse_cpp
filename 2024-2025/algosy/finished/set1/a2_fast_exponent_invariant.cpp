#include <iostream>

int fastExponent(int x, int n) {
  int r = 1;
  int p = x;
  int e = n;
  int c = 0;
  int res = std::pow(x, n);
  int check = r * std::pow(p, e);
  // x^n = r * p ^ e
  std::cout << (check == res) << ' ';
  while (e > 0) {  // r * 2 <= p
    std::cout << (check == res) << ' ';
    if (e % 2 != 0) {
      r = r * p;
    }
    p = p * p;
    e = e / 2;
  }
  std::cout << (check == res) << ' ';
  return r;
}

std::string toBinary(int n) {
  std::string r;
  while (n != 0) {
    r = (n % 2 == 0 ? "0" : "1") + r;
    n /= 2;
  }
  return r;
}

int toBinary2(int n) {
  std::string r;
  int rr = 0;
  while (n != 0) {
    (n % 2 == 0 ? rr++ : rr += 2);
    n /= 2;
  }
  return rr;
}

int main() {
  int max = 0;
  
  for (int i = 7; i < 16; i++) {
    std::cout << fastExponent(3, i) << "\n\n";
  }
  std::cout << max;
  return 0;
}