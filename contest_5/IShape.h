#ifndef A_ISHAPE_H
#define A_ISHAPE_H

/*
  Move(const Vector&) - сдвига на заданный вектор, метод должен изменять
  состояние объекта и возвращать ссылку на сам объект; ContainsPoint(const
  Point&) - проверка (true/false) содержит ли фигура (внутренность фигуры)
  точку; CrossesSegment(const Segment&) проверка (true/false) пересекается ли
  фигура (граница фигуры) с отрезком; Clone() - копирование объекта (необходимо
  вернуть умный или обычный указатель на копию фигуры); ToString() - строковое
  представление фигуры (формат см. в примерах).
*/

// #include "point.h"
// #include "segment.h"
// #include "vector.h"
#include <string>

namespace geometry {

class Vector;
class Point;
class Segment;
class Ray;
class Line;
class Polygon;

class IShape {
public:
  virtual void Move(const Vector &) = 0;
  virtual bool ContainsPoint(const Point &) const = 0;
  virtual bool CrossesSegment(const Segment &) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;

protected:
  std::string StringFormat(std::string class_name, std::string args[], size_t length) const;

  bool IsMult(int n1, int n2);
};

} // namespace geometry

#endif