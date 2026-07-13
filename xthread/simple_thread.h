#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <string_view>

namespace xthread {

    enum class SimpleThreadState {
        kNotStarted,
        kStarting,
        kRunning,
        kJoined,
    };

    class SimpleThread {
    public:
        SimpleThread() noexcept = default;

        explicit SimpleThread(std::string_view name) : name_(name) {}

        virtual ~SimpleThread();

        SimpleThread(const SimpleThread&) = delete;
        SimpleThread& operator=(const SimpleThread&) = delete;
        SimpleThread(SimpleThread&&) = delete;
        SimpleThread& operator=(SimpleThread&&) = delete;

        void start();
        void start_async();
        void join();

        void request_stop();

        SimpleThreadState state() const;
        bool joinable() const;

    protected:
        bool stop_requested() const noexcept {
            return stop_requested_.load(std::memory_order_relaxed);
        }

        virtual void run() = 0;

    private:
        std::thread thread_;
        std::string name_;
        std::atomic<bool> stop_requested_{false};
        SimpleThreadState state_{SimpleThreadState::kNotStarted};
        mutable std::mutex mtx_;
        std::condition_variable cv_;
    };

    inline SimpleThread::~SimpleThread() {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    inline void SimpleThread::start() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            if (state_ != SimpleThreadState::kNotStarted) {
                throw std::logic_error("SimpleThread already started");
            }
            state_ = SimpleThreadState::kStarting;
        }

        thread_ = std::thread([this] {
            {
                std::lock_guard<std::mutex> lock(mtx_);
                state_ = SimpleThreadState::kRunning;
                cv_.notify_all();
            }

            run();

            {
                std::lock_guard<std::mutex> lock(mtx_);
                state_ = SimpleThreadState::kJoined;
            }
            cv_.notify_all();
        });

        {
            std::unique_lock<std::mutex> lock(mtx_);
            cv_.wait(lock, [this] {
                return state_ >= SimpleThreadState::kRunning;
            });
        }
    }

    inline void SimpleThread::start_async() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            if (state_ != SimpleThreadState::kNotStarted) {
                throw std::logic_error("SimpleThread already started");
            }
            state_ = SimpleThreadState::kStarting;
        }

        thread_ = std::thread([this] {
            {
                std::lock_guard<std::mutex> lock(mtx_);
                state_ = SimpleThreadState::kRunning;
                cv_.notify_all();
            }

            run();

            {
                std::lock_guard<std::mutex> lock(mtx_);
                state_ = SimpleThreadState::kJoined;
            }
            cv_.notify_all();
        });
    }

    inline void SimpleThread::join() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            if (state_ == SimpleThreadState::kNotStarted) {
                throw std::logic_error("SimpleThread not started");
            }
            if (state_ == SimpleThreadState::kJoined) {
                return;
            }
        }

        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this] {
            return state_ == SimpleThreadState::kJoined;
        });
    }

    inline void SimpleThread::request_stop() {
        stop_requested_.store(true, std::memory_order_relaxed);
    }

    inline SimpleThreadState SimpleThread::state() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return state_;
    }

    inline bool SimpleThread::joinable() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return state_ >= SimpleThreadState::kStarting &&
               state_ <= SimpleThreadState::kRunning;
    }

} // namespace xthread
