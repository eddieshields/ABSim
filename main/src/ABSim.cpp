#include "ABSim.h"
#include "msgservice.h"

#include <iostream>
#include <chrono>

using namespace ABSIM;

int main()
{
  std::string descriptor_str = "D*+ => { D0 => { K_S0 => pi+ pi- } K+ K- } pi+";
  DecayDescriptor descriptor( descriptor_str );

  // Speed test.
  int nEv = 1e6;
  MemoryManager<Event>::request(nEv);
  MemoryManager<Particle>::request(7*nEv);
  MemoryManager<Decay>::request(3*nEv);
  Event* event = nullptr;

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < nEv; i++) {
    event = new Event(descriptor);
  }
  auto finish = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  return 0;
}