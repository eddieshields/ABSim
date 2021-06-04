#ifndef ABSIM_ALGORITHM_H
#define ABSIM_ALGORITHM_H

#include "event.h"

#include <string>
#include <memory>

namespace ABSIM {

  class Algorithm
  {
  private:
    const std::string name_;
    
  public:
    Algorithm(std::string name) :
      name_( name ),
      next( nullptr )
    {}
    virtual ~Algorithm() {}

    std::unique_ptr<Algorithm> next;

    void init() {}

    void shutdown() {}

    virtual void operator()(Event& ev) = 0;

  };

} // namespace ABSIM

#endif