#ifndef IMATRIX_MATRIX_H
#define IMATRIX_MATRIX_H

#include <cstddef>

class Matrix {
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
private:    
  double* _storage;
  size_t _rows_num;
  size_t _cols_num;
};

#endif