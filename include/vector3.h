#ifndef ABSIM_VECTOR3_H
#define ABSIM_VECTOR3_H

#include "types.h"
#include "msgservice.h"

namespace ABSIM {

  class Vector3
  {
  friend class FourVector;
  private:
    real_t x_, y_, z_;

  public:
    Vector3() = default;
    Vector3(real_t x, real_t y, real_t z);
    Vector3(real_t*);
    Vector3(const Vector3&);
    ~Vector3() {}

    inline Vector3 operator=(const Vector3&);

    // Getters.
    inline real_t operator()(int_t) const;
    inline real_t operator[](int_t) const;

    inline real_t& operator()(int_t);
    inline real_t& operator[](int_t);

    inline real_t x()  const;
    inline real_t y()  const;
    inline real_t z()  const;
    inline real_t X()  const;
    inline real_t Y()  const;
    inline real_t Z()  const;
    inline real_t Px() const;
    inline real_t Py() const;
    inline real_t Pz() const;

    // Setters;
    inline void SetX(const real_t& x);
    inline void SetY(const real_t& y);
    inline void SetZ(const real_t& z);
    inline void SetPx(const real_t& px);
    inline void SetPy(const real_t& py);
    inline void SetPz(const real_t& pz);
    inline void SetXYZ(const real_t& x, const real_t& y, const real_t& z);
    inline void SetPxPyPz(const real_t& px, const real_t& py, const real_t& pz);
    inline void SetXYZ(real_t* x0);
    inline void SetPxPyPz(real_t* p0);

    // Operators.
    inline Vector3 operator+(const Vector3&);
    inline Vector3 operator-(const Vector3&);
    inline real_t operator*(const Vector3&);
    inline Vector3 operator*(const real_t&);
    inline bool operator==(const Vector3&) const;
    inline bool operator!=(const Vector3&) const;
    inline Vector3& operator+=(const Vector3&);
    inline Vector3& operator-=(const Vector3&);
    inline Vector3& operator*=(const Vector3&);
    inline Vector3 operator-();

    // Methods.
    inline real_t Mag2() const;
    inline real_t Mag() const;
    inline real_t Perp2() const;
    inline real_t Perp() const;
    inline real_t Pt() const;
    inline real_t CosTheta() const;
  };

  inline Vector3::Vector3(real_t x, real_t y, real_t z) :
    x_( x ), y_( y ), z_( z )
  {}

  inline Vector3::Vector3(real_t* x0) :
    x_( x0[0] ), y_( x0[1] ), z_( x0[2] )
  {}

  inline Vector3::Vector3(const Vector3& v) :
    x_( v.x_ ), y_( v.y_ ), z_( v.z_ )
  {}

  inline Vector3 Vector3::operator=(const Vector3& rhs)
  {
    x_ = rhs.x_;
    y_ = rhs.y_;
    z_ = rhs.z_;
    return *this;
  }

  inline real_t Vector3::operator()(int_t i) const
  {
    switch(i) {
      case 0:
        return x_;
      case 1:
        return y_;
      case 2:
        return z_;
      default:
        error() << "Bad index: " << i << endmsg;
    }
    return 0.;
  }

  inline real_t& Vector3::operator()(int_t i)
  {
    switch(i) {
      case 0:
        return x_;
      case 1:
        return y_;
      case 2:
        return z_;
      default:
        error() << "Bad index: " << i << endmsg;
    }
    return x_;
  }

  inline real_t Vector3::operator[](int_t i) const
  {
    switch(i) {
      case 0:
        return x_;
      case 1:
        return y_;
      case 2:
        return z_;
      default:
        error() << "Bad index: " << i << endmsg;
    }
    return 0.;
  }

  inline real_t& Vector3::operator[](int_t i)
  {
    switch(i) {
      case 0:
        return x_;
      case 1:
        return y_;
      case 2:
        return z_;
      default:
        error() << "Bad index: " << i << endmsg;
    }
    return x_;
  }

