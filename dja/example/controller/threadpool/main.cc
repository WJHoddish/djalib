// Copyright (C) summer 2019 Jiaheng Wang.
// License(BSD)
// Author: Jiaheng Wang
// dja5
//

#include <chrono>

#include "thread_pool.h"

int main(int argc, char* argv[]) {
  {
    using namespace dja;

    ThreadPool pool(4);

    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i) {
      results.emplace_back(pool.enqueue([i] {
        std::cout << "hello " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "world " << i << std::endl;
        return i * i;
      }));
    }

    std::system("pause");

    for (auto&& result : results) std::cout << result.get() << ' ';
  }
  return 0;
}