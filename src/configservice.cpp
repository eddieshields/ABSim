#include "configservice.h"
#include "ABSim.h"

using namespace ABSIM;

template <typename Arg, typename... Args>
void ConfigSvc::addAlgorithms(const Arg& alg, Args... algs)
{
  target_->sequence_.addAlgorithm( alg );
  addAlgorithms( algs... );
}

template<typename Arg>
void ConfigSvc::addAlgorithms(const Arg& alg)
{
  target_->sequence_.addAlgorithm( alg );
}
