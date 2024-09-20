#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H

#include <stdexcept>

class BadWeakPtr : public std::exception {};

struct Counter {
  Counter() : strong_counter_(0), weak_counter_(0) {
  }
  Counter(size_t sc, size_t wc) : strong_counter_(sc), weak_counter_(wc) {
  }
  size_t strong_counter_;
  size_t weak_counter_;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
  friend WeakPtr<T>;

 public:
  SharedPtr() : pointer_(nullptr), counter_(nullptr) {
  }

  explicit SharedPtr(T* pointer) : pointer_(pointer) {
    counter_ = pointer ? new Counter(1, 0) : nullptr;
  }

  SharedPtr(const SharedPtr<T>& other) : pointer_(other.pointer_), counter_(other.counter_) {
    if (counter_) {
      counter_->strong_counter_++;
    }
  }

  SharedPtr& operator=(const SharedPtr<T>& other) {
    if (this == &other) {
      return *this;
    }

    FreeMemory();
    pointer_ = other.pointer_;
    counter_ = other.counter_;
    if (counter_) {
      counter_->strong_counter_++;
    }
    return *this;
  }

  explicit SharedPtr(const WeakPtr<T>& other) : pointer_{other.pointer_}, counter_(other.counter_) {
    if (other.Expired()) {
      throw BadWeakPtr();
    }
    if (counter_) {
      counter_->strong_counter_++;
    }
  }

  SharedPtr(SharedPtr&& other) noexcept : pointer_{other.pointer_}, counter_(other.counter_) {
    other.pointer_ = nullptr;
    other.counter_ = nullptr;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    FreeMemory();
    pointer_ = other.pointer_;
    counter_ = other.counter_;
    other.pointer_ = nullptr;
    other.counter_ = nullptr;
    return *this;
  }

  ~SharedPtr() {
    FreeMemory();
  }

 public:
  void Reset(T* ptr = nullptr) {
    FreeMemory();
    pointer_ = ptr;
    counter_ = ptr ? new Counter(1, 0) : nullptr;
  }

  void Swap(SharedPtr& up) {
    std::swap(pointer_, up.pointer_);
    std::swap(counter_, up.counter_);
  }

 public:
  T* Get() const {
    return pointer_;
  }

  size_t UseCount() const {
    return counter_ ? counter_->strong_counter_ : 0;
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
  void FreeMemory() {
    if (counter_ && (--(counter_->strong_counter_)) == 0) {
      delete pointer_;
      if (counter_->weak_counter_ == 0) {
        delete counter_;
      }
    }
  }

  explicit SharedPtr(T* pointer, Counter* counter) : pointer_(pointer), counter_(counter) {
    if (counter_) {
      counter_->strong_counter_++;
    }
  }

 private:
  T* pointer_;
  Counter* counter_;
};

template <class T>
class WeakPtr {
  friend SharedPtr<T>;

 public:
  WeakPtr() : pointer_(nullptr), counter_(nullptr) {
  }

  explicit WeakPtr(const SharedPtr<T>& shp) : pointer_(shp.pointer_), counter_(shp.counter_) {
    if (counter_) {
      counter_->weak_counter_++;
    }
  }

  WeakPtr(const WeakPtr<T>& other) : pointer_(other.pointer_), counter_(other.counter_) {
    if (counter_) {
      counter_->weak_counter_++;
    }
  }

  WeakPtr& operator=(const WeakPtr<T>& other) {
    if (this == &other) {
      return *this;
    }

    FreeMemory();
    pointer_ = other.pointer_;
    counter_ = other.counter_;
    if (counter_) {
      counter_->weak_counter_++;
    }
    return *this;
  }

  WeakPtr(WeakPtr&& other) noexcept : pointer_{other.pointer_}, counter_(other.counter_) {
    other.pointer_ = nullptr;
    other.counter_ = nullptr;
  }

  WeakPtr& operator=(WeakPtr&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    FreeMemory();
    pointer_ = other.pointer_;
    counter_ = other.counter_;
    other.pointer_ = nullptr;
    other.counter_ = nullptr;
    return *this;
  }

  ~WeakPtr() {
    FreeMemory();
  }

 public:
  void Reset() {
    FreeMemory();
    pointer_ = nullptr;
    counter_ = nullptr;
  }

  void Swap(WeakPtr& up) {
    std::swap(pointer_, up.pointer_);
    std::swap(counter_, up.counter_);
  }

 public:
  size_t UseCount() const {
    return counter_ ? counter_->strong_counter_ : 0;
  }

  bool Expired() const {
    return !UseCount();
  }

  SharedPtr<T> Lock() const {
    if (Expired()) {
      return SharedPtr<T>();
    }
    return SharedPtr<T>(pointer_, counter_);
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
  void FreeMemory() {
    if (counter_ && (--counter_->weak_counter_) == 0 && counter_->strong_counter_ == 0) {
      delete counter_;
    }
  }

 private:
  T* pointer_;
  Counter* counter_;
};

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif