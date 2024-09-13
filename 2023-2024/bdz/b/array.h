#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t N = 0>
class Array {
 public:
  T& operator[](size_t idx) {
    return arr_[idx];
  }

  const T& operator[](size_t idx) const {
    return arr_[idx];
  }

  T& At(size_t idx) {
    if (0 <= idx && idx < N) {
      return arr_[idx];
    }
    throw ArrayOutOfRange();
  }

  const T& At(size_t idx) const {
    if (0 <= idx && idx < N) {
      return arr_[idx];
    }
    throw ArrayOutOfRange();
  }

  T& Front() {
    return arr_[0];
  }

  const T& Front() const {
    return arr_[0];
  }

  T& Back() {
    return arr_[N - 1];
  }

  const T& Back() const {
    return arr_[N - 1];
  }

  T* Data() noexcept {
    return arr_;
  }

  const T* Data() const noexcept {
    return arr_;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return !N;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; i++) {
      arr_[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; i++) {
      std::swap(arr_[i], other.arr_[i]);
    }
  }

 public:
  T arr_[N]{};
};

template <class T, size_t N = 0>
size_t GetSize(const T (&)[N]) {
  return N;
}

template <class U>
size_t GetSize(const U&) {
  return 0;
}

template <class U>
size_t GetRank(const U&) {
  return 0;
}

template <class T, size_t N = 0>
size_t GetRank(const T (&array)[N]) {
  return 1 + GetRank(array[0]);
}

template <class U>
size_t GetNumElements(const U&) {
  return 1;
}

template <class T, size_t N = 0>
size_t GetNumElements(const T (&array)[N]) {
  return N * GetNumElements(array[0]);
}

#endif