#include "../line.h"
#include "../segment.h"
#include "../vector.h"

namespace geometry {

Line::Line(const Point& p, const Vector& v) : Line() {
  if (v.GetLength() == 0)
    return;
  if (!v.GetA()) {
    a_ = 1;
    b_ = 0;
    c_ = -(p.GetX() * a_) - (p.GetY() * b_);
    return;
  } else {
    a_ = 0;
    b_ = 1;
    c_ = -(p.GetX() * a_) - (p.GetY() * b_);
    return;
  }
  a_ = 1 / v.GetA();
  b_ = -1 / v.GetB();
  c_ = -(p.GetX() * a_) - (p.GetY() * b_);
}

Line::Line(const Point& point1, const Point& point2) {
  a_ = point2.GetY() - point1.GetY();
  b_ = point1.GetX() - point2.GetX();
  c_ = point2.GetX() * point1.GetY() - point1.GetX() * point2.GetY();
}

Line Line::operator=(const Line& other) {
  if (this == &other) {
    return *this;
  }
  Line tmp = other;
  Swap(*this, tmp);
  return *this;
}

Line& Line::Move(const Vector& v) {
  c_ -= a_ * v.GetA() + b_ * v.GetB();
  return *this;
}
bool Line::ContainsPoint(const Point& p) const {
  return a_ * p.GetX() + b_ * p.GetY() + c_ == 0;
}
bool Line::GetPointY(Point& p) const {
  int num = a_ * p.GetX() + c_;
  if (num % b_) {
    return false;
  }

  p.GetY() = -num / b_;
  return true;
}

bool Line::GetPoint(Point& p) const {
  if (!a_ && !b_) {
    return false;
  }
  if (!a_) {
    if (c_ % b_) {
      return false;
    }
    p = Point(0, -c_ / b_);
    return true;
  }
  if (!b_) {
    if (c_ % a_) {
      return false;
    }
    p = Point(-c_ / a_, 0);
    return true;
  }

  if (GetPointY(p)) {
    return true;
  }

  for (++p.GetX(); p.GetX() < std::numeric_limits<int>::max(); ++p.GetX()) {
    if (GetPointY(p)) {
      return true;
    }
    p.GetX() = -p.GetX();
    if (GetPointY(p)) {
      return true;
    }
    p.GetX() = -p.GetX();
  }

  return false;
}

bool geometry::Line::CrossesSegment(const Segment& s) const {
  Point p;
  if (!GetPoint(p)) {
    return false;
  }

  if (p == s.GetPoint1() || p == s.GetPoint2()) {
    return true;
  }

  Vector v(-b_, a_);
  Vector va(p, s.GetPoint1());
  Vector vb(p, s.GetPoint2());

  int c1 = Sign(Vector::Cross(v, va));
  int c2 = Sign(Vector::Cross(v, vb));

  return (c1 != c2) || (!c1 && !c2);
}
Line* Line::Clone() const {
  return new Line(*this);
}
std::string Line::ToString() const {
  std::string vars[]{std::to_string(a_), std::to_string(b_), std::to_string(c_)};
  return StringFormat("Line", vars, 3);
}

Point Line::GetP() const {
  if (a_ == 0 || b_ == 0)
    return Point(0, 0);
  return Point(-c_ / a_, 0);
}

Vector Line::GetN() const {
  Vector n(a_, b_);
  return n;
}
Vector Line::GetV() const {
  Vector v(b_, -a_);
  return v;
}

bool Line::PointPlane(const Point& p1, const Point& p2) const {
  int res1 = a_ * p1.GetX() + b_ * p1.GetY() + c_;
  int res2 = a_ * p2.GetX() + b_ * p2.GetY() + c_;
  return res1 * res2 >= 0 ? true : false;
}

bool Line::IsParralel(const Line& other) const {
  return GetV() == other.GetV();
}

double Line::Distance(const Point& p) const {
  Vector v(GetP(), p);
  return Vector::Cross(v, GetV()) / v.GetLength();
}

}  // namespace geometry