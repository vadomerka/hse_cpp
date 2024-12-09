#ifndef A_RATIONAL_H
#define A_RATIONAL_H

#include <cstdint>
#include <stdexcept>

class Rational {
public:
  Rational()
      : numerator_(0), denominator_(1){};

  Rational(int32_t n1); // NOLINT

  Rational(int32_t n1, int32_t n2);

  Rational(const Rational &other) = default;

  Rational &operator=(const Rational &other) = default;

public:
  int32_t GetNumerator(void) const;
  int32_t GetDenominator() const;
  void SetNumerator(int32_t n1);
  void SetDenominator(int32_t n2);

#pragma region operators
  Rational &operator*=(const Rational &other);

  Rational &operator/=(const Rational &other);

  Rational &operator+=(const Rational &other);

  Rational &operator-=(const Rational &other);

  Rational &operator++();

  Rational &operator--();

  Rational operator*(const Rational &other) const {
    return Rational(*this) *= other;
  }

  Rational operator/(const Rational &other) const {
    return Rational(*this) /= other;
  }

  Rational operator+(const Rational &other) const {
    return Rational(*this) += other;
  }

  Rational operator-(const Rational &other) const {
    return Rational(*this) -= other;
  }

  Rational operator+() const { return (*this); }

  Rational operator-() const { return {-numerator_, denominator_}; }

  Rational operator++(int);

  Rational operator--(int);

  friend std::ostream& operator<<(std::ostream& os, const Rational& f);
  friend std::istream& operator>>(std::istream& is, Rational& f);
#pragma endregion

#pragma region Bool operators
  bool operator==(const Rational &other) const {
    return numerator_ == other.numerator_ && denominator_ == other.denominator_;
  };
  bool operator!=(const Rational &other) const { 
    return !(*this == other); 
  };
  bool operator<(const Rational &other) const {
    return numerator_ * other.denominator_ < other.numerator_ * denominator_;
  };
  bool operator>(const Rational &other) const {
    return !(*this < other) && *this != other;
  };
  bool operator<=(const Rational &other) const { 
    return !(*this > other); 
  };
  bool operator>=(const Rational &other) const { 
    return !(*this < other); 
  };

  bool operator==(int32_t num) const {
    return numerator_ == num && denominator_ == 1;
  };
  bool operator!=(int32_t num) const { 
    return !(*this == num);
  };
  bool operator<(int32_t num) const {
    return numerator_ < num * denominator_;
  };
  bool operator>(int32_t num) const {
    return !(*this < num) && *this != num;
  };
  bool operator<=(int32_t num) const { 
    return !(*this > num); 
  };
  bool operator>=(int32_t num) const { 
    return !(*this < num);
  };

  friend bool operator==(int32_t num, const Rational &other) {
    return num == other.numerator_ && 1 == other.denominator_;
  };
  friend bool operator!=(int32_t num, const Rational &other) { 
    return !(num == other);
  };
  friend bool operator<(int32_t num, const Rational &other) {
    return num * other.denominator_ < other.numerator_;
  };
  friend bool operator>(int32_t num, const Rational &other) {
    return !(num < other) && num != other;
  };
  friend bool operator<=(int32_t num, const Rational &other) { 
    return !(num > other); 
  };
  friend bool operator>=(int32_t num, const Rational &other) { 
    return !(num < other); 
  };
#pragma endregion

private:
  int32_t numerator_;
  int32_t denominator_;

  void SimpleSet(int32_t num, int32_t div);
  void CheckZero(int32_t div);
};

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
 }
};

#endif