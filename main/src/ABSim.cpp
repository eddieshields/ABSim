#include "ABSim.h"

#include <iostream>
#include <chrono>

using namespace ABSIM;

int main()
{
  std::string descriptor_str = "D*+ => { D0 => { K_S0 => pi+ pi- } K+ K- } pi+";
  ABSim simulate(descriptor_str);
  simulate.run();

  return 0;
}