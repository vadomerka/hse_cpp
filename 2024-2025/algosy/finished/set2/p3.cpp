#include <algorithm>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

class Matrix {
private:
  std::vector<std::vector<int64_t>> data;
  size_t rows, cols;

public:
  // Конструктор от 2D вектора
  Matrix(const std::vector<std::vector<int64_t>> &input) {
    if (input.empty() || input[0].empty()) {
      return;
    }
    rows = input.size();
    cols = input[0].size();
    data = input;
  }

  Matrix(const Matrix &q1, const Matrix &q2, const Matrix &q3,
         const Matrix &q4) {
    rows = q1.data.size() * 2;
    cols = q1.data[0].size() * 2;
    data = {rows, std::vector<int64_t>(cols, 0)};
    size_t half = rows / 2;
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (i < half) {
          if (j < half) {
            data[i][j] = q1.data[i][j];
          } else {
            data[i][j] = q2.data[i][j - half];
          }
        } else {
          if (j < half) {
            data[i][j] = q3.data[i - half][j];
          } else {
            data[i][j] = q4.data[i - half][j - half];
          }
        }
      }
    }
  }

  // Метод для умножения двух матриц
  Matrix multiply(const Matrix &other) const {
    std::vector<std::vector<int64_t>> result(
        rows, std::vector<int64_t>(other.cols, 0));

    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < other.cols; ++j) {
        for (size_t k = 0; k < cols; ++k) {
          result[i][j] += data[i][k] * other.data[k][j];
        }
      }
    }

    return Matrix(result);
  }

  Matrix add(const Matrix &other) const {
    std::vector<std::vector<int64_t>> result(rows,
                                             std::vector<int64_t>(cols, 0));

    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        result[i][j] = data[i][j] + other.data[i][j];
      }
    }

    return Matrix(result);
  }

  // Метод для вычитания матриц
  Matrix subtract(const Matrix &other) const {
    std::vector<std::vector<int64_t>> result(rows,
                                             std::vector<int64_t>(cols, 0));

    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        result[i][j] = data[i][j] - other.data[i][j];
      }
    }

    return Matrix(result);
  }

  Matrix GetQ11() const {
    int64_t halfLen = rows / 2;
    std::vector<std::vector<int64_t>> res;
    for (int i = 0; i < halfLen; i++) {
      res.push_back(
          std::vector<int64_t>{data[i].begin(), data[i].begin() + halfLen});
    }
    return Matrix(res);
  }

  Matrix GetQ12() const {
    int64_t halfLen = rows / 2;
    std::vector<std::vector<int64_t>> res;
    for (int i = 0; i < halfLen; i++) {
      res.push_back(
          std::vector<int64_t>{data[i].begin() + halfLen, data[i].end()});
    }
    return Matrix(res);
  }

  Matrix GetQ21() const {
    int64_t halfLen = rows / 2;
    std::vector<std::vector<int64_t>> res;
    for (int i = halfLen; i < rows; i++) {
      res.push_back(
          std::vector<int64_t>{data[i].begin(), data[i].begin() + halfLen});
    }
    return Matrix(res);
  }

  Matrix GetQ22() const {
    int64_t halfLen = rows / 2;
    std::vector<std::vector<int64_t>> res;
    for (int i = halfLen; i < rows; i++) {
      res.push_back(
          std::vector<int64_t>{data[i].begin() + halfLen, data[i].end()});
    }
    return Matrix(res);
  }

  void print() const {
    for (const auto &row : data) {
      for (const auto &elem : row) {
        std::cout << elem << " ";
      }
      std::cout << std::endl;
    }
  }

  size_t size() const { return rows; }
};

Matrix strassen(const Matrix &m1, const Matrix &m2) {
  if (m1.size() <= 64) {
    return m1.multiply(m2);
  }

  Matrix a11{m1.GetQ11()};
  Matrix a12{m1.GetQ12()};
  Matrix a21{m1.GetQ21()};
  Matrix a22{m1.GetQ22()};
  Matrix b11{m2.GetQ11()};
  Matrix b12{m2.GetQ12()};
  Matrix b21{m2.GetQ21()};
  Matrix b22{m2.GetQ22()};

  /*
  Matrix s1{b12.subtract(b22)};
  Matrix s2{a11.add(a12)};
  Matrix s3{a21.add(a22)};
  Matrix s4{b21.subtract(b11)};
  Matrix s5{a11.add(a22)};
  Matrix s6{b11.add(b22)};
  Matrix s7{a12.subtract(a22)};
  Matrix s8{b21.add(b22)};
  Matrix s9{a11.subtract(a21)};
  Matrix s10{b11.add(b12)};

  Matrix p1{strassen(a11, s1)};
  Matrix p2{strassen(s2, b22)};
  Matrix p3{strassen(s3, b11)};
  Matrix p4{strassen(a22, s4)};
  Matrix p5{strassen(s5, s6)};
  Matrix p6{strassen(s7, s8)};
  Matrix p7{strassen(s9, s10)};

  Matrix c11{p5.add(p4.add(p6.subtract(p2)))}; // p5 + (p4 + (p6 - p2))
  Matrix c12{p1.add(p2)};
  Matrix c21{p3.add(p4)};
  Matrix c22{p5.add(p1.subtract(p3.add(p7)))}; // p5 + (p1 - (p3 + p7))
  */

  Matrix h1 {strassen(a11, b11)};
  Matrix h2 {strassen(a12, b21)};
  Matrix h3 {strassen(a11, b12)};
  Matrix h4 {strassen(a12, b22)};
  Matrix h5 {strassen(a21, b11)};
  Matrix h6 {strassen(a22, b21)};
  Matrix h7 {strassen(a21, b12)};
  Matrix h8 {strassen(a22, b22)};

  Matrix c11 {h1.add(h2)};
  Matrix c12 {h3.add(h4)};
  Matrix c21 {h5.add(h6)};
  Matrix c22 {h7.add(h8)};
  return Matrix(c11, c12, c21, c22);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n = 0;
  std::cin >> n;
  std::vector<std::vector<int64_t>> mat1_data(n);
  std::vector<std::vector<int64_t>> mat2_data(n);
  int64_t x = 0;

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      std::cin >> x;
      mat1_data[i].push_back(x);
    }
  }

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      std::cin >> x;
      mat2_data[i].push_back(x);
    }
  }

  Matrix mat1(mat1_data);
  Matrix mat2(mat2_data);

  Matrix result = strassen(mat1, mat2);
  result.print();
  return 0;
  /*
4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
  */
}
