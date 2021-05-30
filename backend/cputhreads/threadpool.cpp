#include "threadpool.h"

thread_local unsigned int threadId_;
unsigned int threadN_;

using namespace ABSIM;

ThreadPool::ThreadPool(size_t threads) :
  id_( 0 )
{
  stop_ = false;
  if ( workers_.size() ) {
    return;
  }
  if ( !threads ) { nthreads_ = std::thread::hardware_concurrency(); } else { nthreads_ = threads; }
  debug() << "Creating ThreadPool with " << nthreads_ << " threads" << endmsg;
  for(size_t i = 0; i < nthreads_ ; ++i) {
    workers_.emplace_back( Worker( this , id_ ) );
    ++id_;
  }

  threadN_ = nthreads_;
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