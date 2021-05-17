#ifndef ABSIM_THREADPOOL_H
#define ABSIM_THREADPOOL_H

#include "CPUBackend.h"
#include "types.h"
#include "msgservice.h"

#include <thread>
#include <atomic>
#include <functional>
#include <vector>
#include <queue>
#include <future>

namespace ABSIM {

  class ThreadPool
  {
  private:
    class Worker {
    private:
      ThreadPool* pool_;
      unsigned int id_;

    public:
      Worker(ThreadPool* pool, const unsigned int id) :
        pool_( pool ),
        id_( id )
      {}
      ~Worker() {}

      void operator() () {
        // Use a thread as a block.
        blockIdx.x = id_;

        std::function<void()> task;
        while ( true ) {
          {
            std::unique_lock<std::mutex> lock(pool_->queue_mutex_);
            pool_->condition_.wait(lock, [this]{ return pool_->stop_ || !pool_->tasks_.empty(); });
            if(pool_->stop_ && pool_->tasks_.empty())
                return;
            task = std::move(pool_->tasks_.front());
            pool_->tasks_.pop();
          }
          task();
        }
      }
    };

    /** Container of threads. */
    std::vector< std::thread > workers_;
    /** Queue for tasks. */
    std::queue< std::function<void()> > tasks_;
    
    /** Queue mutex. */
    std::mutex queue_mutex_;
    /** Runtime mutex. */
    std::mutex runtime_mutex_;
    /** Condition for threads. */
    std::condition_variable condition_;
    /** Stop adding jobs to queue. */
    bool stop_;

    /** Number of threads created. */
    unsigned int nthreads_;

    /** IDs of threads. */
    unsigned int id_;

  public:
    /** Constructor. */
    ThreadPool(size_t threads = 0);
    /** Destructor. */
    ~ThreadPool();

    /** Submit a job, then retrieve its return from a future later. */
    template<class F, class... Args>
    auto submit(F&& f, Args&&... args) 
      -> std::future<typename std::result_of<F(Args...)>::type>;
    
    /** Add a job to the queue then wait for it's return. */
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
      -> typename std::result_of<F(Args...)>::type;

      
  };



  template<class F, class... Args>
  auto ThreadPool::submit(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
  {
    using return_type = typename std::result_of<F(Args...)>::type;
  
    auto task = std::make_shared< std::packaged_task<return_type()> >(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
          
    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(queue_mutex_);  
      
      // don't allow enqueueing after stopping the pool
      if ( stop_ )
        throw std::runtime_error("enqueue on stopped ThreadPool");  
      tasks_.emplace([task](){ (*task)(); });
    }
    condition_.notify_one();
    return res;
  }
  
  // add new work item to the pool
  template<class F, class... Args>
  auto ThreadPool::enqueue(F&& f, Args&&... args) 
      -> typename std::result_of<F(Args...)>::type
  {
    using return_type = typename std::result_of<F(Args...)>::type;
  
    auto task = std::make_shared< std::packaged_task<return_type()> >(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
          
    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(queue_mutex_);  
      
      // don't allow enqueueing after stopping the pool
      if ( stop_ )
        throw std::runtime_error("enqueue on stopped ThreadPool");  
      tasks_.emplace([task](){ (*task)(); });
    }
    condition_.notify_one();
    return res.get();
  }

} // namespace ANSIM

#endif