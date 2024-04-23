#include "matrix.h"

Matrix::Matrix(size_t rows_num, size_t cols_num) 
  : Matrix()
{
  // TODO: интуиция...
  if (rows_num == 0 && cols_num == 0) {
    return;
  }

  // Либо оба нули, либо оба не нули.
  if (rows_num == 0 || cols_num == 0) {
    // TODO: throw runtime exception
  }
}