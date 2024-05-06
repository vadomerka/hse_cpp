#ifndef A_RATIONAL_EXCEPTIONS_H
#define A_RATIONAL_EXCEPTIONS_H

#include <stdexcept>

class TestClass : public std::runtime_error
{
public:
  TestClass(char const* const message) throw();
  virtual char const* what() const throw();
};

#endif