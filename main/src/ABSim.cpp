#include "threadpool.h"
#include "CPUBackend.h"

#include <iostream>
#include <chrono>

using namespace ABSIM;

void task()
{
  std::cout << "BlockID = " << blockIdx.x << std::endl;
}

int main()
{
  ThreadPool pool;
  for (unsigned int i = 0; i < gridDim.x; ++i) {
    pool.submit( &task );
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return 0;
}