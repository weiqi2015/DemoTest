#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

// 单例模式
// 懒汉式：在使用的时候才会创建，需要注意线程安全问题
class Singleton {
public:
    static Singleton& GetInstance() {
        // Static定义，内存中有且只有一个变量，只能初始化一次
        // c++11 magic static 特性：如果当变量在初始化的时候，并发同时进⼊声明语句，并发线程将会阻塞等待初始化结束。
        static Singleton instance;

        return instance;
    }

private:
    Singleton() {};
    ~Singleton() {};
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

int main(int argc, char const *argv[])
{
    Singleton& p1 = Singleton::GetInstance();
    Singleton& p2 = Singleton::GetInstance();

    std::cout << "p1：" << &p1 << std::endl;
    std::cout << "p2：" << &p2 << std::endl;

    return 0;
}
