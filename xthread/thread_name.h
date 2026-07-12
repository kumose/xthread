#pragma once

#include <string>
#include <thread>

#if defined(__linux__)
#include <pthread.h>
#elif defined(__APPLE__)
#include <pthread.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

namespace xthread {

inline void set_current_thread_name(const char* name) {
#if defined(__linux__)
    pthread_setname_np(pthread_self(), name);
#elif defined(__APPLE__)
    pthread_setname_np(name);
#elif defined(_WIN32)
    wchar_t wname[256];
    int len = MultiByteToWideChar(CP_UTF8, 0, name, -1, wname, 256);
    if (len > 0) {
        SetThreadDescription(GetCurrentThread(), wname);
    }
#endif
}

inline std::string current_thread_name() {
#if defined(__linux__)
    char buf[16] = {};
    pthread_getname_np(pthread_self(), buf, sizeof(buf));
    return buf;
#elif defined(__APPLE__)
    char buf[64] = {};
    pthread_getname_np(pthread_self(), buf, sizeof(buf));
    return buf;
#elif defined(_WIN32)
    PWSTR wname = nullptr;
    if (SUCCEEDED(GetThreadDescription(GetCurrentThread(), &wname))) {
        int len = WideCharToMultiByte(CP_UTF8, 0, wname, -1, nullptr, 0, nullptr, nullptr);
        std::string name(len - 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, wname, -1, &name[0], len, nullptr, nullptr);
        LocalFree(wname);
        return name;
    }
    return {};
#endif
}

} // namespace xthread
