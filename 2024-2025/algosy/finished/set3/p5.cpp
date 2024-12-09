#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <random>

template <size_t N>
std::vector<std::bitset<N>> parseMatrix(const std::string &hexString, int n) {
  std::vector<std::bitset<N>> matrix(n);
  int bitsPerHex = 4;
  int k = n / 4 + int(n % 4 != 0);
  int hexIndex = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j) {
      char hx = hexString[k * i + j];
      int dx = 0;
      if (hx >= '0' && hx <= '9') {
        dx = hx - '0';
      } else {
        dx = hx - 'A' + 10;
      }
      for (int l = bitsPerHex - 1; l >= 0; l--) {
        if (j * bitsPerHex + l < n) {matrix[i][j * bitsPerHex + l] = dx & 1;}
        dx >>= 1;
      }
    }
  }

  return matrix;
}

template <size_t N>
bool checkMatrix(const std::vector<std::bitset<N>> &a,
                                           const std::vector<std::bitset<N>> &b,
                                           const std::vector<std::bitset<N>> &c,
                                           int n) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<int> unifx(0, 1);
  for (int t = 0; t < 5; ++t) {
    std::bitset<N> x;
    for (int i = 0; i < n; ++i) x[i] = unifx(rng);

    std::bitset<N> ax, bx, abx;
    for (int i = 0; i < n; ++i)
      if (x[i]) ax ^= a[i];

    for (int j = 0; j < n; ++j)
      if (ax[j]) abx ^= b[j];

    for (int i = 0; i < n; ++i)
      if (x[i]) bx ^= c[i];

    if (abx != bx) return false;
  }

  return true;

  // for (size_t i = 0; i < n; i++)
  //   for (size_t j = 0; j < n; j++)
  //     for (size_t k = 0; k < n; k++)
  //       result[i][j] = result[i][j] ^ (A[i][k] & B[k][j]);
  // return result;
}

template <size_t N>
bool compareMatrices(const std::vector<std::bitset<N>> &A,
                     const std::vector<std::bitset<N>> &B, int n) {
  for (int i = 0; i < n; ++i) {
    if (A[i].count() != B[i].count()) {
      return false;
    }
  }
  return true;
}

template <size_t N> void printM(std::vector<std::bitset<N>> m, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << m[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::string> hexe(3, "");
  std::string str = "";
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < n; j++) {
      std::cin >> str;
      hexe[i] += str;
    }
  }

  auto A = parseMatrix<4000>(hexe[0], n);
  auto B = parseMatrix<4000>(hexe[1], n);
  auto C = parseMatrix<4000>(hexe[2], n);
  
  // printM(A, n);
  // printM(B, n);
  // printM(C, n);
  // printM(AB, n);

  if (checkMatrix(A, B, C, n)) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }

  return 0;
}
/*#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void removeSpaces(std::vector<std::string>& hexStrings) {
  for (std::string& hexString : hexStrings) {
      std::stringstream ss(hexString);
      std::string noSpaces, temp;
      while (ss >> temp) {
          noSpaces += temp;
      }
      hexString = noSpaces;
  }
}

char c16(int num) {
  if (num < 10) return static_cast<char>('0' + num);
  switch (num)
  {
  case 10:
    return 'A';
    break;
  case 11:
    return 'B';
    break;
  case 12:
    return 'C';
    break;
  case 13:
    return 'D';
    break;
  case 14:
    return 'E';
    break;
  case 15:
    return 'F';
    break;
  default:
    return '0';
    break;
  }
}

int main() {
  int n;
  std::cin >> n;
  
  std::vector<std::vector<std::string>> hexe {{
    "0 0 1 0 1 0 0",
    "1 0 1 0 1 0 0",
    "0 1 1 0 1 0 0",
    "0 1 1 1 1 0 0",
    "1 1 0 1 0 0 0",
    "1 0 0 0 1 0 0",
    "0 1 1 1 0 0 0"}, {

    "0 0 1 0 1 0 0",
    "1 0 1 0 1 0 0",
    "0 1 1 0 1 0 0",
    "0 1 1 1 1 0 0",
    "1 1 0 1 0 0 0",
    "1 0 0 0 1 0 0",
    "0 1 1 1 0 0 0"}, {

    "0 0 1 0 1 0 0",
    "1 0 1 0 1 0 0",
    "0 1 1 0 1 0 0",
    "0 1 1 1 1 0 0",
    "1 1 0 1 0 0 0",
    "1 0 0 0 1 0 0",
    "0 1 1 1 0 0 0"}};
  
  std::cin.ignore();
  std::vector<std::string> hexe(n, "");
  for (size_t i = 0; i < n; i++) {
    std::getline(std::cin, hexe[i]);
  }
  
  int hexPerLine = n / 4 + int(n % 4 != 0);
  int bytePerHex = 4;
  // std::cout << hexPerLine;

  removeSpaces(hexe);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j += bytePerHex) {
      std::string conv = "";
      for (int k = 0; k < bytePerHex; k++) {
        if (j + k >= n) {
          std::string zero = "0";
          conv += zero;  // 1\000000
        } else {
          conv += hexe[i][j + k];
        }
      }
      int res = std::stoi(conv, nullptr, 2);
      char r = c16(res);
      std::cout << r;
    }
    std::cout << " ";
  }
  std::cout << '\n';
  // std::string hexString = "10001";
  // int hexIndex = 0;
  // std::cout << std::stoi(hexString.substr(hexIndex, 1), nullptr, 16);

9
1 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0
0 0 0 0 1 0 0 0 0
0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1 0 0 0

800 400 200 100 080 040 020 010 001

9
1 1 1 1 1 1 1 1 1
0 1 0 0 0 0 0 0 0
0 0 1 0 1 0 1 0 0
0 0 0 1 0 1 0 0 0
0 0 0 0 1 0 1 0 0
0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 1 0
1 1 1 1 1 1 1 1 1
FF8 400 2A0 140 0A0 040 020 010 FF8

6
1 0 0 0 0 0
0 1 0 0 0 0
0 0 1 0 0 0
0 0 0 1 0 0
0 0 0 0 1 0
0 0 0 0 0 1

std::string str = "1234";
// std::getline(std::cin, str);
std::string new_str = "";
new_str += str[4];
new_str += "0";
std::cout << new_str;

  return 0;
}*/