#ifndef ABSIM_LINKEDLIST_H
#define ABSIM_LINKEDLIST_H

#include <memory>

namespace ABSIM
{

  template <typename T>
  class LinkedList
  {
  private:
    std::unique_ptr<T> head_;

  public:
    LinkedList() :
      head_( nullptr )
    {}
    LinkedList(const LinkedList& ll)
    {
      head_ = std::move( ll.head_ );
    }
    ~LinkedList() {}

    LinkedList operator=(const LinkedList& ll)
    {
      head_ = std::move( ll.head_ );
      return *this;
    }

    template <typename D>
    void add(D* node)
    {
      auto tmp = std::make_unique<D>( *node );

      if ( head_ ) {
        tmp->next = std::move( head_ );
        head_ = std::move( tmp );
      } else {
        head_ = std::move( tmp );
      }
    }

    std::unique_ptr<T>& head() { return head_; }

  };

} // namespace ABSIM

#endif