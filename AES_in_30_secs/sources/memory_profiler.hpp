#ifndef MEMORY_PROFILER_HPP
#define MEMORY_PROFILER_HPP

#include <iostream>
#include <string>
#include <malloc.h>
#include <cstdint>

class MemoryProfiler {
    std::string function_name;
    size_t heap_start;
    void* stack_base;
    uintptr_t stack_start;

    size_t get_heap_usage() {
        struct mallinfo info = mallinfo();
        return static_cast<size_t>(info.uordblks); // Total allocated space
    }

    uintptr_t get_stack_pointer() {
        volatile int local;
        return reinterpret_cast<uintptr_t>(&local);
    }

public:
    MemoryProfiler(const std::string& func)
        : function_name(func) {
        heap_start = get_heap_usage();
        stack_start = get_stack_pointer();

        std::cout << "[ENTER] " << function_name
                  << " - Heap: " << heap_start
                  << " bytes, Stack pointer: 0x" << std::hex << stack_start << std::dec << "\n";
    }

    ~MemoryProfiler() {
        size_t heap_end = get_heap_usage();
        uintptr_t stack_end = get_stack_pointer();
        long heap_diff = static_cast<long>(heap_end) - static_cast<long>(heap_start);
        long stack_diff = static_cast<long>(stack_start) - static_cast<long>(stack_end);

        std::cout << "[EXIT ] " << function_name
                  << " - Heap: " << heap_end
                  << " bytes (Δ: " << (heap_diff >= 0 ? "+" : "") << heap_diff << "), "
                  << "Stack usage: " << stack_diff << " bytes\n";
    }
};

#define PROFILE_MEMORY() MemoryProfiler _mem_profiler_(__func__)

#endif
