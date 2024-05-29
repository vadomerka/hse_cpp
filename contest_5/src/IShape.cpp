#include "../IShape.h"

namespace geometry {

std::string IShape::StringFormat(std::string class_name, std::string args[], size_t length) const {
  std::string ret = class_name + "(" + args[0];
  for (size_t i = 1; i < length; i++) {
    ret += ", " + args[i];
  }
  ret += ")";
  return ret;
}

}  // namespace geometry