#include "../polygon.h"
#include "../segment.h"
#include "../vector.h"
#include "../point.h"
#include "../line.h"
#include "../ray.h"

namespace geometry {

Polygon::Polygon(std::vector<Point> points) : vertices_(nullptr), size_(points.size()) {
  if (size_ == 0)
    return;
  vertices_ = new Point[size_];
  for (size_t i = 0; i < size_; i++) {
    vertices_[i] = points[i];
  }
}

Polygon::Polygon(const Polygon& other) : vertices_(nullptr), size_(other.size_) {
  if (size_ == 0)
    return;
  vertices_ = new Point[size_];
  for (size_t i = 0; i < size_; i++) {
    vertices_[i] = other.vertices_[i];
  }
}

Polygon::~Polygon() {
  delete[] vertices_;
}

Polygon Polygon::operator=(const Polygon& other) {
  if (this == &other) {
    return *this;
  }
  Polygon tmp = other;
  Swap(*this, tmp);
  return *this;
}

Polygon& Polygon::Move(const Vector& v) {
  for (size_t i = 0; i < size_; i++) {
    vertices_[i].Move(v);
  }
  return *this;
}
bool Polygon::ContainsPoint(const Point& p) const {
  if (!size_) {
    return false;
  }
  if (size_ == 1) {
    return vertices_[0] == p;
  }
  if (size_ == 2) {
    return Segment(vertices_[0], vertices_[1]).ContainsPoint(p);
  }

  Ray r(p, Vector(3, 2));
  Segment s(vertices_[0], vertices_[1]);
  size_t counter = 0;

  if (s.ContainsPoint(r.GetPoint())) {
    return true;
  } else if (HasIntersects(r, s, 1)) {
    ++counter;
  }

  for (size_t i = 2; i < size_; ++i) {
    s.GetPoint1() = s.GetPoint2();
    s.GetPoint2() = vertices_[i];
    if (s.ContainsPoint(r.GetPoint())) {
      return true;
    } else if (HasIntersects(r, s, 1)) {
      ++counter;
    }
  }

  s.GetPoint1() = s.GetPoint2();
  s.GetPoint2() = vertices_[0];
  if (s.ContainsPoint(r.GetPoint())) {
    return true;
  } else if (HasIntersects(r, s, 1)) {
    ++counter;
  }
  return counter % 2;
}

bool Polygon::CrossesSegment(const Segment& other) const {
  for (size_t i = 0; i < size_ - 1; i++) {
    if (Segment(vertices_[i], vertices_[i + 1]).CrossesSegment(other)) {
      return true;
    }
  }
  return Segment(vertices_[0], vertices_[size_ - 1]).CrossesSegment(other);
}
Polygon* Polygon::Clone() const {
  return new Polygon(*this);
}
std::string Polygon::ToString() const {
  std::string points = "";
  if (size_) {
    for (size_t i = 0; i < size_ - 1; i++) {
      points += vertices_[i].ToString() + ", ";
    }
    points += vertices_[size_ - 1].ToString();
  }
  std::string vars[]{points};
  return StringFormat("Polygon", vars, 1);
}

bool Polygon::operator==(const Polygon& other) const {
  if (this == &other)
    return true;
  if (size_ != other.size_)
    return false;
  for (size_t i = 0; i < size_; i++) {
    if (vertices_[i] != other.vertices_[i])
      return false;
  }
  return true;
}

bool geometry::Polygon::HasIntersects(const Ray& r, const Segment& s, size_t idx) const {
  bool is_a = r.ContainsPoint(s.GetPoint1());
  bool is_b = r.ContainsPoint(s.GetPoint2());

  if (is_a && is_b) {
    return idx == 1;
  }

  if (is_a) {
    return true;
  }

  if (is_b) {
    int s1 = Sign(Vector::Cross(r.GetVector(), Vector(r.GetPoint(), s.GetPoint1())));
    int s2 = Sign(Vector::Cross(r.GetVector(), Vector(r.GetPoint(), vertices_[++idx % size_])));
    return s1 == s2 && idx < size_;
  }

  return r.CrossesSegment(s);
}

}  // namespace geometry