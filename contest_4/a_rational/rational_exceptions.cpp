#include "rational_exceptions.h"

TestClass::TestClass(char const* const message) throw()
    : std::runtime_error(message)
{

}