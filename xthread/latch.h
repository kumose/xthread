#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>

namespace xthread {

    class Latch {
    public:
        static constexpr std::ptrdiff_t max() noexcept {
            return PTRDIFF_MAX;
        }

        explicit Latch(std::ptrdiff_t count) : count_(count) {}

        ~Latch() = default;

        Latch(const Latch&) = delete;
        Latch& operator=(const Latch&) = delete;

        void count_down(std::ptrdiff_t n = 1) {
            std::lock_guard<std::mutex> lock(mtx_);
            if (n > count_) {
                count_ = 0;
            } else {
                count_ -= n;
            }
            if (count_ == 0) {
                cv_.notify_all();
            }
        }

        bool try_wait() const noexcept {
            std::lock_guard<std::mutex> lock(mtx_);
            return count_ == 0;
        }

        void wait() const {
            std::unique_lock<std::mutex> lock(mtx_);
            cv_.wait(lock, [this] { return count_ == 0; });
        }

        void arrive_and_wait(std::ptrdiff_t n = 1) {
            count_down(n);
            wait();
        }

    private:
        mutable std::mutex mtx_;
        mutable std::condition_variable cv_;
        std::ptrdiff_t count_;
    };

} // namespace xthread
