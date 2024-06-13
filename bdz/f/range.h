#ifndef RANGE_H
#define RANGE_H

#include <cmath>
#include <iterator>


class Range {
 public:
  Range() = delete;

  explicit Range(int end) : start_(0), end_(end), step_(1) {
  }

  Range(int start, int end, int step = 1) : start_(start), end_(end), step_(step) {
  }

 public:
  struct RangeIterator {
   public:
    using iterator_category = std::forward_iterator_tag;  // NOLINT
    using difference_type = std::ptrdiff_t;               // NOLINT
    using value_type = int64_t;                           // NOLINT

    explicit RangeIterator(value_type cur_num, difference_type istep = 1) : cur_num_(cur_num), istep_(istep) {
    }

   public:
    value_type operator*() const {
      return cur_num_;
    }

    RangeIterator& operator++() {
      cur_num_ += istep_;
      return *this;
    }

    RangeIterator operator++(int) {
      RangeIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    RangeIterator& operator--() {
      cur_num_ -= istep_;
      return *this;
    }

    RangeIterator operator--(int) {
      RangeIterator tmp = *this;
      --(*this);
      return tmp;
    }

    friend bool operator==(const RangeIterator& a, const RangeIterator& b) {
      return a.cur_num_ == b.cur_num_;
    };
    friend bool operator!=(const RangeIterator& a, const RangeIterator& b) {
      return a.cur_num_ != b.cur_num_;
    };

   private:
    value_type cur_num_;
    difference_type istep_;
  };

  using ReverseRangeIterator = std::reverse_iterator<RangeIterator>;

 public:
  RangeIterator begin() const {  // NOLINT
    return RangeIterator(start_, step_);
  }

  RangeIterator end() const {  // NOLINT
    int len = end_ - start_;
    int step_count = 0;
    if (len * step_ <= 0) {
      step_count = 0;
    } else {
      step_count = len / step_ + (Module(len, step_) ? 1 : 0);
    }
    int the_end = start_ + step_ * step_count;
    return RangeIterator(the_end, step_);
  }

  ReverseRangeIterator rbegin() const {  // NOLINT
    // int c = start_;
    // for (int i : *this) {
    //   c = i;
    // }
    return std::reverse_iterator<RangeIterator>(end());
  }

  ReverseRangeIterator rend() const {  // NOLINT
    // int the_rstart = start_ - step_;
    // int len = end_ - start_;
    // if (len * step_ <= 0) {
    //   the_rstart = start_;
    // }
    return std::reverse_iterator<RangeIterator>(begin());
  }

 private:
  int Module(int num, int base) const {
    base = std::abs(base);
    int res = std::abs(num) % base;
    return (num >= 0 || !res) ? res : base - res;
  }

 private:
  int start_;
  int end_;
  int step_;
};

#endif