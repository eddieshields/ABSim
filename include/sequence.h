#ifndef ABSIM_SEQUENCE_H
#define ABSIM_SEQUENCE_H

#include "algorithm.h"
#include "event.h"
#include "linkedlist.h"


namespace ABSIM {

  class Sequence
  {
  private:
    LinkedList<Algorithm> algorithms_;

  public:
    Sequence() = default;
    ~Sequence() {}

  
    template <typename A>
    void addAlgorithm(const A& alg)
    {
      addAlgorithm( &alg );
    }

    template <typename A>
    void addAlgorithm(A* alg)
    {
      algorithms_.add( alg );
    }

    template <typename A>
    void operator+(A* alg)
    {
      addAlgorithm( alg );;
    }

    template <typename A>
    void operator+=(A* alg)
    {
      addAlgorithm( alg );
    }

    void operator()(Event& ev)
    {
      Algorithm* alg = algorithms_.head().get();
      while ( alg ) {
        alg->operator()(ev);
        alg = alg->next.get();
      }
    }
  };


}  // namespace ABSIM

#endif