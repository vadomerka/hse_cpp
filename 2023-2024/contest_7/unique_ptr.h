#ifndef MY_UNIQUE_PTR_H
#define MY_UNIQUE_PTR_H

template <class T>
class UniquePtr {
 public:
  UniquePtr() : pointer_(nullptr) {
  }

  explicit UniquePtr(T* pointer) : pointer_(pointer) {
  }

  UniquePtr(const UniquePtr<T>&) = delete;
  UniquePtr& operator=(const UniquePtr<T>& u) = delete;

  UniquePtr(UniquePtr&& up) noexcept : pointer_{up.pointer_} {
    up.pointer_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& up) noexcept {
    if (this == &up) {
      return *this;
    }

    delete pointer_;
    pointer_ = up.pointer_;
    up.pointer_ = nullptr;
    return *this;
  }

  ~UniquePtr() {
    delete pointer_;
  }

 public:
  T* Release() {
    T* tmp_pointer = pointer_;
    pointer_ = nullptr;
    return tmp_pointer;
  }

  void Reset(T* ptr = nullptr) {
    delete pointer_;
    pointer_ = ptr;
  }

  void Swap(UniquePtr& up) {
    std::swap(pointer_, up.pointer_);
  }

 public:
  T* Get() const {
    return pointer_;
  }

  T& operator*() const {
    return *pointer_;
  }

  T* operator->() const {
    return pointer_;
  }

  explicit operator bool() const {
    return pointer_;
  }

 private:
  T* pointer_;
};

#endif