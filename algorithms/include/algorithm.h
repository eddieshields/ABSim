#ifndef ABSIM_ALGORITHM_H
#define ABSIM_ALGORITHM_H

#include <string>

namespace ABSIM {

  template <typename EVENT>
  class Algorithm
  {
  private:
    const std::string name_;
    
  public:
    Algorithm(std::string name) :
      name_( name )
    {}
    ~Algorithm() {}

    void init() {}

    void shutdown() {}

    virtual void operator()(EVENT& ev) = 0;
  };

} // namespace ABSIM

#endif