#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// A thread pool in cpp11.
//

#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#include <functional>
#include <memory>
#include <queue>
#include <vector>

#include "core/error.h"

#ifndef DJA_THREAD_POOL_H_
#define DJA_THREAD_POOL_H_

namespace dja {
class ThreadPool {
 public:
  ThreadPool(int threads) : stop_(false) {
    for (int i = 0; i < threads; ++i) {
      // lambda expressions are load in the thread vector as tasks
      workers_.emplace_back([this] {
        while (1) {
          // for each worker, repeatedly getting a task from the queue
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(this->queue_mutex_);
            this->condition_.wait(
                // get lock
                lock,
                // if the expression is false (), stuck
                [this] { return (this->stop_ || !this->tasks_.empty()); });
            if (this->stop_ && this->tasks_.empty()) {
              return;
            }
            task = std::move(this->tasks_.front());
            this->tasks_.pop();
            // unique_lock will release the mutex after leaving this space
          }
          // execute the task
          task();
        }
      });
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(queue_mutex_);
      stop_ = true;
    }
    condition_.notify_all();
    for (std::thread& worker : workers_) {
      worker.join();
    }
  }

  /// \brief
  ///
  /// \param f A function object with a complete type F.
  /// The type of return value will be derived through the std::result_of<>.
  /// \param args All parameters that the function f needs.
  ///
  /// \return The return type is qualified by std::future...
  template <typename F, typename... Args>
  auto enqueue(F&& f, Args&&... args)
      -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(queue_mutex_);
      // don't allow enqueueing after stopping the pool
      if (stop_) {
        throw std::runtime_error("enqueue on stopped ThreadPool");
      }
      tasks_.emplace([task]() { (*task)(); });
      // unique_lock will release the mutex after leaving this space
    }
    condition_.notify_one();
    return res;
  }

 private:
  ///< \brief the task queue
  std::queue<std::function<void()>> tasks_;
  ///< \brief keep track of threads so we can join them
  std::vector<std::thread> workers_;

  bool stop_;
  std::mutex queue_mutex_;
  std::condition_variable condition_;
};
}  // namespace dja

#endif
