#include "for_each.h"
#include <xthread/taskflow.h>
#include <xthread/algorithm/for_each.h>

void for_each_taskflow(size_t num_threads) {

  static xthread::Executor executor(num_threads);
  xthread::Taskflow taskflow;

  xthread::IndexRange<size_t> range(0, vec.size(), 1);

  taskflow.for_each_by_index(range, [&](xthread::IndexRange<size_t> sr){
    for(size_t i=sr.begin(); i<sr.end(); i+=sr.step_size()) {
      vec[i] = std::tan(vec[i]);
    }
  });

  executor.run(taskflow).get();


  //executor.async(xthread::make_for_each_by_index_task(range, [&](xthread::IndexRange<size_t> sr) {
  //  for(size_t i=sr.begin(); i<sr.end(); i+=sr.step_size()) {
  //    vec[i] = std::tan(vec[i]);
  //  }
  //})).wait();
}

std::chrono::microseconds measure_time_taskflow(size_t num_threads) {
  auto beg = std::chrono::high_resolution_clock::now();
  for_each_taskflow(num_threads);
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
}


