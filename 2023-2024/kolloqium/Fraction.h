#ifndef FRACTION_H
#define FRACTION_H

struct Fraction {
 public:
  Fraction() 
  : num_(0)
  , dev_(1)
  {}

  Fraction(int num)
  : num_(num)
  , dev_(1)
  {}

  Fraction(int num, int dev) : num_(num) {
    dev_ = dev ? dev : 1;
  }

  Fraction(const Fraction& other) {
    num_ = other.num_;
    dev_ = other.dev_;
  }

  Fraction& operator=(const Fraction& other) {
    Fraction nfrac(other);
    Swap(*this, nfrac);
    return *this;
  }
  
  ~Fraction() = default;

 public:
  Fraction& operator+=(const Fraction& other) {
    num_ = num_ * other.dev_ + other.num_ * dev_;
    dev_ = dev_ * other.dev_;
    return *this;
  }

  Fraction& operator-=(const Fraction& other) {
    num_ = num_ * other.dev_ - other.num_ * dev_;
    dev_ = dev_ * other.dev_;
    return *this;
  }

  Fraction& operator*=(const Fraction& other) {
    num_ = num_ * other.num_;
    dev_ = dev_ * other.dev_;
    return *this;
  }

  Fraction& operator/=(const Fraction& other) {
    num_ = num_ * other.dev_;
    dev_ = dev_ * other.num_;
    return *this;
  }

  Fraction operator+(const Fraction& other) const {
    return Fraction(*this) += other;
  }

  Fraction operator-(const Fraction& other) const {
    return Fraction(*this) -= other;
  }

  Fraction operator*(const Fraction& other) const {
    return Fraction(*this) *= other;
  }

  Fraction operator/(const Fraction& other) const {
    return Fraction(*this) /= other;
  }

  bool operator==(const Fraction& other) const {
    return num_ == other.num_ && dev_ == other.dev_;
  }

  bool operator!=(const Fraction& other) const {
    return !(*this == other);
  }

  bool operator<(const Fraction& other) const {
    return num_ * other.dev_ < other.num_ * dev_;
  }


 public:
  std::string ToString() const {
    return std::to_string(num_) + ", " + std::to_string(dev_);
  }

 private:
  static void Swap(Fraction& first, Fraction& second) {
    std::swap(first.num_, second.num_);
    std::swap(first.dev_, second.dev_);
  }
 private:
  int num_;
  int dev_;
};

#endif