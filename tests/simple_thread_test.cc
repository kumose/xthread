#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <xthread/simple_thread.h>
#include <doctest.h>
#include <thread>

struct Worker : xthread::SimpleThread {
  int count = 0;
  void run() override {
    while (!stop_requested()) {
      count++;
    }
  }
};

TEST_CASE("SimpleThread.start_and_stop") {
  Worker w;
  w.start();
  CHECK(w.state() == xthread::SimpleThreadState::kRunning);
  w.request_stop();
  w.join();
  CHECK(w.state() == xthread::SimpleThreadState::kJoined);
  CHECK(w.count > 0);
}

TEST_CASE("SimpleThread.start_async") {
  Worker w;
  w.start_async();
  // start_async 不保证线程已进入 run()，所以不能假设 count > 0
  w.request_stop();
  w.join();
  CHECK(w.state() == xthread::SimpleThreadState::kJoined);
}

TEST_CASE("SimpleThread.double_start") {
  Worker w;
  w.start();
  CHECK_THROWS_AS(w.start(), std::logic_error);
  w.request_stop();
  w.join();
}

TEST_CASE("SimpleThread.join_before_start") {
  Worker w;
  CHECK_THROWS_AS(w.join(), std::logic_error);
}

TEST_CASE("SimpleThread.stop_before_run") {
  for (int i = 0; i < 100; i++) {
    Worker w;
    w.start();
    w.request_stop();
    w.join();
    REQUIRE(w.count > 0);
  }
}
