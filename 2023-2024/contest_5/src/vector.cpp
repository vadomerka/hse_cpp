#include "../vector.h"
#include <stdexcept>

namespace geometry {

bool Vector::operator==(const Vector &other) {
  if (this == &other)
    return true;
  return (a_ == other.a_ && b_ == other.b_);
}

Vector &Vector::operator*=(int lambda) {
  a_ *= lambda;
  b_ *= lambda;
  return *this;
}

Vector &Vector::operator/=(int lambda) {
  if (!lambda)
    throw std::overflow_error("Vector can't be devided by zero.");
  a_ /= lambda;
  b_ /= lambda;
  return *this;
}

Vector &Vector::operator+=(const Vector &other) {
  a_ += other.a_;
  b_ += other.b_;
  return *this;
}

Vector &Vector::operator-=(const Vector &other) {
  a_ -= other.a_;
  b_ -= other.b_;
  return *this;
}

std::string Vector::StringFormat(std::string class_name, std::string args[], size_t length) const {
  std::string ret = class_name + "(" + args[0];
  for (size_t i = 1; i < length; i++) {
    ret += ", " + args[i];
  }
  ret += ")";
  return ret;
}

}  // namespace geometry