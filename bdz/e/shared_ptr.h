#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H

template <class T>
class SharedPtr {
 public:
  SharedPtr() : pointer_(nullptr), strong_counter_(nullptr) {
  }

  explicit SharedPtr(T* pointer) : pointer_(pointer), strong_counter_(pointer ? new size_t(1) : nullptr) {
  }

  SharedPtr(const SharedPtr<T>& other) : pointer_(other.pointer_), strong_counter_(other.strong_counter_) {
    if (strong_counter_) {
      (*strong_counter_)++;
    }
  }

  SharedPtr& operator=(const SharedPtr<T>& other) {
    if (this == &other) {
      return *this;
    }
    this->~SharedPtr();
    pointer_ = other.pointer_;
    strong_counter_ = other.strong_counter_;
    if (strong_counter_) {
      (*strong_counter_)++;
    }
    return *this;
  }

  SharedPtr(SharedPtr&& other) noexcept : pointer_{other.pointer_}, strong_counter_(other.strong_counter_) {
    other.pointer_ = nullptr;
    other.strong_counter_ = nullptr;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    this->~SharedPtr();
    pointer_ = other.pointer_;
    strong_counter_ = other.strong_counter_;
    other.pointer_ = nullptr;
    other.strong_counter_ = nullptr;
    return *this;
  }

  ~SharedPtr() {
    if (strong_counter_ && (--(*strong_counter_)) == 0) {
      delete pointer_;
      delete strong_counter_;
    }
  }

 public:
  void Reset(T* ptr = nullptr) {
    this->~SharedPtr();
    pointer_ = ptr;
    strong_counter_ = ptr ? new size_t(1) : nullptr;
  }

  void Swap(SharedPtr& up) {
    std::swap(pointer_, up.pointer_);
    std::swap(strong_counter_, up.strong_counter_);
  }

 public:
  T* Get() const {
    return pointer_;
  }

  size_t UseCount() const {
    return strong_counter_ ? *strong_counter_ : 0;
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
  size_t* strong_counter_;
};

#endif