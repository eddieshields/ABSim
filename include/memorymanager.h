#ifndef ABSIM_MEMORY_MANAGER_H
#define ABSIM_MEMORY_MANAGER_H

#include "types.h"
#include "msgservice.h"

#include <atomic>

namespace ABSIM {

  template <typename T>
  class MemoryManager
  {
  private:
    static T*                 pool_;
    static std::atomic<int_t> head_;
    static int_t              tail_;

    static constexpr size_t size_ = sizeof(T);

  public:
    static void request(int_t n)
    {
      debug() << "Requested to allocate memory for " << n << " " << T::NAME() << "s" << endmsg;
      pool_ = reinterpret_cast<T*>( new char[sizeof(T)*n] );
      head_ = 0;
      tail_ = n;
    }

    inline static void* allocate(size_t size)
    {
      int_t n = size / size_;
      if ( head_ + n > tail_ ) {
        fatal() << "Not enough memory to allocate more " << T::NAME() << "s" << leave;
      }

      int_t head = head_.fetch_add( n );
      return pool_ + head;
    }

    inline static void free(void* deleted)
    {
      return;
    }

  };

  template <typename T>
  T* MemoryManager<T>::pool_ = nullptr;

  template <typename T>
  std::atomic<int_t> MemoryManager<T>::head_(0);

  template <typename T>
  int_t MemoryManager<T>::tail_ = 0;

} // namespace ABSIM


#endif