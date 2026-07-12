#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <xthread/thread_atexit.h>
#include <doctest.h>
#include <atomic>
#include <thread>
#include <vector>

TEST_CASE("thread_atexit.basic") {
  std::atomic<int> count{0};
  {
    std::thread t([&] {
      xthread::thread_atexit([&] { count++; });
      xthread::thread_atexit([&] { count++; });
    });
    t.join();
  }
  CHECK(count == 2);
}

TEST_CASE("thread_atexit.cancel") {
  std::atomic<int> count{0};
  {
    std::thread t([&] {
      auto id = xthread::thread_atexit([&] { count++; });
      xthread::thread_atexit_cancel(id);
    });
    t.join();
  }
  CHECK(count == 0);
}

TEST_CASE("thread_atexit.main_thread") {
  std::atomic<int> count{0};
  auto id = xthread::thread_atexit([&] { count++; });
  xthread::thread_atexit([&] { count++; });
  (void)id;
  CHECK(count == 0); // not yet run
}
