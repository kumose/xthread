// This program demonstrates how to use a runtime task to forcefully
// schedule an active task that would never be scheduled.

#include <xthread/taskflow.hpp>

int main() {

  xthread::Taskflow taskflow("Runtime Tasking");
  xthread::Executor executor;

  xthread::Task A, B, C, D;

  std::tie(A, B, C, D) = taskflow.emplace(
    [] () { return 0; },
    [&C] (xthread::Runtime& rt) {  // C must be captured by reference
      std::cout << "B\n";
      rt.schedule(C);
    },
    [] () { std::cout << "C\n"; },
    [] () { std::cout << "D\n"; }
  );

  // name tasks
  A.name("A");
  B.name("B");
  C.name("C");
  D.name("D");

  // create conditional dependencies
  A.precede(B, C, D);

  // dump the graph structure
  taskflow.dump(std::cout);

  // we will see both B and C in the output
  executor.run(taskflow).wait();

  return 0;
}
