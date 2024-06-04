#ifndef MYMATRIX_MATRIX_H
#define MYMATRIX_MATRIX_H

#include <cstddef> 
//#include <stdexcept> детали реализации в интерфейсе появляться не должны

class Matrix {
public:
  //Представляет объект строку.
  class Row {
    friend class Matrix;
  public:
    size_t size() const {
      return matrix_->GetColsNum();
    }

    double operator[](size_t colNum) const {
      return matrix_->GetEl(rowNum_, colNum);
    }

    double& operator[](size_t colNum) {
      return matrix_->GetEl(rowNum_, colNum);
    }

  private:
    Row(size_t rowNum, Matrix* matrix)
    : rowNum_(rowNum)
    , matrix_(matrix)
    {}
  private:
    size_t rowNum_;
    Matrix* matrix_;
  };

public:
  Matrix()
    : storage_(nullptr) // ВЫПОЛНЯЕТСЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТА, А НЕ ПРИСВАИВАНИЕ, ТО ЕСТЬ ВЫЗОВ КОНСТРУКТОРОВ СООТВЕТСВУЮЩИХ ТИПОВ
    , rowsNum_(0)
    , colsNum_{0}  //фигурные скобки тоже можно 
  {
    //В следующих трех строчках мы перезаписали раннее инициализированные объекты,
    //поэтому использовать это место для инициализации, слишком поздно, РАБОТАЕТ ОПЕРАТОР ПРИСВАИВАНИЯ, Т.К КОНСТРУКТОР ПО УМОЛЧАНИЮ УЖЕ ОТРАБОТАЛ
    //_storage = nullptr;
    //rowNum = 0;
    //colNum = 0;
  }
  
  //инициализирует матрицу n на m.
  Matrix(size_t rowsNum, size_t colsNum);

  //инициализирует матрицу n на m, устанавливая дефолтный элемент.
  Matrix(size_t rowsNum, size_t colsNum, double def);

  ~Matrix() {
    delete storage_; //Делать delete для nullptr безопасно
  }

public:
  //не делает проверку. Для проверки нужно сделать отдельную функцию at: if(i > rowsNum) {throw std::out_of_range}
  //double GetElement(int i, int j) const {
  double At(size_t i, size_t j) const {
    // if (i >= rowsNum_ || j >= colsNum_) {
    //   throw std::out_of_range{"Incorrect row or column."};
    // }
    CheckIJ(i, j);
    return storage_[CalcOffset(i, j)];
  }

  //Неконстантная перегрузка для модифиакции ij элемента
  double& At(size_t i, size_t j) {
    // if (i >= rowsNum_ || j >= colsNum_) {
    //   throw std::out_of_range{"Incorrect row or column."};
    // }
    CheckIJ(i, j);
    return GetEl(i, j);
    //return storage_[CalcOffset(i, j)];
  }

  //Неконстантная перегрузка для модифиакции ij элемента без проверки на выход.
  double& GetEl(size_t i, size_t j) {
    return storage_[CalcOffset(i, j)];
  }

  size_t CalcOffset(size_t i, size_t j) const {
    return i * colsNum_ + j;
  }
  
  size_t GetRowsNum() const {
    return rowsNum_;
  }

  size_t GetColsNum() const {
    return colsNum_;
  }

  Row operator[](size_t rowNum) {
    return Row(rowNum, this);
  }
private:
  //Проверяет невыход за диапозон номера строки и столбца матрицы.
  void CheckIJ(size_t i, size_t j) const;

private:
  double* storage_;
  size_t rowsNum_;
  size_t colsNum_;
};

#endif