#include "string_view.h"

StringView::StringView(const char* str) : str_(str)
, str_size_(0)
{
  if (str == nullptr) {
    return;
  }
  while (*(str_ + str_size_) != '\0') {
    str_size_++;
  }
}

StringView::StringView(const char* str, size_t len) 
: StringView()
{
  if (str == nullptr) {
    return;
  }
  str_ = str;
  while (*(str_ + str_size_) != '\0' && str_size_ < len) {
    str_size_++;
  }
}

char StringView::operator[](size_t ind) const {
  if (str_ == nullptr) {
    return '\0';
  }
  return str_[ind];
}

char StringView::At(size_t ind) const {
  if (str_ == nullptr) {
    return '\0';
  }
  CheckRange(ind);
  return str_[ind];
}

char StringView::Front() const {
  if (str_ == nullptr) {
    return '\0';
  }
  return str_size_ > 0 ? str_[0] : '\0';
}

char StringView::Back() const {
  if (str_ == nullptr) {
    return '\0';
  }
  return str_size_ > 0 ? str_[str_size_ - 1] : '\0';
}

void StringView::Swap(StringView& other) {
  if (this == &other) {
    return;
  }
  std::swap(str_, other.str_);
  std::swap(str_size_, other.str_size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
  if (str_ == nullptr) {
    return;
  }
  if (prefix_size > str_size_) {
    prefix_size = str_size_;
  }
  str_ += prefix_size;
  str_size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  if (suffix_size > str_size_) {
    suffix_size = str_size_;
  }
  str_size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  if (str_ == nullptr) {
    return {};
  }
  CheckRange(pos);
  return {str_ + pos, std::min(count, Size() - pos)};
}

void StringView::CheckRange(size_t ind) const {
  if (ind >= str_size_) {
    throw StringViewOutOfRange();
  }
}