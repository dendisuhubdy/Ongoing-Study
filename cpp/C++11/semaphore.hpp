// 2018-03-21T09:11+08:00
#ifndef SEMAPHORE_HPP_
#define SEMAPHORE_HPP_

#include <cassert>
#include <chrono>
#include <condition_variable>
#include <mutex>


class Semaphore
{
public:
    explicit Semaphore(int avail = 0) noexcept
        : avail_(avail)
    {
        assert(avail >= 0);
    }

    ~Semaphore() noexcept
    {
    }

    Semaphore(const Semaphore &) = delete;
    Semaphore &operator=(const Semaphore &) = delete;

    void Acquire(int n = 1)
    {
        assert(n >= 0);

        std::unique_lock<std::mutex> lock(mutex_);

#if 1
        cond_.wait(lock, [&,this] { return avail_ >= n; });
#else
        while (avail_ < n)
            cond_.wait(lock);
#endif

        avail_ -= n;
    }

    bool TryAcquire(int n = 1, int timeout = -1)
    {
        assert(n >= 0);

        std::unique_lock<std::mutex> lock(mutex_);

        if (timeout < 0)
        {
            while (avail_ < n)
                cond_.wait(lock);
        }
        else
        {
            cond_.wait_for(lock, std::chrono::milliseconds(timeout));
            if (avail_ < n)
                return false;
        }

        avail_ -= n;

        return true;
    }

    void Release(int n = 1)
    {
        assert(n >= 0);

        std::lock_guard<std::mutex> lock(mutex_);
        avail_ += n;

        if (n == 1)
            cond_.notify_one();
        else
            cond_.notify_all();
    }

    int Available()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return avail_;
    }

private:
    std::mutex mutex_;
    std::condition_variable cond_;
    int avail_;
};

#endif // SEMAPHORE_HPP_


// References:
// QtCore/QSemaphore
// https://github.com/drh/cii/blob/master/include/sem.h
// https://stackoverflow.com/questions/4792449/c0x-has-no-semaphores-how-to-synchronize-threads
// https://github.com/preshing/cpp11-on-multicore/blob/master/common/sema.h
// https://gist.github.com/sguzman/9594227
// https://stackoverflow.com/questions/42269611/non-blocking-semaphores-in-c11

// https://www.cprogramming.com/c++11/c++11-lambda-closures.html
// https://stackoverflow.com/questions/16323032/why-cant-i-capture-this-by-reference-this-in-lambda
// https://stackoverflow.com/questions/32922053/c-lambda-capture-member-variable
// https://stackoverflow.com/questions/7895879/using-member-variable-in-lambda-capture-list-inside-a-member-function

// About `Spurious wakeup`:
// C++ Concurrency in Action
// https://en.wikipedia.org/wiki/Spurious_wakeup
// https://blogs.msdn.microsoft.com/oldnewthing/20180201-00/?p=97946
// https://www.douban.com/note/309639829/
// https://stackoverflow.com/questions/8594591/why-does-pthread-cond-wait-have-spurious-wakeups
// https://stackoverflow.com/questions/31871267/how-does-condition-variablewait-for-deal-with-spurious-wakeups
// http://en.cppreference.com/w/cpp/thread/condition_variable
// >When the condition variable is notified, a timeout expires, or a spurious 
//  wakeup occurs, the thread is awakened, and the mutex is atomically reacquired. 
//  The thread should then check the condition and resume waiting if the wake up was spurious. 
// >template< class Predicate >
//  void wait( std::unique_lock<std::mutex>& lock, Predicate pred );
//  Equivalent to
//  while (!pred()) {
//      wait(lock);
//  }
// http://www.modernescpp.com/index.php/condition-variables
// The implementation of:
//   1. wait(lock);
//   2. wait(lock, pred);
// in VS2017:
/*
    void wait(unique_lock<mutex>& _Lck)
        {   // wait for signal
        // Nothing to do to comply with LWG 2135 because std::mutex lock/unlock are nothrow
        _Cnd_waitX(_Mycnd(), _Lck.mutex()->_Mymtx());
        }

    template<class _Predicate>
        void wait(unique_lock<mutex>& _Lck, _Predicate _Pred)
        {   // wait for signal and test predicate
        while (!_Pred())
            wait(_Lck);
        }
*/

// 2018-08-01T12:23+08:00
// Multithreading Applications in Win32
// >Semaphores are often used to protect fixed-size ring buffers.
//  Programs that want to read from the ring buffer would wait on the sema-
//  phore. The thread that writes to the ring buffer may write more than one
//  thing to the buffer, in which case the release count would be the number of
//  things written to the buffer.
// >With the ring buffer example, the semaphore would usually be created
//  with a release count of zero so that any thread waiting would block. As
//  things are added to the buffer, the semaphore is incremented with Release-
//  Semaphore ( ) and threads waiting would be allowed to run.

