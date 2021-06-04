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
    void addAlgorithm(A* algo)
    {
      algorithms_.add( algo );
    }

    template <typename A>
    void operator+(A* algo)
    {
      addAlgorithm( algo );;
    }

    template <typename A>
    void operator+=(A* algo)
    {
      addAlgorithm( algo );
    }

    void operator()(Event& ev)
    {
      Algorithm* algo = algorithms_.head().get();
      while ( algo ) {
        algo->operator()(ev);
        algo = algo->next.get();
      }
    }
  };

  extern Sequence gSequence;

}  // namespace ABSIM

#endif