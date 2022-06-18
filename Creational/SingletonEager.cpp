#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

// 单例模式
// 饿汉式：初始化的时候就创建单例对象
// 优点：线程安全、便于使用，简单；
// 缺点：如果对象一直没有使用，会浪费内存空间。
class Singleton {
public:
    static Singleton* GetInstance() {
        return &m_instance;
    }

private:
    // 构造和析构
    Singleton(){};
    ~Singleton(){};
    // 拷贝和复制
    Singleton(const Singleton&)            = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    static Singleton m_instance;
};

Singleton Singleton::m_instance;

int main(int argc, char const* argv[]) {
    Singleton* p1 = Singleton::GetInstance();
    Singleton* p2 = Singleton::GetInstance();

    std::cout << "p1：" << p1 << std::endl;
    std::cout << "p2：" << p2 << std::endl;

    return 0;
}
