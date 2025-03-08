#pragma once

#include <mutex>
#include <string>
#include <iostream>

#include <fcntl.h>
#include <unistd.h>

namespace ease {

class mutex {
public:
  virtual ~mutex() = default;
  virtual void lock() = 0;
  virtual void unlock() = 0;
};

class std_mutex : public mutex {
public:
  virtual void lock() override {
    _m.lock();
  }

  virtual void unlock() override {
    _m.unlock();
  }

private:
  std::mutex _m;
};

class flock_mutex : public mutex {
public:
  flock_mutex(const std::string &filepath) {
    _fd = open(filepath.c_str(), O_CREAT | O_RDWR, 0666);
  }
  virtual ~flock_mutex() {
    if (_fd != -1) {
      close(_fd);
      _fd = -1;
    }
  }

  virtual void lock() override {
    flock(_fd, LOCK_EX);
  }

  virtual void unlock() override {
    flock(_fd, LOCK_UN);
  }

private:
  int _fd = -1;
};

}; // namespace ease
