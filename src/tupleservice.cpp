#include "tupleservice.h"
#include "ABSim.h"

using namespace ABSIM;

template <typename Fn>
void TupleSvc::addEntry(std::string name, const Fn& fn, int_t index)
{
  //using T = typename std::result_of<Fn(Particle)>::type;
  info() "Name of functor = " << quote( fn ) << endmsg;
  ParticleEntry<Fn,real_t> entry = new ParticleEntry<Fn,real_t>(name,fn,index);
  target_->writer_.addEntry( entry );
}