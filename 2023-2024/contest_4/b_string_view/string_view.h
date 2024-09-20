#ifndef B_STRING_VIEW_H
#define B_STRING_VIEW_H


#include <stdexcept>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 public:
  StringView() 
  : str_(nullptr)
  , str_size_(0)
  {}

  StringView(const char* str); // NOLINT

  StringView(const char* str, size_t len);

 public:
  char operator[](size_t ind) const;

  char At(size_t ind) const;

  char Front() const;

  char Back() const;

  size_t Size() const {
    return str_size_;
  }

  size_t Length() const {
    return str_size_;
  }

  bool Empty() const {
    return str_ == nullptr || str_size_ == 0;
  }

  const char* Data() const {
    return str_;
  }

  void Swap(StringView& other);

  void RemovePrefix(size_t prefix_size);

  void RemoveSuffix(size_t suffix_size);

  StringView Substr(size_t pos, size_t count = -1);

 private:
  void CheckRange(size_t ind) const;
  
 private:
  const char* str_;
  size_t str_size_;
};

#endif