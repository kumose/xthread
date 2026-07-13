#include "sort.h"
#include <xthread/taskflow.h>
#include <xthread/algorithm/sort.h>

void sort_taskflow(size_t num_threads) {

  static xthread::Executor executor(num_threads);
  xthread::Taskflow taskflow;

  taskflow.sort(vec.begin(), vec.end());

  executor.run(taskflow).get();
}

std::chrono::microseconds measure_time_taskflow(size_t num_threads) {
  auto beg = std::chrono::high_resolution_clock::now();
  sort_taskflow(num_threads);
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
}


