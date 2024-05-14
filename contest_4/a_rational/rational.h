#ifndef A_RATIONAL_H
#define A_RATIONAL_H

#include <cstdint>

class Rational {
public:
  Rational()
    : _numerator(0)
    , _denominator(1)
  {

  };

  Rational(int32_t n1);
  
  Rational(int32_t n1, int32_t n2);

  int32_t GetNumerator(void);
  int32_t GetDenominator();
  void SetNumerator(int32_t n1);
  void SetDenominator(int32_t n2);

private:
  int32_t _numerator;
  int32_t _denominator;

  void SimpleSet(int32_t num, int32_t dev);
};

#endif