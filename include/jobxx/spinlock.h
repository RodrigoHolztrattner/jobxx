// jobxx - C++ lightweight task library.
//
// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non - commercial, and by any
// means.
// 
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 
// For more information, please refer to <http://unlicense.org/>
//
// Authors:
//   Sean Middleditch <sean.middleditch@gmail.com>

#if !defined(_guard_JOBXX_SPINLOCK_H)
#define _guard_JOBXX_SPINLOCK_H
#pragma once

#include <atomic>

namespace jobxx
{

    class spinlock
    {
    public:
        spinlock() = default;

        spinlock(spinlock const&) = delete;
        spinlock& operator=(spinlock const&) = delete;

        inline void lock();
        inline void unlock();

    private:
        std::atomic<bool> _flag = false;
    };

    

    void spinlock::lock()
    {
        for (;;)
        {
            bool expected = false;
            if (_flag.compare_exchange_weak(expected, true, std::memory_order_acquire))
            {
                break;
            }
            // FIXME: backoff
        }
    }

    void spinlock::unlock()
    {
        _flag.store(false, std::memory_order_release);
    }

}

#endif // defined(_guard_JOBXX_SPINLOCK_H)
