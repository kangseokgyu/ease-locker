#include <gtest/gtest.h>

#include <thread>

#include "ease/guard.hpp"
#include "ease/locker.hpp"

void func(std::shared_ptr<ease::mutex> m) {
  ease::locker guard(m);
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

TEST(guard_test, lock_guard_test) {
  auto m1 = std::make_shared<ease::flock_mutex>("/tmp/test.lock");
  auto m2 = std::make_shared<ease::flock_mutex>("/tmp/test.lock");
  auto m3 = std::make_shared<ease::flock_mutex>("/tmp/test.lock");
  auto m4 = std::make_shared<ease::flock_mutex>("/tmp/test.lock");
  auto m5 = std::make_shared<ease::flock_mutex>("/tmp/test.lock");
  auto m6 = std::make_shared<ease::flock_mutex>("/tmp/test.lock");

  std::thread t1(func, m1);
  std::thread t2(func, m2);
  std::thread t3(func, m3);
  std::thread t4(func, m4);
  std::thread t5(func, m5);
  std::thread t6(func, m6);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
}

TEST(guard_test, std_mutex_test) {
  auto m1 = std::make_shared<ease::std_mutex>();

  std::thread t1(func, m1);
  std::thread t2(func, m1);
  std::thread t3(func, m1);
  std::thread t4(func, m1);
  std::thread t5(func, m1);
  std::thread t6(func, m1);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
}
