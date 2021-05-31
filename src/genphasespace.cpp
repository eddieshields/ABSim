#include "genphasespace.h"

using namespace ABSIM;

const int_t MAXP_ = 18;

int DoubleMax(const void* a, const void* b)
{
  real_t aa = *((real_t*) a);
  real_t bb = *((real_t*) b);
  if ( aa > bb ) return 1;
  if ( aa < bb ) return -1;
  return 0;
}

GenPhaseSpace::GenPhaseSpace(const GenPhaseSpace& gen)
{
  n_ = gen.n_;
  wtMax_ = gen.wtMax_;
  teCmTm_ = gen.teCmTm_;
  beta_[0] = gen.beta_[0];
  beta_[1] = gen.beta_[1];
  beta_[2] = gen.beta_[2];
  for (int_t i = 0; i < n_; i++) {
    mass_[i] = gen.mass_[i];
    decProd_[i] = gen.decProd_[i];
  }
}

GenPhaseSpace& GenPhaseSpace::operator=(const GenPhaseSpace& gen)
{
  n_ = gen.n_;
  wtMax_ = gen.wtMax_;
  teCmTm_ = gen.teCmTm_;
  beta_[0] = gen.beta_[0];
  beta_[1] = gen.beta_[1];
  beta_[2] = gen.beta_[2];
  for (int_t i = 0; i < n_; i++) {
    mass_[i] = gen.mass_[i];
    decProd_[i] = gen.decProd_[i];
  }
  return *this;
}

FourVector* GenPhaseSpace::GetDecay(int_t n)
{
  if ( n > n_ ) error() << "Bad index " << n << endmsg;
  return decProd_[n];
}

bool GenPhaseSpace::SetDecay(FourVector& p, int_t n, const real_t* mass)
{
  n_ = n;

  if ( n_ < 2 || n_ > 18 ) return false;

  pM_ = teCmTm_ = p.Mag();

  int_t i;
  for (i = 0; i < n_; i++) {
    mass_[i] = mass[i];
    teCmTm_ -= mass[i];
  }

  if ( teCmTm_ <= 0 ) return false;

  real_t emmax = teCmTm_ + mass_[0];
  real_t emmin = 0.;
  real_t wtmax = 1.;

  for (i = 1; i < n_; i++) {
    emmin += mass_[i-1];
    emmax += mass_[i];
    wtmax *= pdk_(emmax, emmin, mass_[i]);
  }
  wtMax_ = 1 / wtmax;

  if ( p.Beta() ) {
    real_t w = p.Beta() / p.Rho();
    beta_[0] = p(0) * w;
    beta_[1] = p(1) * w;
    beta_[2] = p(2) * w;
  } else {
    beta_[0] = beta_[1] = beta_[2] = 0.;
  }

  return true;
}

bool GenPhaseSpace::UpdateDecay(FourVector& p)
{
  real_t m = p.Mag();
  teCmTm_ += m - pM_;
  // Update previous mass.
  pM_ = m;

  if ( teCmTm_ <= 0 ) return false;

  real_t emmax = teCmTm_ + mass_[0];
  real_t emmin = 0.;
  real_t wtmax = 1.;

  for (int_t i = 1; i < n_; i++) {
    emmin += mass_[i-1];
    emmax += mass_[i];
    wtmax *= pdk_(emmax, emmin, mass_[i]);
  }
  wtMax_ = 1 / wtmax;

  if ( p.Beta() ) {
    real_t w = p.Beta() / p.Rho();
    beta_[0] = p(0) * w;
    beta_[1] = p(1) * w;
    beta_[2] = p(2) * w;
  } else {
    beta_[0] = beta_[1] = beta_[2] = 0.;
  }

  return true;
}

real_t GenPhaseSpace::Generate()
{
  real_t rno[MAXP_];
  rno[0] = 0;
  int_t n;
  if ( n_ > 2 ) {
    for (n = 1; n < n_; n++) rno[n] = Random::Rnd();
    qsort(rno+1, n_ - 2, sizeof(real_t), DoubleMax);
  }
  rno[n_-1] = 1.;

  real_t invMass[MAXP_], sum = 0;
  for (n = 0; n < n_; n++) {
    sum += mass_[n];
    invMass[n] = rno[n] * teCmTm_ + sum;
  }

  real_t wt = wtMax_;
  real_t pd[MAXP_];
  for (n = 0; n < n_ - 1; n++) {
    pd[n] = pdk_(invMass[n+1],invMass[n],mass_[n+1]);
    wt *= pd[n];
  }

  decProd_[0]->SetPxPyPzE( 0 , pd[0] , 0 , std::sqrt( ( pd[0] * pd[0] ) + ( mass_[0] * mass_[0] ) ) );

  int_t i = 1;
  int_t j;
  while (1) {
    decProd_[i]->SetPxPyPzE( 0 , -pd[i-1] , 0 , std::sqrt( ( pd[i-1] * pd[i-1] ) + ( mass_[i] * mass_[i] ) ) );

    real_t cZ = 2 * Random::Rnd() - 1;
    real_t sZ = std::sqrt( 1 - cZ * cZ );
    real_t angY = 2 * M_PI * Random::Rnd();
    real_t cY = std::cos( angY );
    real_t sY = std::sin( angY );
    for (j = 0; j <= i; j++) {
      FourVector *v = decProd_[j];
      real_t x = v->Px();
      real_t y = v->Py();
      v->SetPx( ( cZ * x ) - ( sZ * y ) );
      v->SetPy( ( sZ * x ) + ( cZ * y ) );
      x = v->Px();
      real_t z = v->Pz();
      v->SetPx( ( cY * x ) - ( sY * z ) );
      v->SetPz( ( sY * x ) + ( cY * z ) );
    }

    if ( i == ( n_ - 1 ) ) break;

    real_t beta = pd[i] / std::sqrt( ( pd[i] * pd[i] ) + invMass[i] * invMass[i] );
    for (j = 0; j <= i; j++ ) decProd_[j]->Boost(0,beta,0);
    i++;
  }

  // Final boost of all particles.
  for (n = 0; n < n_; n++) decProd_[n]->Boost( beta_[0] , beta_[1] , beta_[2] );

  // Return weight of event.
  return wt;
}