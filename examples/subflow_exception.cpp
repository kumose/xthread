// This program demonstrates the exception in subflow.

#include <xthread/taskflow.hpp>

int main() {
    xthread::Executor executor;
    xthread::Taskflow taskflow;

    taskflow.emplace([](xthread::Subflow &sf) {
        xthread::Task A = sf.emplace([]() {
            std::cout << "Task A\n";
            throw std::runtime_error("exception on A");
        });
        xthread::Task B = sf.emplace([]() {
            std::cout << "Task B\n";
        });
        A.precede(B);
        sf.join();
    });

    try {
        executor.run(taskflow).get();
    } catch (const std::runtime_error &re) {
        std::cout << "exception thrown from running the taskflow: " << re.what() << '\n';
    }

    return 0;
}
