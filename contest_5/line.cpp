#include "line.h"
#include "segment.h"
#include "vector.h"

namespace geometry
{
  
Line::Line(Point p, Vector v) : Line() {
  if (v.GetLength() == 0) return;
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

Line Line::operator=(const Line& other) {
  if (this == &other) { return *this; }
  Line tmp = other;
  Swap(*this, tmp);
  return *this;
}

void Line::Move(const Vector& v) {
  c_ += v.GetB();
}
bool Line::ContainsPoint(const Point& p) const {
  return a_ * p.GetX() + b_ * p.GetY() + c_ == 0;
}
bool Line::CrossesSegment(const Segment& segment) const {
  return PointPlane(segment.GetPoint1(), segment.GetPoint2());
}
Line* Line::Clone() const {
  return new Line(*this);
}
std::string Line::ToString() const {
  std::string vars[] { std::to_string(a_), std::to_string(b_), std::to_string(c_) };
  return StringFormat("Line", vars, 3);
}

Point Line::GetP() const {
  if (a_ == 0 || b_ == 0) return Point(0, 0);
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

} // namespace geometry