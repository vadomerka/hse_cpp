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

#include <string>

namespace geometry {

class Vector;
class Point;
class Segment;
class Ray;
class Line;
class Circle;

class IShape {
 public:
  virtual ~IShape() = default;

 public:
  virtual IShape &Move(const Vector &) = 0;
  virtual bool ContainsPoint(const Point &) const = 0;
  virtual bool CrossesSegment(const Segment &) const = 0;
  virtual IShape *Clone() const = 0;
  virtual std::string ToString() const = 0;

 protected:
  std::string StringFormat(std::string class_name, std::string args[], size_t length) const;

  bool IsMult(int n1, int n2);
  int Sign(int num) const {
    if (num > 0) {
      return 1;
    }
    if (num == 0) {
      return 0;
    }
    return -1;
  }
};

}  // namespace geometry

#endif