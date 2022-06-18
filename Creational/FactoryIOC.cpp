#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

template <class T>
class IocContainer {
public:
    IocContainer() {}
    ~IocContainer() {}

    // 注册需要创建对象的构造函数
    template <class Drived>
    void RegisterType(std::string strKey) {
        // 仿函数
        std::function<T*()> function = [] { return new Drived(); };
        RegisterType(strKey, function);
    }

    // 根据唯一标识查找对应的构造函数，并创建指针对象
    T* Resolve(std::string strKey) {
        if (m_creatorMap.find(strKey) == m_creatorMap.end())
            return nullptr;

        std::function<T*()> function = m_creatorMap[strKey];
        return function();
    }

    // 创建智能指针对象
    std::shared_ptr<T> ResolveShared(std::string strKey) {
        T* ptr = Resolve(strKey);
        return std::shared_ptr<T>(ptr);
    }

private:
    void RegisterType(std::string strKey, std::function<T*()> creator) {
        if (m_creatorMap.find(strKey) != m_creatorMap.end()) {
            throw std::invalid_argument("this key has already exist!");
        }

        m_creatorMap.emplace(strKey, creator);
    }

private:
    std::map<std::string, std::function<T*()>> m_creatorMap;
};

class Computer {
public:
    void SetDisplay(std::string display) {
        m_display = display;
    };

    void SetMainFrame(std::string mainframe) {
        m_mainframe = mainframe;
    }

    void SetKeyboard(std::string keyboard) {
        m_keyboard = keyboard;
    }

    void Work() {
        if (m_display.empty() || m_mainframe.empty() || m_keyboard.empty()) {
            std::cout << "Computer cannot work!" << std::endl;
            return;
        }

        std::cout << m_display << "MainFrame is working!" << std::endl;
        std::cout << m_mainframe << "Display is working!" << std::endl;
        std::cout << m_keyboard << "Keyboard is working!" << std::endl;
        std::cout << "Computer is working!" << std::endl;
    }

private:
    std::string m_display;    // 显示器
    std::string m_mainframe;  // 主机
    std::string m_keyboard;   // 键盘
};

class ComputerA : public Computer {
public:
    ComputerA() {
        SetDisplay("A牌");
        SetMainFrame("A牌");
        SetKeyboard("A牌");
    }
};

class ComputerB : public Computer {
public:
    ComputerB() {
        SetDisplay("B牌");
        SetMainFrame("B牌");
        SetKeyboard("B牌");
    }
};

class ComputerC : public Computer {
public:
    ComputerC() {
        SetDisplay("C牌");
        SetMainFrame("C牌");
        SetKeyboard("C牌");
    }
};

int main(int argc, char const* argv[]) {
    IocContainer<Computer> carIOC;
    carIOC.RegisterType<ComputerA>("computera");
    carIOC.RegisterType<ComputerB>("computerb");
    carIOC.RegisterType<ComputerC>("computerc");

    // 获取ComputerA型号电脑工作
    std::shared_ptr<Computer> c = carIOC.ResolveShared("computera");
    c->Work();

    return 0;
}
