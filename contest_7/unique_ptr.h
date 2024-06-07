#ifndef MY_UNIQUE_PTR_H
#define MY_UNIQUE_PTR_H

/*
Детали реализации

Шаблонный класс должен поддерживать:

    Конструктор по умолчанию (создает нулевой указатель).

    Конструктор от указателя (сохраняет указатель на объект).

    Конструктор копирования и копирующее присваивание должны отсутствовать.

    Перемещающий конструктор и перемещающее присваивание должны передавать владение объектом.

    Метод Release(), который отлучает класс от владения текущим ресурсом и возвращает указатель на него.

    Метод Reset(T* ptr = nullptr), меняет указатель, которым владеет объект (старый ресурс удаляется).

    Метод Swap(UniquePtr&).

    Метод Get(), возвращающий указатель на объект.

    Оператор разыменовывания operator*.

    Оператор "стрелочка" operator->.

    Явный оператор приведения к bool (operator bool).

*/

#include <memory>


template<class T> class UniquePtr {
 public:
  UniquePtr() : pointer_(nullptr) {
  }

  UniquePtr(T* pointer) : pointer_(pointer) {
  }

  UniquePtr(UniquePtr&&<T> up) noexcept : pointer_{ up.pointer_ } {
    up.data = nullptr;
  }

  UniquePtr& operator=(UniquePtr&&<T> up) noexcept {
    if (this == &up) {
      return *this;
    }

    pointer_ = up.pointer_;
    up.pointer_ = nullptr;
    return *this;
  }

  


 private:
  T* pointer_;
};

#endif