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

  class ConstRow {
    friend class Matrix;
  public:
    size_t size() const {
      return matrix_->GetColsNum();
    }

    double operator[](size_t colNum) const {
      return matrix_->GetEl(rowNum_, colNum);
    }

    // Для константной строки оператор, модифицирующий какой-либо её элемент не имеет смысла 
    //double& operator[](size_t colNum) {
      //return matrix_->GetEl(rowNum_, colNum);
    //}


    ConstRow(const Row& other)
    : rowNum_(other.rowNum_)
    , matrix_(other.matrix_)
    {}



  private:
    ConstRow(size_t rowNum, const Matrix* matrix)
    : rowNum_(rowNum)
    , matrix_(matrix)
    {}
  private:
    size_t rowNum_;
    const Matrix* matrix_;
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

  // TODO перенести в c++
  Matrix(const Matrix& other) 
    : rowsNum_{other.rowsNum_}
    , colsNum_{other.colsNum_}
    , storage_{other.storage_ ? new double[other.rowsNum_ * other.colsNum_] : nullptr}
  {
    for (size_t i = 0; i < other.rowsNum_; i++) {
      for (size_t j = 0; j < other.colsNum_; j++) {
        GetEl(i, j) = other.GetEl(i, j);
      }
    }
  }

  ~Matrix() {
    delete storage_; //Делать delete для nullptr безопасно
  }

  Matrix& operator=(const Matrix& rhs) {
    // Мы не будем это использовать, но вообще 
    // Matrix& lhs = *this;

    if (this == &rhs) {
      return *this;
    }

    // Вариант 1: "в лоб" 
    // Освобождаем предыдущий ресурс предыдущего значения перезаписываемого объекта.
    // delete[] storage_;
    // rowsNum_ = rhs.rowsNum_;
    // colsNum_ = rhs.colsNum_;
    // storage_ = new double[rowsNum_ * colsNum_];
    // // в этом месте может полететь исключение, и объект остается в неконсистентном состоянии
    // for (size_t i = 0; i < rowsNum_; i++) {
    //   for (size_t j = 0; j < colsNum_; j++) {
    //     GetEl(i, j) = rhs.GetEl(i, j);
    //   }
    // }

    // Вариант 2: идиома "copy and swap"
    // 1. Мы хотим свести все связанное с копированием к кунструктору копирования.
    // 2. Реализуем сппециальную функцию swap, которая коварно будет обменивать 
    // ресурсы которыми они владеют.
    // 3. Исключения нас не пугают.
    Matrix temp = rhs;
    Swap(*this, temp);
    

    return *this;
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



  //
  double GetEl(size_t i, size_t j) const {
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

  // Я определён в классе Matrix.
  ConstRow operator[] (size_t rowNum) const {
    return ConstRow(rowNum, this);
  }
private:
  // Проверяет невыход за диапозон номера строки и столбца матрицы.
  void CheckIJ(size_t i, size_t j) const;

  // TODO: cpp
  static void Swap(Matrix& m1, Matrix& m2) {
    std::swap(m1.rowsNum_, m2.rowsNum_);
    std::swap(m1.colsNum_, m2.colsNum_);
    std::swap(m1.storage_, m2.storage_);
  }

private:
  double* storage_;
  size_t rowsNum_;
  size_t colsNum_;
};

#endif