#include "matrix.h"
#include <xthread/taskflow.h>

// wavefront computing
void wavefront_taskflow(unsigned num_threads) {

  static xthread::Executor executor(num_threads);
  xthread::Taskflow taskflow;

  std::vector<std::vector<xthread::Task>> node(MB);

  for(auto &n : node){
    for(int i=0; i<NB; i++){
      n.emplace_back(taskflow.placeholder());
    }
  }

  matrix[M-1][N-1] = 0;
  for( int i=MB; --i>=0; ) {
    for( int j=NB; --j>=0; ) {
      node[i][j].work(
        [=]() {
          block_computation(i, j);
        }
      );

      if(j+1 < NB) node[i][j].precede(node[i][j+1]);
      if(i+1 < MB) node[i][j].precede(node[i+1][j]);
    }
  }

  executor.run(taskflow).get();
}

std::chrono::microseconds measure_time_taskflow(unsigned num_threads) {
  auto beg = std::chrono::high_resolution_clock::now();
  wavefront_taskflow(num_threads);
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
}


