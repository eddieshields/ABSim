#include "catch.hpp"

#include "decaydescriptor.h"
#include "iostream"

using namespace ABSIM;

TEST_CASE( "Test DecayDescriptor", "[DecayDescriptor]") {
  std::string descriptor_str = "D*+ => { D0 => { KS0 => pi+ pi- } K+ K- } pi+";
  DecayDescriptor descriptor(descriptor_str);
  std::cout << descriptor << std::endl;
}