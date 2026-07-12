#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <xthread/latch.h>
#include <doctest.h>
#include <atomic>
#include <thread>

TEST_CASE("Latch.count_down_and_wait") {
  xthread::Latch l(2);
  std::atomic<int> c{0};
  std::thread t1([&] { c++; l.count_down(); });
  std::thread t2([&] { c++; l.count_down(); });
  l.wait();
  CHECK(c == 2);
  t1.join();
  t2.join();
  CHECK(l.try_wait());
}

TEST_CASE("Latch.arrive_and_wait") {
  xthread::Latch l(3);
  std::atomic<bool> arrived{false};
  std::thread t([&] {
    l.arrive_and_wait();
    arrived = true;
  });
  CHECK(!arrived);
  l.count_down();
  CHECK(!arrived);
  l.count_down();
  t.join();
  CHECK(arrived);
  CHECK(l.try_wait());
}

TEST_CASE("Latch.count_down_zero") {
  xthread::Latch l(1);
  l.count_down(0);
  CHECK(!l.try_wait());
  l.count_down();
  CHECK(l.try_wait());
}

TEST_CASE("Latch.const_methods") {
  const xthread::Latch l(0);
  CHECK(l.try_wait());
}
