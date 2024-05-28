#ifndef A_VECTOR_H
#define A_VECTOR_H

#include "point.h"
#include <cmath>

namespace geometry {

class Vector {
public:
  Vector() : a_(0), b_(0) {}

  Vector(int x, int y) : a_(x), b_(y) {}

  Vector(const Point &p1, const Point &p2)
      : a_{p2.GetX() - p1.GetX()}, b_{p2.GetY() - p1.GetY()} {}

  Vector(const Vector &other) : a_(other.a_), b_(other.b_) {}

  ~Vector() = default;

  Vector operator=(const Vector &other) {
    if (this == &other) {
      return *this;
    }
    Vector tmp = other;
    Swap(*this, tmp);
    return *this;
  }

#pragma region operators

public:
  bool operator==(const Vector &other);

  bool operator!=(const Vector &other) { return !(*this == other); }

  Vector &operator*=(int lambda);

  Vector &operator/=(int lambda);

  Vector &operator+=(const Vector &other);

  Vector &operator-=(const Vector &other);

  Vector operator*(int lambda) const { return Vector(*this) *= lambda; }

  Vector operator/(int lambda) const { return Vector(*this) /= lambda; }

  Vector operator+(const Vector &other) const { return Vector(*this) += other; }

  Vector operator-(const Vector &other) const { return Vector(*this) -= other; }

  Vector operator+() const { return (*this); }

  Vector operator-() const { return {-a_, -b_}; }

#pragma endregion

public:
  static bool AreColliniar(const Vector &v1, const Vector &v2) {
    return !Cross(v1, v2);
  }

  static bool AreCoDirected(const Vector &v1, const Vector &v2) {
    return AreColliniar(v1, v2) && v1.a_ * v2.a_ >= 0 && v1.b_ * v2.b_ >= 0;
  }

  static bool AreOpDirected(const Vector &v1, const Vector &v2) {
    return AreColliniar(v1, v2) && v1.a_ * v2.a_ < 0 && v1.b_ * v2.b_ < 0;
  }

  static bool ArePerpendicular(const Vector &v1, const Vector &v2) {
    return !Scalar(v1, v2);
  }

  static int Scalar(const Vector &v1, const Vector &v2) {
    return v1.a_ * v2.a_ + v1.b_ * v2.b_;
  }

  static int Cross(const Vector &v1, const Vector &v2) {
    return v1.a_ * v2.b_ - v1.b_ * v2.a_;
  }

public:
  int GetA() const { return a_; }
  int GetB() const { return b_; }
  double GetLength() const { return sqrt(a_ * a_ + b_ * b_); }
  std::string ToString() const {
    std::string vars[]{std::to_string(a_), std::to_string(b_)};
    return StringFormat("Vector", vars, 2);
  }

private:
  void Swap(Vector &v1, Vector &v2) {
    std::swap(v1.a_, v2.a_);
    std::swap(v1.b_, v2.b_);
  }

protected:
  std::string StringFormat(std::string class_name, std::string args[],
                           size_t length) const;

private:
  int a_;
  int b_;
};

} // namespace geometry
#endif