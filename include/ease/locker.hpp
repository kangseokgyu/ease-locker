#pragma once

#include <memory>
#include <iostream>

#include "ease/guard.hpp"

namespace ease {

class locker {
public:
  locker(std::shared_ptr<ease::mutex> m) {
    _m = m;
    if (_m) {
      _m->lock();
    }
  }

  locker(std::shared_ptr<ease::std_mutex> m) {
    _m = std::dynamic_pointer_cast<ease::mutex>(m);
    if (_m) {
      _m->lock();
    }
  }

  locker(std::shared_ptr<ease::flock_mutex> m) {
    _m = std::dynamic_pointer_cast<ease::mutex>(m);
    if (_m) {
      _m->lock();
    }
  }

  ~locker() {
    if (_m) {
      _m->unlock();
      _m = nullptr;
    }
  }

private:
  std::shared_ptr<ease::mutex> _m = nullptr;
};

}; // namespace ease
