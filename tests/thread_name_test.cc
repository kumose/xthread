#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <xthread/thread_name.h>
#include <doctest.h>
#include <cstring>

TEST_CASE("thread_name") {
  xthread::set_current_thread_name("test-worker");
  auto name = xthread::current_thread_name();
  CHECK(std::strcmp(name.c_str(), "test-worker") == 0);
}
