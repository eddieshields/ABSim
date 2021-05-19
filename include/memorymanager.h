#ifndef ABSIM_MEMORY_MANAGER_H
#define ABSIM_MEMORY_MANAGER_H

#include "msgservice.h"

#include <atomic>

namespace ABSIM {

  template <typename T>
  class MemoryManager
  {
  private:
    static T*               pool_;
    static std::atomic<int> head_;
    static int              tail_;

  public:
    static void request(int n)
    {
      ABSIM_INFO("Requested to allocate memory for " << n << " " << T::NAME() << "s");
      pool_ = reinterpret_cast<T*>( new char[sizeof(T)*n] );
      tail_ = n;
    }

    inline static void* allocate(size_t size)
    {
      if ( head_ + size >= tail_ ) FATAL("Not evenough memory to allocate more " << T::NAME() << "s");

      int head = head_.fetch_add( size );
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
  std::atomic<int> MemoryManager<T>::head_(0);

  template <typename T>
  int MemoryManager<T>::tail_ = 0;

} // namespace ABSIM


#endif