  inline real_t Vector3::x() const { return x_; }

  inline real_t Vector3::y() const { return y_; }

  inline real_t Vector3::z() const { return z_; }

  inline real_t Vector3::X() const { return x_; }

  inline real_t Vector3::Y() const { return y_; }

  inline real_t Vector3::Z() const { return z_; }

  inline real_t Vector3::Px() const { return x_; }

  inline real_t Vector3::Py() const { return y_; }

  inline real_t Vector3::Pz() const { return z_; }

  inline void Vector3::SetX(const real_t& x) { x_ = x; }

  inline void Vector3::SetY(const real_t& y) { y_ = y; }

  inline void Vector3::SetZ(const real_t& z) { z_ = z; }

  inline void Vector3::SetPx(const real_t& px) { x_ = px; }

  inline void Vector3::SetPy(const real_t& py) { y_ = py; }

  inline void Vector3::SetPz(const real_t& pz) { z_ = pz; }

  inline void Vector3::SetXYZ(const real_t& x, const real_t& y, const real_t& z)
  {
    x_ = x;
    y_ = y;
    z_ = z;
  }

  inline void Vector3::SetPxPyPz(const real_t& px, const real_t& py, const real_t& pz)
  {
    x_ = px;
    y_ = py;
    z_ = pz;
  }

  inline void Vector3::SetXYZ(real_t* x0)
  {
    x_ = x0[0];
    y_ = x0[1];
    z_ = x0[2];
  }

  inline void Vector3::SetPxPyPz(real_t* p0)
  {
    x_ = p0[0];
    y_ = p0[1];
    z_ = p0[2];
  }

  inline Vector3 Vector3::operator+(const Vector3& rhs)
  {
    return Vector3( x_ + rhs.x_ , y_ + rhs.y_ , z_ + rhs.z_ );
  }

  inline Vector3 Vector3::operator-(const Vector3& rhs)
  {
    return Vector3( x_ - rhs.x_ , y_ - rhs.y_ , z_ - rhs.z_ );
  }
  inline real_t Vector3::operator*(const Vector3& rhs)
  {
    return ( x_ * rhs.x_ ) + ( y_ * rhs.y_ ) + ( z_ + rhs.z_ );
  }
  inline Vector3 Vector3::operator*(const real_t& a)
  {
    return Vector3( x_ * a , y_ * a , z_ * a );
  }

  inline bool Vector3::operator==(const Vector3& rhs) const
  {
    return ( rhs.x_ == x_ && rhs.y_ == y_ && rhs.z_ == z_ ) ? true : false;
  }

  inline bool Vector3::operator!=(const Vector3& rhs) const
  {
    return ( rhs.x_ != x_ || rhs.y_ != y_ || rhs.z_ != z_ ) ? true : false;
  }

  inline Vector3& Vector3::operator+=(const Vector3& rhs)
  {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    return *this;
  }

  inline Vector3& Vector3::operator-=(const Vector3& rhs)
  {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    return *this;
  }

  inline Vector3& Vector3::operator*=(const Vector3& rhs)
  {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    z_ *= rhs.z_;
    return *this;
  }

  inline Vector3 Vector3::operator-()
  {
    return Vector3( -x_ , -y_ , -z_ );
  }

  inline real_t Vector3::Mag2() const
  {
    return ( x_* x_ ) + ( y_ * y_ ) + ( z_ * z_ );
  }

  inline real_t Vector3::Mag() const
  {
    return std::sqrt( Mag2() );
  }

  inline real_t Vector3::Perp2() const
  {
    return ( x_ * x_ ) + ( y_ * y_ );
  }

  inline real_t Vector3::Perp() const
  {
    return std::sqrt( Perp2() );
  }

  inline real_t Vector3::Pt() const
  {
    return Perp();
  }

  inline real_t Vector3::CosTheta() const
  {
    real_t ptot = Mag();
    return ptot == 0 ? 1. : z_/ptot;
  }

} //namespace ABSIM

#endif