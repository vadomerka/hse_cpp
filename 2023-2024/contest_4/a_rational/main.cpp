#include <iostream>
#include "rational.h"
#include <vector>


struct RVector {
  public:
    RVector(const std::vector<Rational>& v) : v_(v) {}
    RVector(const std::initializer_list<Rational>& v) {
      for (auto it = v.begin(); it != v.end(); ++it) {
        v_.push_back(*it);
      }
    }
    RVector(const RVector& rv) {
      for (auto it = rv.v_.begin(); it != rv.v_.end(); ++it) {
        v_.push_back(*it);
      }
    }
  public:
    RVector& operator*=(const Rational& c) {
      for (size_t i = 0; i < v_.size(); i++) {
        v_[i] *= c;
      }
      return *this;
    }

    RVector operator*(const Rational& c) const {
      return RVector(*this) *= c;
    }

    RVector& operator+=(const RVector& other) {
      for (size_t i = 0; i < v_.size(); i++) {
        v_[i] += other.v_[i];
      }
      return *this;
    }

    RVector operator+(const RVector& c) const {
      return RVector(*this) += c;
    }

    RVector& operator-=(const RVector& other) {
      for (size_t i = 0; i < v_.size(); i++) {
        v_[i] -= other.v_[i];
      }
      return *this;
    }

    RVector operator-(const RVector& c) const {
      return RVector(*this) -= c;
    }

    Rational Scalar(const RVector& other) const {
      Rational res(0);
      for (size_t i = 0; i < v_.size(); i++) {
        res += v_[i] * other.v_[i];
      }
      return res;
    }

    void Scalar(const RVector& other, Rational& res) const {
      for (size_t i = 0; i < v_.size(); i++) {
        res += v_[i] * other.v_[i];
      }
    }

    void Print() {
      for (size_t i = 0; i < v_.size(); i++) {
        std::cout << v_[i] << " ";
      }
      std::cout << '\n';
    }

  private:
    std::vector<Rational> v_;
};

int main() {
  //RVector a1 {4, 2, -2, 2};
  //RVector a2 {-2, 0, 2, 4};
  //RVector a3 {1, 2, -2, 2};
//
  //RVector e1 {4, 2, -2, 2};
  //RVector e2 = a2 - (e1 * (a2.Scalar(e1) / e1.Scalar(e1)));
  //// e2.Print();
  //RVector e3 = a3 - (e1 * (a3.Scalar(e1) / e1.Scalar(e1)))-(e2 * (a3.Scalar(e2) / e2.Scalar(e2)));
  //// e3.Print();
  //RVector x {0, 0, -4, 0};
  //RVector prx = e1 * (x.Scalar(e1)/e1.Scalar(e1)) + e2 * (x.Scalar(e2)/e2.Scalar(e2)) + e3 * (x.Scalar(e3)/e3.Scalar(e3));
  //prx.Print();
  //RVector ort = x - prx;
  //ort.Print();
  //Rational rho = x.Scalar(x);
  std::cout << Rational(9333, 5000) + Rational(1425, 625);
  return 0;
}

// 8 969 967 91 15 дмитрий