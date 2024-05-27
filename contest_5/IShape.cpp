#include "IShape.h"

namespace geometry
{
  
std::string IShape::StringFormat(std::string class_name, std::string args[], size_t length) {
  std::string ret = class_name + "(" + args[0];
  for (int i = 1; i < length; i++) {
    ret += ", " + args[i];
  }
  ret += ")";
  return ret;
}

} // namespace geometry