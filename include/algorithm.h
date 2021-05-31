#ifndef ABSIM_ALGORITHM_H
#define ABSIM_ALGORITHM_H

#include "backend.h"
#include "event.h"

#include <string>

namespace ABSIM {

  class Algorithm
  {
  private:
    const std::string name_;
    
  public:
    Algorithm(std::string name) :
      name_( name )
    {}
    ~Algorithm() {}

    __device__
    void init() {}

    __device__
    void shutdown() {}

    __device__
    virtual void operator()(Event& ev) = 0;
  };

} // namespace ABSIM

#endif