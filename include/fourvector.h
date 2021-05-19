#ifndef ABSIM_FOURVECTOR_H
#define ABSIM_FOURVECTOR_H

#include "vector3.h"
#include "types.h"

namespace ABSIM {

  class FourVector
  {
  private:
    Vector3 p_;
    real_t  e_;

  public:
    FourVector() = default;
    FourVector(real_t x, real_t y, real_t z, real_t t);
    FourVector(real_t*);
    FourVector(const Vector3&, real_t);
    FourVector(const FourVector&);
    ~FourVector() {}

    inline FourVector operator=(const FourVector&);

    // Getters.
    inline real_t operator()(int) const;
    inline real_t operator[](int) const;

    inline real_t& operator()(int);
    inline real_t& operator[](int);

    inline real_t x()  const;
    inline real_t y()  const;
    inline real_t z()  const;
    inline real_t t()  const;
    inline real_t X()  const;
    inline real_t Y()  const;
    inline real_t Z()  const;
    inline real_t T()  const;
    inline real_t Px() const;
    inline real_t Py() const;
    inline real_t Pz() const;
    inline real_t E()  const;

    // Setters.
    inline void SetX(const real_t& x);
    inline void SetY(const real_t& y);
    inline void SetZ(const real_t& z);
    inline void SetT(const real_t& t);
    inline void SetPx(const real_t& px);
    inline void SetPy(const real_t& py);
    inline void SetPz(const real_t& px);
    inline void SetE(const real_t& e);
    inline void SetXYZT(const real_t& x, const real_t& y, const real_t& z, const real_t& t);
    inline void SetPxPyPzE(const real_t& px, const real_t& py, const real_t& pz, const real_t& e);
    inline void SetXYZT(real_t* x0);
    inline void SetPxPyPzE(real_t* p0);

    // Operators.
    inline FourVector operator+(const FourVector&);
    inline FourVector operator-(const FourVector&);
    inline real_t operator*(const FourVector&);
    inline FourVector operator*(const real_t&);
    inline bool operator==(const FourVector&) const;
    inline bool operator!=(const FourVector&) const;
    inline FourVector& operator+=(const FourVector&);
    inline FourVector& operator-=(const FourVector&);
    inline FourVector& operator*=(const FourVector&);
    inline FourVector operator-();

    // Methods.
    inline real_t Mag2() const;
    inline real_t Mag() const;
    inline real_t M() const;
    inline real_t M2() const;
    inline real_t Perp2() const;
    inline real_t Perp() const;
    inline real_t Pt() const;
    inline real_t Beta() const;
    inline real_t Gamma() const;
    inline void Boost(const Vector3&);
    inline void Boost(real_t bx, real_t by, real_t bz);
  };

  FourVector::FourVector(real_t x , real_t y, real_t z, real_t t) :
    p_( x , y , z ), e_( t )
  {}

  FourVector::FourVector(real_t* x0) :
    p_( x0 ), e_( x0[3] )
  {}
  FourVector::FourVector(const Vector3& p, real_t e) :
    p_( p ), e_ ( e )
  {}

  FourVector::FourVector(const FourVector& p) :
    p_( p.p_ ), e_( p.e_ )
  {}

  inline FourVector FourVector::operator=(const FourVector& rhs)
  {
    p_ = rhs.p_;
    e_ = rhs.e_;
  }

  inline real_t FourVector::operator()(int i) const
  {
    switch(i) {
      case 0:
        return p_.x();
      case 1:
        return p_.y();
      case 2:
        return p_.z();
      case 3:
        return e_;
    default:
        ERROR("Bad index: " << i);
    }
    return 0.;
  }

  inline real_t FourVector::operator[](int i) const
  {
    return (*this)(i);
  }

  inline real_t& FourVector::operator()(int i)
  {
    switch(i) {
      case 0:
        return p_.x_;
      case 1:
        return p_.y_;
      case 2:
        return p_.z_;
      case 3:
        return e_;
    default:
        ERROR("Bad index: " << i);
    }
    return e_;
  }

  inline real_t& FourVector::operator[](int i)
  {
    return (*this)(i);
  }

  inline real_t FourVector::x()  const { return p_.x_; };

  inline real_t FourVector::y()  const { return p_.y_; };

  inline real_t FourVector::z()  const { return p_.z_; };

  inline real_t FourVector::t()  const { return e_; };

  inline real_t FourVector::X()  const { return p_.x_; };

  inline real_t FourVector::Y()  const { return p_.y_; };

  inline real_t FourVector::Z()  const { return p_.z_; };

  inline real_t FourVector::T()  const { return e_; };

  inline real_t FourVector::Px() const { return p_.x_; };

  inline real_t FourVector::Py() const { return p_.y_; };

  inline real_t FourVector::Pz() const { return p_.z_; };

  inline real_t FourVector::E()  const { return e_; };

  inline void FourVector::SetX(const real_t& x) { p_.x_ = x; }

  inline void FourVector::SetY(const real_t& y) { p_.y_ = y; }

