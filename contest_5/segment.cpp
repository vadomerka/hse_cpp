#include "segment.h"
#include "vector.h"
#include "point.h"
#include "line.h"

namespace geometry
{
  
Segment Segment::operator=(const Segment& other){
  if (this == &other) { return *this; }
  Segment tmp = other;
  Swap(*this, tmp);
  return *this;
}

void Segment::Move(const Vector& v) {
  p1_.Move(v);
  p2_.Move(v);
}
bool Segment::ContainsPoint(const Point& p) const {
  Vector v1 (p1_, p);
  Vector v2 (p, p2_);
  return Vector::AreColliniar(v1, v2);
}
bool Segment::CrossesSegment(const Segment &other) const {
  if (ContainsPoint(other.p1_) || ContainsPoint(other.p2_) ||
      other.ContainsPoint(p1_) || other.ContainsPoint(p2_)) return true;
  return GetLine().CrossesSegment(other) && other.GetLine().CrossesSegment(*this);
}
Segment* Segment::Clone() const {
  return new Segment(*this);
}
std::string Segment::ToString() const {
  std::string vars[] { p1_.ToString(), p2_.ToString() };
  return StringFormat("Segment", vars, 2);
}

Line Segment::GetLine() const { return Line(p1_, Vector(p1_, p2_)); }

double Segment::Distance(const Point& p) {
  if (GetLength() == 0) return Point::Distance(p1_, p);
  Vector ap(p1_, p);
  Vector ab(p1_, p2_);
  if (Vector::Scalar(ap, ab) <= 0) return ap.GetLength();
  Vector bp(p2_, p);
  Vector ba(p2_, p1_);
  if (Vector::Scalar(bp, ba) <= 0) return bp.GetLength();

  return Vector::Cross(ap, ab) / ap.GetLength();
}

} // namespace geometry