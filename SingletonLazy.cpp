#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

// 单例模式
// 懒汉式：在使用的时候才会创建，需要注意线程安全问题
// 处理：
//      1 做双重检查，检查 -> 加锁 -> 再检查
//      2 reorder问题，禁止编译器优化
class Singleton {
public:
    static Singleton* GetInstance() {
#ifdef _win32
        if (m_instance == nullptr) {
            ::EnterCriticalSection(&m_mutex);
            if (m_instance == nullptr) {
                m_instance = new Singleton;
            }
            ::LeaveCriticalSection(&m_mutex);
        }
#else
        Singleton* tmp = m_instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);

            tmp = m_instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new Singleton;
                std::atomic_thread_fence(std::memory_order_relaxed);
                m_instance.store(tmp, std::memory_order_relaxed);
            }
        }
#endif

        return m_instance;
    }

private:
    Singleton() {};
    ~Singleton() {};
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    // 原子操作
    static std::atomic<Singleton*> m_instance;
    // windows 下 MinGW可能会报错，std中没有mutex，需要 posix
#ifdef _win32
    // static CRITICAL_SECTION m_mutex;
#else
    static std::mutex m_mutex;
#endif
};

std::atomic<Singleton*> Singleton::m_instance = nullptr;

#ifdef _win32
    CRITICAL_SECTION m_mutex;
#else
    std::mutex Singleton::m_mutex;
#endif

int main(int argc, char const *argv[])
{
#ifdef _win32
    ::InitializeCriticalSection(&Singleton::m_mutex);
#endif

    Singleton* p1 = Singleton::GetInstance();
    Singleton* p2 = Singleton::GetInstance();

#ifdef _win32
    ::DeleteCriticalSection(&Singleton::m_mutex);
#endif

    std::cout << "p1：" << p1 << std::endl;
    std::cout << "p2：" << p2 << std::endl;

    return 0;
}
