// 2018-04-13T18:23+08:00
#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

template <typename T>
class Singleton
{
public:
    static T &GetInstance()
    {
        static T instance {};
        return instance;
    }

    Singleton(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&) = delete;

protected:
    Singleton() = default;
};

#endif // SINGLETON_HPP_


// References:
// https://www.zhihu.com/question/267013757
// https://www.zhihu.com/question/272087885
// https://stackoverflow.com/questions/11711920/how-to-implement-multithread-safe-singleton-in-c11-without-using-mutex