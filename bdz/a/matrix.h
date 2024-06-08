#ifndef BDZ_MATRIX_H
#define BDZ_MATRIX_H

#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};


template <typename T, size_t ROWNUM, size_t COLNUM>
class Matrix {
 public:
  T data_[ROWNUM][COLNUM]{};

 public:
  Matrix& operator=(const std::initializer_list<T>& arr) {
    if (arr.size() > ROWNUM * COLNUM) {
      return *this;
    }
    auto it = arr.begin();
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        data_[i][j] = it != arr.end() ? (*it++) : T();
      }
    }
    return *this;
  }

 public:
  T& operator()(size_t r, size_t c) {
    return data_[r][c];
  }

  const T& operator()(size_t r, size_t c) const {
    return data_[r][c];
  }

  T& At(size_t r, size_t c) {
    if (r >= ROWNUM || c >= COLNUM) {
      throw MatrixOutOfRange();
    }
    return data_[r][c];
  }

  const T& At(size_t r, size_t c) const {
    if (r >= ROWNUM || c >= COLNUM) {
      throw MatrixOutOfRange();
    }
    return data_[r][c];
  }

 public:
  friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    if (ROWNUM == 0 || COLNUM == 0) {
      return os;
    }
    for (size_t i = 0; i < ROWNUM; i++) {
      os << m.data_[i][0];
      for (size_t j = 1; j < COLNUM; j++) {
        os << " " << m.data_[i][j];
      }
      os << '\n';
    }
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Matrix& m) {
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        is >> m.data_[i][j];
      }
    }
    return is;
  }
 
  Matrix& operator+=(const Matrix& other) {
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        data_[i][j] += other.data_[i][j];
      }
    }
    return *this;
  }

  Matrix operator+(const Matrix& other) const {
    return Matrix(*this) += other;
  }

  Matrix& operator-=(const Matrix& other) {
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        data_[i][j] -= other.data_[i][j];
      }
    }
    return *this;
  }

  Matrix operator-(const Matrix& other) const {
    return Matrix(*this) -= other;
  }

  Matrix<T, ROWNUM, COLNUM>& operator*=(const Matrix<T, COLNUM, COLNUM>& other) {
    T tmp[ROWNUM][COLNUM]{};
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        for (size_t k = 0; k < COLNUM; k++) {
          tmp[i][j] += data_[i][k] * other.data_[k][j];
        }
      }
    }
    DataCopy(tmp);
    return *this;
  }

  template<size_t DEPTH>
  Matrix<T, ROWNUM, DEPTH> operator*(const Matrix<T, COLNUM, DEPTH>& other) const {
    Matrix<T, ROWNUM, DEPTH> tmp_matrix;
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < DEPTH; j++) {
        for (size_t k = 0; k < COLNUM; k++) {
          tmp_matrix.data_[i][j] += data_[i][k] * other.data_[k][j];
        }
      }
    }
    return tmp_matrix;
  }

  Matrix& operator*=(const T& val) {
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        data_[i][j] *= val;
      }
    }
    return *this;
  }

  Matrix operator*(const T& val) const {
    return Matrix(*this) *= val;
  }

  friend Matrix operator*(const T& val, const Matrix& matrix) {
    return Matrix(matrix) *= val;
  }

  Matrix& operator/=(const T& val) {
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        data_[i][j] /= val;
      }
    }
    return *this;
  }

  Matrix operator/(const T& val) const {
    return Matrix(*this) /= val;
  }

  bool operator==(const Matrix& other) const {
    if (this == &other) {
      return true;
    }
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        if (data_[i][j] != other.data_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix& other) const {
    return !((*this) == other);
  }

 public:
  size_t RowsNumber() const {
    return ROWNUM;
  }

  size_t ColumnsNumber() const {
    return COLNUM;
  }

 private:
  void DataCopy(const T (&values)[ROWNUM][COLNUM]) {
    for (size_t i = 0; i < ROWNUM; i++) {
      for (size_t j = 0; j < COLNUM; j++) {
        data_[i][j] = values[i][j];
      }
    }
  }
};

template <typename T, size_t ROWNUM, size_t COLNUM>
Matrix<T, COLNUM, ROWNUM> GetTransposed(const Matrix<T, ROWNUM, COLNUM>& other) {
  Matrix<T, COLNUM, ROWNUM> nm;
  for (size_t i = 0; i < ROWNUM; i++) {
    for (size_t j = 0; j < COLNUM; j++) {
      nm.data_[j][i] = other.data_[i][j];
    }
  }
  return nm;
}

#endif