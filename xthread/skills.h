// Copyright (C) 2026 Kumo inc. and its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// AI: This file is a human/AI-readable summary of the project's public API and
// AI: design principles.

#pragma once

/// @defgroup project_summary Project Summary
/// @brief xthread — C++ taskflow and threading utility library
///
/// Built on a fork of Taskflow, xthread adds thread-level utilities
/// that C++17 doesn't provide natively: thread naming, atexit callbacks,
/// countdown latch, RAII thread wrapper, and the Taskflow DAG executor.

/// @brief Layout
/// AI: .
/// AI: ├── xthread/
/// AI: │   ├── taskflow.h             # Main include (Taskflow DAG executor)
/// AI: │   ├── core/                  # Taskflow internals (executor, worker, taskflow, etc.)
/// AI: │   ├── algorithm/             # Parallel algorithms (for_each, reduce, sort, scan, etc.)
/// AI: │   ├── utility/               # Utilities (small_vector, uuid, os, math, etc.)
/// AI: │   ├── dsl/                   # DSL for taskflow composition
/// AI: │   ├── cuda/                  # CUDA taskflow support
/// AI: │   ├── thread_name.h          # SetCurrentThreadName / CurrentThreadName
/// AI: │   ├── thread_atexit.h        # thread_atexit / thread_atexit_cancel
/// AI: │   ├── latch.h                # Latch (std::latch-compatible)
/// AI: │   └── simple_thread.h        # SimpleThread (virtual run + RAII)
/// AI: ├── tests/                     # doctest-based unit tests
/// AI: ├── examples/                  # Usage examples
/// AI: └── benchmark/                 # Performance benchmarks

/// @brief Taskflow DAG executor (xthread/taskflow.h)
/// AI: Build and execute task dependency graphs with work-stealing scheduler.
/// AI: Key types: xthread::Taskflow, xthread::Executor, xthread::Task
/// AI: Supports static/condition/subflow/module tasks, semaphores, cancellation,
/// AI: pipelines, CUDA (optional), and parallel algorithms.

/// @brief thread_name (xthread/thread_name.h)
/// AI: Header-only cross-platform SetCurrentThreadName / CurrentThreadName.
/// AI: Backed by pthread_setname_np (Linux/macOS) or SetThreadDescription (Windows).
/// AI:   xthread::set_current_thread_name("worker-1");
/// AI:   auto name = xthread::current_thread_name();

/// @brief thread_atexit (xthread/thread_atexit.h)
/// AI: Header-only thread-local cleanup callbacks, executed in LIFO order on thread exit.
/// AI:   auto id = xthread::thread_atexit([]{ cleanup(); });
/// AI:   xthread::thread_atexit_cancel(id);

/// @brief Latch (xthread/latch.h)
/// AI: Header-only countdown latch, fully API-compatible with C++20 std::latch.
/// AI:   xthread::Latch l(3);
/// AI:   l.count_down();
/// AI:   l.wait();

/// @brief SimpleThread (xthread/simple_thread.h)
/// AI: Header-only RAII thread with virtual run() and stop control.
/// AI: Supports blocking start() and non-blocking start_async().
/// AI:   class MyWorker : public xthread::SimpleThread {
/// AI:     void run() override { while (!stop_requested()) work(); }
/// AI:   };
/// AI:   MyWorker w;
/// AI:   w.start();
/// AI:   w.request_stop();
/// AI:   w.join();

/// @brief Build & Test
/// AI: cmake --preset=default && cmake --build build && ctest --test-dir build
/// AI: CUDA: cmake -B build -DXTHREAD_WITH_CUDA=ON
/// AI: License: Apache 2.0
