#include "ABSim.h"
#include "msgservice.h"

#include <iostream>
#include <chrono>

using namespace ABSIM;

int main()
{
  std::string descriptor_str = "D*+ => { D0 => { K_S0 => pi+ pi- } K+ K- } pi+";
  ABSim simulation( descriptor_str );

  simulation().EvtMax = 1e6;
  simulation.run();

  return 0;
}