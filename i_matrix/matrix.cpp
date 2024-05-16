#include "matrix.h"
#include <stdexcept>

Matrix::Matrix(size_t rows_num, size_t cols_num) 
  : Matrix()
{
  // TODO: интуиция...
  if (rows_num == 0 && cols_num == 0) {
    return;
  }

  // Либо оба нули, либо оба не нули.
  if (rows_num == 0 || cols_num == 0) {
    throw std::invalid_argument("Arguments must be either both zero or non zero.");
  }

  _rows_num = rows_num;
  _cols_num = cols_num;
  _storage = new double[rows_num * cols_num];
}

Matrix::Matrix(size_t rows_num, size_t cols_num, double def) 
  : Matrix(rows_num, cols_num)
{
  for (size_t i = 0; i < rows_num; i++)
  {
    for (size_t j = 0; j < cols_num; j++)
    {
      GetEl(i, j) = def;
    }
  }
  
}

void Matrix::CheckIJ(size_t i, size_t j) const {
  if (i >= _rows_num || j >= _cols_num) {
    throw std::out_of_range("Incorrect row or column.");
  }
}