  inline void FourVector::SetZ(const real_t& z) { p_.z_ = z; }

  inline void FourVector::SetT(const real_t& t) { e_ = t; }

  inline void FourVector::SetPx(const real_t& px) { p_.x_ = px; }

  inline void FourVector::SetPy(const real_t& py) { p_.y_ = py; }

  inline void FourVector::SetPz(const real_t& pz) { p_.z_ = pz; }

  inline void FourVector::SetE(const real_t& e) { e_ = e; }

  inline void FourVector::SetXYZT(const real_t& x, const real_t& y, const real_t& z, const real_t& t)
  {
    p_.x_ = x;
    p_.y_ = y;
    p_.z_ = z;
    e_ = t;
  }

  inline void FourVector::SetPxPyPzE(const real_t& px, const real_t& py, const real_t& pz, const real_t& e)
  {
    p_.x_ = px;
    p_.y_ = py;
    p_.z_ = pz;
    e_ = e;
  }

  inline void FourVector::SetXYZT(real_t* x0)
  {
    p_.x_ = x0[0];
    p_.y_ = x0[1];
    p_.z_ = x0[2];
    e_ = x0[3];
  }

  inline void FourVector::SetPxPyPzE(real_t* p0)
  {
    p_.x_ = p0[0];
    p_.y_ = p0[1];
    p_.z_ = p0[2];
    e_ = p0[3];
  }

  inline FourVector FourVector::operator+(const FourVector& rhs)
  {
    return FourVector( p_ + rhs.p_ , e_ + rhs.e_ );
  }

  inline FourVector FourVector::operator-(const FourVector& rhs)
  {
    return FourVector( p_ - rhs.p_ , e_ - rhs.e_ );
  }

  inline real_t FourVector::operator*(const FourVector& rhs)
  {
    return ( e_ * rhs.e_ ) - ( p_.x_ * rhs.p_.x_ ) - ( p_.y_ * rhs.p_.y_ ) - ( p_.z_ + rhs.p_.z_ );
  }

  inline FourVector FourVector::operator*(const real_t& a)
  {
    return FourVector( p_ * a , e_ * a );
  }

  inline bool FourVector::operator==(const FourVector& rhs) const
  {
    return ( rhs.p_ == p_ && rhs.e_ == e_ ) ? true : false;
  }

  inline bool FourVector::operator!=(const FourVector& rhs) const
  {
    return ( rhs.p_ != p_ || rhs.e_ != e_ ) ? true : false;
  }

  inline FourVector& FourVector::operator+=(const FourVector& rhs)
  {
    p_ += rhs.p_;
    e_ += rhs.e_;
    return *this;
  }

  inline FourVector& FourVector::operator-=(const FourVector& rhs)
  {
    p_ -= rhs.p_;
    e_ -= rhs.e_;
    return *this;
  }

  inline FourVector& FourVector::operator*=(const FourVector& rhs)
  {
    p_ *= rhs.p_;
    e_ *= rhs.e_;
    return *this;
  }

  inline FourVector FourVector::operator-()
  {
    return FourVector( -p_.x_ , -p_.y_ , -p_.z_ , -e_ );
  }

  inline real_t FourVector::Mag2() const
  {
    return ( e_ * e_ ) - p_.Mag2();
  }

  inline real_t FourVector::Mag() const
  {
    real_t mm = Mag2();
    return mm < 0. ? std::sqrt(-mm) : std::sqrt(mm);
  }

  inline real_t FourVector::M() const
  {
    return Mag();
  }

  inline real_t FourVector::M2() const
  {
    return Mag2();
  }

  inline real_t FourVector::Perp2() const
  {
    return p_.Perp2();
  }

  inline real_t FourVector::Perp() const
  {
    return p_.Perp();
  }

  inline real_t FourVector::Pt() const
  {
    return p_.Perp();
  }

  inline real_t FourVector::Beta() const
  {
    return p_.Mag() / e_;
  }

  inline real_t FourVector::Gamma() const
  {
    real_t b = Beta();
    return 1. / std::sqrt( 1 - ( b * b ) );
  }

  inline void FourVector::Boost(const Vector3& b)
  {
    Boost( b.X() , b.Y() , b.Z() );
  }

  inline void FourVector::Boost(real_t bx, real_t by, real_t bz)
  {
    real_t b2 = ( bx * bx ) + ( by * by ) + ( bz * bz );
    real_t gamma = 1. / std::sqrt( 1. = b2 );
    real_t bp = ( bx * X() ) + ( by * Y() ) + ( bz * Z() );
    real_t gamma2 = b2 > 0 ? ( gamma - 1. ) / b2 : 0.;

    SetX( X() + ( gamma2 * bp * bx ) + ( gamma * bx * T() ) );
    SetY( Y() + ( gamma2 * bp * by ) + ( gamma * by * T() ) );
    SetZ( Z() + ( gamma2 * bp * bz ) + ( gamma * bz * T() ) );
    SetT( gamma * ( T() + bp ) );
  }




} // namespace ABSIM

#endif