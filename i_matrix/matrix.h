#ifndef IMATRIX_MATRIX_H
#define IMATRIX_MATRIX_H

#include <cstddef>

class Matrix {
public:
  // Представляет объект строку.
  class Row {
    friend Matrix;
  public:
    size_t Size() const {
      return _matrix->GetColsNum();
    }

    double operator[](size_t col_num) const {
      return _matrix->GetEl(_row_num, col_num);
    }

    double& operator[](size_t col_num) {
      return _matrix->GetEl(_row_num, col_num);
    }
  private:
    Row(size_t row_num, Matrix* matrix)
      : _row_num(row_num)
      , _matrix(matrix)
    {};
  private:
    size_t _row_num;
    Matrix* _matrix;
  };
public:
  Matrix()
    : _storage(nullptr) // Выполняется ИНИЦИАЛИЗАЦИЯ объектов,
    , _rows_num(0)      // то есть вызов конструкторов соответствующих типов
    , _cols_num{0}      // Фигурные скобки тоже можно (ФСТМ)
  {
    // В следующих 3 строчках мы ПЕРЕЗАПИСЫВАЕМ ранее инициализированные объекты,
    // поэтому использовать это место для инициализации слишком поздно.
    // Используется оператор присваивания
    // _storage = nullptr;
    // _rows_num = 0;
    // _cols_num = 0;
  }

  // Инициализирует матрицу m*n.
  Matrix(size_t rows_num, size_t cols_num);

  // Инициализирует матрицу m*n, Устанавливет дефолтный элемент.
  Matrix(size_t rows_num, size_t cols_num, double def);

  ~Matrix() {
    delete _storage;  // Делать delete для nullptr безопасно.
  };
public:
  // Не делает проверку.
  // double GetElement(int i, int j) const {
  double At(size_t i, size_t j) const {
    // if (i >= _rows_num || j >= _cols_num) {
    //   throw std::out_of_range("Incorrect row or column.");
    // }
    CheckIJ(i, j);
    return _storage[CalcOffSet(i, j)];
  }

  // Неконстантная перегрузка для модификации элемента.
  double& At(size_t i, size_t j) {
    // if (i >= _rows_num || j >= _cols_num) {
    //   throw std::out_of_range("Incorrect row or column.");
    // }
    CheckIJ(i, j);
    return GetEl(i, j);
  }

  // Неконстантная перегрузка для модификации элемента. Без проверки на выход.
  double& GetEl(size_t i, size_t j) {
    return _storage[CalcOffSet(i, j)];
  }

  size_t CalcOffSet(size_t i, size_t j) const {
    return i * _cols_num + j;
  }

  size_t GetRowsNum() const {
    return _rows_num;
  }

  size_t GetColsNum() const {
    return _cols_num;
  }

  Row operator[](size_t row_num) {
    return Row(row_num, this);
  }
private:
  // Проверяет невыход за диапозон по номеру строки или столбца.
  void CheckIJ(size_t i, size_t j) const;
private:
  double* _storage;
  size_t _rows_num;
  size_t _cols_num;
};

#endif