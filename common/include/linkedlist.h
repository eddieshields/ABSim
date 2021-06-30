#ifndef ABSIM_LINKEDLIST_H
#define ABSIM_LINKEDLIST_H

#include <memory>
#include "types.h"

namespace ABSIM
{

  template <typename T>
  class LinkedList
  {
  private:
    std::unique_ptr<T> head_;
    int_t              len_;

  public:
    LinkedList() :
      head_( nullptr ),
      len_( 0 )
    {}
    LinkedList(const LinkedList& ll) :
      len_( 0 )
    {
      head_ = std::move( ll.head_ );
    }
    ~LinkedList() {}

    LinkedList operator=(const LinkedList& ll)
    {
      head_ = std::move( ll.head_ );
      len_ = ll.len_;
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
      ++len_;
    }

    std::unique_ptr<T>& head() { return head_; }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T> ll)
    {
      T* tmp_ = ll.head_.get();
      while ( tmp_ != nullptr ) {
        os << *tmp_;
        tmp_ = tmp_->next.get();
      }
    }

    class Iterator
    {
    public:
      Iterator(T* ptr): ptr(ptr){}
      Iterator operator++() { ++ptr; return *this; }
      bool operator!=(const Iterator & other) const { return ptr != other.ptr; }
      const T& operator*() const { return *ptr; }
    private:
      T* ptr;
    };

    Iterator begin() const { return Iterator(head_.get()); }
    Iterator end() const { return Iterator(head_.get() + len_); }

  };

} // namespace ABSIM

#endif