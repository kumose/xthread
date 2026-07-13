#pragma once

#include <cstdint>
#include <functional>
#include <vector>

namespace xthread {

    namespace detail {

        struct thread_atexit_manager {
            uint64_t next_id = 1;
            std::vector<std::pair<uint64_t, std::function<void()>>> callbacks;

            ~thread_atexit_manager() {
                while (!callbacks.empty()) {
                    auto cb = std::move(callbacks.back().second);
                    callbacks.pop_back();
                    cb();
                }
            }
        };

        inline thread_atexit_manager& get_atexit_manager() {
            static thread_local thread_atexit_manager mgr;
            return mgr;
        }

    } // namespace detail

    template <typename F>
    uint64_t thread_atexit(F&& f) {
        auto& mgr = detail::get_atexit_manager();
        auto id = mgr.next_id++;
        mgr.callbacks.emplace_back(id, std::forward<F>(f));
        return id;
    }

    inline bool thread_atexit_cancel(uint64_t id) {
        auto& mgr = detail::get_atexit_manager();
        for (auto it = mgr.callbacks.begin(); it != mgr.callbacks.end(); ++it) {
            if (it->first == id) {
                mgr.callbacks.erase(it);
                return true;
            }
        }
        return false;
    }

} // namespace xthread
