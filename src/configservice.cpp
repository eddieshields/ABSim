#include "configservice.h"
#include "ABSim.h"

using namespace ABSIM;

template <typename Arg, typename... Args>
void ConfigSvc::addAlgorithms(const Arg& alg, Args... algs)
{
  algorithms_.addAlgorithm( alg );
  addAlgorithms( algs... );
}

template<typename Arg>
void ConfigSvc::addAlgorithms(const Arg& alg)
{
  algorithms_.addAlgorithm( alg );
}
