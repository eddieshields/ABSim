#include "tupleservice.h"
#include "ABSim.h"

using namespace ABSIM;

template <typename Fn>
void TupleSvc::addEntry(const Fn& fn, int_t index)
{
  info() "Name of functor = " << quote( fn ) << endmsg;
  ParticleEntry<Fn,real_t> entry = new ParticleEntry<Fn,real_t>("D0",index);
}

template <typename Fn>
std::string TupleSvc::generateName(const int_t index) const
{
  return "";
}