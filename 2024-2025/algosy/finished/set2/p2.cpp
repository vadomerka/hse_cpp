/*
#include <iostream>
#include <deque>
#include <string>
#include <ios>


int toDigit(char ch) { return ch - '0'; }


struct LongNumber {
  std::deque<int8_t> arr;
  int _sign = 1;

  LongNumber() {}

  LongNumber(std::deque<int8_t> nArr) {
    for (size_t i = 0; i < nArr.size(); i++) {
      arr.push_back(nArr[i]);
    }
    trim();
  }

  LongNumber(std::deque<int8_t> nArr, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
      arr.push_back(nArr[i]);
    }
    trim();
  }

  LongNumber(std::string num_line) {
    if (!num_line.size()) {
      arr.push_back(0);
    }
    for (size_t i = 0; i < num_line.size(); i++) {
      arr.push_front(toDigit(num_line[i]));
    }
    trim();
  }

  void print() {
    for (size_t i = 0; i < arr.size(); i++) {
      size_t output = arr[arr.size() - i - 1];
      std::cout << output;
    }
    std::cout << '\n';
  }

  std::string toString() {
    std::string str = "";
    if (size() == 0) {
      str = "0";
    }
    for (size_t i = 0; i < size(); i++) {
      str += arr[arr.size() - i - 1] + '0';
    }
    return str;
  }

  size_t size() const {
    return arr.size();
  }

  void reSize(size_t newSize) {
    while(newSize > arr.size()) {
      arr.push_back(0);
    }
  }

  void trim() {
    if (size() <= 1) return;
    size_t k = size() - 1;
    while(size() - 1 && !(arr[k])) {
      arr.pop_back();
      k--;
    }
  }

  bool operator>(const LongNumber& other) const {
    if (!size()) return false;
    if (size() > other.size()) return true;
    else if (size() == other.size()) {
      return arr[size() - 1] > other.arr[size() - 1];
    }
    return false;
  }

  LongNumber operator+=(const LongNumber& other) {
    if (size() < other.size()) {
      reSize(other.size());
    }
    size_t minSize = std::min(other.size(), size());
    reSize(size() + 1);
    for (int i = 0; i < minSize; i++) {
      size_t k = i;
      arr[i] += other.arr[i];
      while (arr[k] > 9) {
        int8_t tmp = arr[k];
        arr[k] = tmp % 10;
        arr[++k] += tmp / 10;
      }
    }

    trim();
    return *this;
  }

  LongNumber operator+(const LongNumber& other) {
    return (LongNumber(*this) += other);
  }

  LongNumber operator-=(const LongNumber& other) {
    // if (other._sign * _sign * -1 == 1) return (*this += other);
    // _sign = *this > other ? 1 : -1;
    if (size() < other.size()) {
      reSize(other.size());
    }
    size_t minSize = std::min(other.size(), size());
    int debt = 0;
    for (int i = 0; i < minSize; i++) {
      if (debt) {
        arr[i] -= debt;
        debt = 0;
      }
      int sm = arr[i] - other.arr[i];
      if (sm < 0) {
        debt += 1;
        sm = 10 + sm;
      }
      arr[i] = sm;
    }
    if (size() > minSize && debt) {
      arr[minSize] -= debt;
      debt = 0;
    }

    trim();
    return *this;
  }

  LongNumber operator*(LongNumber& other) {
    size_t maxSize = std::max(other.size(), size());
    if (other.size() != size()) {
      other.reSize(maxSize);
      reSize(maxSize);
    }

    std::deque<int8_t> res(2 * maxSize, 0);
    for (int i = 0; i < maxSize; i++) {
      for (int j = 0; j < maxSize; j++) {
        size_t k = i + j;
        int mlt = arr[j] * other.arr[i];
        res[k] += mlt;
        while (res[k] > 9) {
          int8_t tmp = res[k];
          res[k] = tmp % 10;
          res[++k] += tmp / 10;
        }
      }
    }

    trim();
    other.trim();
    return LongNumber(res);
  }

  LongNumber shift(size_t step) {
    for (int i = 0; i < step; i++) {
      arr.push_front(0);
    }
    return *this;
  }
};


LongNumber karatsuba(LongNumber& n1, LongNumber& n2) {
  if (n1.size() <= 64 || n2.size() <= 64) {
    return n1 * n2;
  }

  size_t maxSize = std::max(n1.size(), n2.size());
  if (n2.size() != n1.size()) {
    n1.reSize(maxSize);
    n2.reSize(maxSize);
  }
  size_t mid = maxSize / 2;
  LongNumber a1 {n1.arr, mid, maxSize};
  LongNumber a0 {n1.arr, 0, mid};
  LongNumber b1 {n2.arr, mid, maxSize};
  LongNumber b0 {n2.arr, 0, mid};

  LongNumber r1 {karatsuba (a1, b1)};
  LongNumber r2 {karatsuba (a0, b0)};
  LongNumber s3 {a1 + a0};
  LongNumber s4 {b1 + b0};
  LongNumber r3 {karatsuba (s3, s4)};
  r3 -= r1;
  r3 -= r2;

  LongNumber ans {r1.shift(mid * 2) + r3.shift(mid) + r2};
  return ans;
}


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);        
  std::string n1 = "";
  std::string n2 = "";
  std::getline(std::cin, n1);
  std::getline(std::cin, n2);

  while (n1[0] == '0' && n1.size() > 1) {
    n1.erase(0, 1);
  }

  while (n2[0] == '0' && n2.size() > 1) {
    n2.erase(0, 1);
  }

  if (n1 == "0" || n2 == "0") {
    std::cout << "0";
    return 0;
  } 
  if (n1 == "1") {
    std::cout << n2;
    return 0;
  }
  if (n2 == "1") {
    std::cout << n1;
    return 0;
  }

  // for (int i = 0; i < 10000; i++) {
  //   LongNumber n11 {std::to_string(i)};
  //   for (int j = 0; j < 10000; j++) {
  //     LongNumber n22 {std::to_string(j)};
  //     // LongNumber n3(karatsuba(n11, n22));
  //     LongNumber n3(n11 * n22);
  //     std::string left = n3.toString();
  //     std::string right = std::to_string(i * j);
  //     if (left != right) {
  //       std::cout << i << " " << j << "\t";
  //       n3.print();
  //     }
  //   }
  // }
  LongNumber n11 {n1};
  LongNumber n22 {n2};
  LongNumber n3(karatsuba(n11, n22));
  n3.print();
  // while (n1 != "\n") {
  //   std::cout << "Введите число" << '\n';
  //   LongNumber n11 {n1};
  //   LongNumber n22 {n2};
  //   LongNumber n3(karatsuba(n11, n22));
  //   LongNumber n4(n11 * n22);
  //   std::string left = n3.toString();
  //   std::string right = n4.toString();
  //   if (left != right) {
  //     std::cout << n1 << " " << n2 << "\t";
  //     n3.print();
  //     n4.print();
  //   }
  // }

  return 0;
}
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ios>


int toDigit(char ch) { return ch - '0'; }
char toChar(int d) { return d + '0'; }

void reSize(std::string& n1, size_t newSize) {
  n1 = std::string(newSize - n1.size(), '0') + n1;
}

std::string shift(std::string& n1, size_t count) {
  n1 = n1 + std::string(count, '0');
  return n1;
}

void trim(std::string &n1) {
  size_t pos = n1.find_first_not_of('0');
  if (pos == std::string::npos) {
    n1 = "0";
  } else {
    n1 = n1.substr(pos);
  }
}

std::string naiive(const std::string& n1, const std::string& n2) {
  std::vector<int> res(n1.size() + n2.size(), 0);
  for (int i = n1.size() - 1; i >= 0; i--) {
    for (int j = n2.size() - 1; j >= 0; j--) {
      int mlt = (toDigit(n1[i]) * toDigit(n2[j]));

      size_t k = i + j + 1;
      int tmp = res[k] + mlt;
      res[k] = tmp % 10;
      res[k - 1] += tmp / 10;
    }
  }
  
  std::string rStr = "";
  for (size_t i = 0; i < res.size(); i++) {
    rStr.push_back(toChar(res[i]));
  }
  trim(rStr);
  return rStr;
}

std::string summa(const std::string& n1, const std::string& n2) {
  size_t maxSize = std::max(n1.size(), n2.size());
  std::string res;
  int debt = 0;
  for (size_t i = 0; i < maxSize; i++) {
    int d1 = (i < n1.size()) ? toDigit(n1[n1.size() - i - 1]) : 0;
    int d2 = (i < n2.size()) ? toDigit(n2[n2.size() - i - 1]) : 0;
    int sum = d1 + d2 + debt;
    res.push_back(toChar(sum % 10));
    debt = sum / 10;
  }
  if (debt) {
    res.push_back(toChar(debt));
  }

  std::reverse(res.begin(), res.end());
  return res;
}

std::string diff(const std::string& n1, const std::string& n2) {
  // size_t maxSize = std::max(n1.size(), n2.size());
  std::string res;
  int debt = 0;
  for (int i = 0; i < n1.size(); i++) {
    int d1 = toDigit(n1[n1.size() - i - 1]);
    int d2 = (i < n2.size()) ? toDigit(n2[n2.size() - i - 1]) : 0;
    int dif = d1 - d2 - debt;
    if (dif < 0) {
      dif += 10;
      debt = 1;
    } else {
      debt = 0;
    }
    res.push_back(toChar(dif));
  }

  std::reverse(res.begin(), res.end());
  trim(res);
  return res;
}

std::string karatsuba(std::string& n1, std::string& n2) {
  if (n1.size() == 1 || n2.size() == 1) {
    return std::to_string(std::stoll(n1) * std::stoll(n2));
  }

  if (n1.size() <= 64 || n2.size() <= 64) {
    return naiive(n1, n2);
  }

  size_t maxSize = std::max(n1.size(), n2.size());
  if (n2.size() != n1.size()) {
    reSize(n1, maxSize);
    reSize(n2, maxSize);
  }
  size_t mid = maxSize / 2;
  std::string a0 = n1.substr(maxSize - mid, maxSize);
  std::string a1 = n1.substr(0, maxSize -mid);
  std::string b0 = n2.substr(maxSize - mid, maxSize);
  std::string b1 = n2.substr(0, maxSize - mid);

  std::string r1 {karatsuba (a1, b1)};
  std::string r2 {karatsuba (a0, b0)};
  std::string s3 = summa(a1, a0);
  std::string s4 = summa(b1, b0);
  std::string r3 {karatsuba (s3, s4)};
  r3 = diff(r3, r1);
  r3 = diff(r3, r2);
  std::string ans = summa(summa(shift(r1, mid * 2), shift(r3, mid)), r2);
  trim(ans);
  return ans;
}


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);        
  std::string n1 = "";
  std::string n2 = "";
  std::getline(std::cin, n1);
  std::getline(std::cin, n2);

  while (n1[0] == '0' && n1.size() > 1) {
    n1.erase(0, 1);
  }

  while (n2[0] == '0' && n2.size() > 1) {
    n2.erase(0, 1);
  }

  if (n1 == "0" || n2 == "0") {
    std::cout << "0";
    return 0;
  } 
  if (n1 == "1") {
    std::cout << n2;
    return 0;
  }
  if (n2 == "1") {
    std::cout << n1;
    return 0;
  }
  
  std::cout << karatsuba(n1, n2);
  return 0;
}