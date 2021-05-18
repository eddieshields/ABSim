#include "decaydescriptor.h"

#include <iostream>
#include <chrono>

using namespace ABSIM;

int main()
{
  std::string descriptor_str = "D*+ => { D0 => { KS0 => pi+ pi- } K+ K- } pi+";
  DecayDescriptor descriptor(descriptor_str);
  descriptor.Print();

  return 0;
}