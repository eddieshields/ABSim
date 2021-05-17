#include "threadpool.h"

using namespace ABSIM;

ThreadPool::ThreadPool(size_t threads) :
  id_( 0 )
{
  stop_ = false;
  if ( workers_.size() ) {
    return;
  }
  if ( !threads ) { nthreads_ = std::thread::hardware_concurrency(); } else { nthreads_ = threads; }
  for(size_t i = 0; i < nthreads_ ; ++i) {
    workers_.emplace_back( Worker( this , id_ ) );
    ++id_;
  }
  gridDim.x = nthreads_;
}

ThreadPool::~ThreadPool()
{
  {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    stop_ = true;
  }
  condition_.notify_all();
  for(std::thread &worker: workers_) {
    worker.join();
  }

  workers_.clear();
}