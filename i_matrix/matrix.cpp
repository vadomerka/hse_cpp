#include "matrix.h"

#include <stdexcept>

Matrix::Matrix(size_t rowsNum, size_t colsNum) 
  : Matrix()
{
  if (!rowsNum && !colsNum) {
    return;
  }

  //Либо оба нули, либо оба не нули.
  if (!rowsNum || !colsNum) {
    throw std::invalid_argument{"Arguments must be either both zero or non-zero."};
  }

  rowsNum_ = rowsNum;
  colsNum_ = colsNum;
  storage_ = new double[rowsNum * colsNum];

}

Matrix::Matrix(size_t rowsNum, size_t colsNum, double def)
  : Matrix(rowsNum, colsNum)
  {
    for (size_t i = 0; i < rowsNum; ++i) {
      for (size_t j = 0; j < colsNum; ++j) {
        GetEl(i, j) = def;
      }
    }
  }

void Matrix::CheckIJ(size_t i, size_t j) const {
  if (i >= rowsNum_ || j >= colsNum_) {
    throw std::out_of_range{"Incorrect row or column."};
  }
}