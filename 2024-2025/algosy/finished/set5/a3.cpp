#include <cmath>
#include <iostream>
#include <random>
#include <vector>

size_t hash(std::string s) {
  const int p = 20; // Простое число для хеширования
  long long h = 0, p_pow = 1;

  for (size_t i = 0; i < s.length(); ++i) {
    h += (s[i] - 'a' + 1) * p_pow;
    p_pow *= p;
  }

  return h;
}

size_t hash(std::string s, int p) {
  // const int p = 20; // Простое число для хеширования
  long long h = 0, p_pow = 1;

  for (size_t i = 0; i < s.length(); ++i) {
    h += (s[i] - 'a' + 1) * p_pow;
    p_pow *= p;
  }

  return h;
}


int findP(const std::string& ch) {
  int p = 0;
  for (int i = 0; i < ch.size(); i++) {
    for (int j = i; j < ch.size(); j++) {
      std::string promt = ch.substr(i, 1) + ch.substr(j, 1);
      size_t res = hash(promt);
      if (res == 0) {
        std::cout << promt << " " << ch[i] - 'a' << " " << ch[j] - 'a' << '\n';
        // std::cout << -(ch[i] - 'a' + 1) / (ch[j] - 'a' + 1) << '\n';
        p = -(ch[i] - 'a' + 1) / (ch[j] - 'a' + 1);
        return p;
      }
      // std::cout << ch[i] << " " << ch[i] - 'a' << '\n';
    }
  }
}

bool checkBound(char c) {
  if ('0' <= c && c <= '9' || 'A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' ) return true;
  return false;
}

// Тестирование
int main() {
  std::string ch = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  // int p = findP(ch);
  // if (!p) return 0;

  for (int p = 1; p < 32; p++) {
    std::cout << "p = " << p << '\n';
    int k = 0;
    while(k < ch.size()) {
      char chk1 = (ch[k] - 'a' + 1);
      // -(ch[k] - 'a' + 1) / p - 1 + 'a'
      // =
      // ch[l]
      if (chk1 % p == 0) {
        char chk2 = (-1 * chk1) / p - 1 + 'a';
        if (checkBound(chk2)) {
          std::cout << ch[k] << " " << chk2 << '\n';
        }
      }
      k++;
    }
    std::cout << '\n';
  }

  return 0;
}
