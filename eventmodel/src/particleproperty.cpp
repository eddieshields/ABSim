#include "particleproperty.h"

using namespace ABSIM;

template <typename T>
ParticleProperty<T>::ParticleProperty(const ParticleProperty<T>& rhs)
{
  gen_ = rhs.gen_;
  reco_ = rhs.reco_;
}

template <typename T>
ParticleProperty<T>& ParticleProperty<T>::operator=(const ParticleProperty<T>& rhs)
{
  gen_ = rhs.gen_;
  reco_ = rhs.reco_;
  return *this;
}

template <typename T>
ParticleProperty<T>& ParticleProperty<T>::operator=(const std::tuple<T,T>& rhs)
{
  gen_ = std::get<0>(rhs);
  reco_ = std::get<1>(rhs);
  return *this;
}

//template <typename T>
//ParticleProperty<T>& ParticleProperty<T>::operator=(const T& rhs)
//{
//  gen_ = rhs;
//  reco_ = rhs;
//  return *this;
//}

template <typename T>
ParticleProperty<T> ParticleProperty<T>::operator+(const ParticleProperty<T>& rhs)
{
  ParticleProperty<T> prop;
  prop.gen_ = gen_ + rhs.gen_;
  prop.reco_ = reco_ + rhs.reco_;
  return prop;
}

template <typename T>
ParticleProperty<T> ParticleProperty<T>::operator-(const ParticleProperty<T>& rhs)
{
  ParticleProperty<T> prop;
  prop.gen_ = gen_ - rhs.gen_;
  prop.reco_ = reco_ - rhs.reco_;
  return prop;
}

template <typename T>
ParticleProperty<T> ParticleProperty<T>::operator*(const ParticleProperty<T>& rhs)
{
  ParticleProperty<T> prop;
  prop.gen_ = gen_ * rhs.gen_;
  prop.reco_ = reco_ * rhs.reco_;
  return prop;
}

template <typename T>
ParticleProperty<T> ParticleProperty<T>::operator/(const ParticleProperty<T>& rhs)
{
  ParticleProperty<T> prop;
  prop.gen_ = gen_ / rhs.gen_;
  prop.reco_ = reco_ / rhs.reco_;
  return prop;
}