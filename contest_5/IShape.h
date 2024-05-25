#ifndef A_ISHAPE_H
#define A_ISHAPE_H

/*
  Move(const Vector&) - сдвига на заданный вектор, метод должен изменять состояние объекта и возвращать ссылку на сам объект;
  ContainsPoint(const Point&) - проверка (true/false) содержит ли фигура (внутренность фигуры) точку;
  CrossesSegment(const Segment&) проверка (true/false) пересекается ли фигура (граница фигуры) с отрезком;
  Clone() - копирование объекта (необходимо вернуть умный или обычный указатель на копию фигуры);
  ToString() - строковое представление фигуры (формат см. в примерах).
*/
#include "vector.h"
// #include "point.h"
// #include "segment.h"
#include <string>


class IShape {
 public:
  virtual void Move(const Vector&);
  // virtual bool ContainsPoint(const Point&);
  // virtual bool CrossesSegment(const Segment&);
  virtual IShape& Clone();
  virtual std::string ToString();
};

#endif