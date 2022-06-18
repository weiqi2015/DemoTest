#include <iostream>
#include <map>

// ===========================================
// 动态创建类

// 定义函数指针
typedef void* (*Constructor)();

// 工厂类，用于注册、保存和创建需要动态创建的类
class CObjectFactory {
public:
    static void RegisterClass(std::string className, Constructor constructor) {
        Constructors()[className] = constructor;
    }

    static void* CreateObject(std::string className) {
        // 如果查看返回指针指向的不是结束指针为查找到
        if (Constructors().find(className) != Constructors().end()) {
            // 获取 map 的 value 值
            return Constructors().find(className)->second();
        }

        return nullptr;
    }

private:
    inline static std::map<std::string, Constructor>& Constructors() {
        static std::map<std::string, Constructor> instance;
        return instance;
    }
};

// 定义宏，用于注册动态创建类
#define REG_CLASS(className)                                                                                           \
    class className##Helper {                                                                                          \
    public:                                                                                                            \
        className##Helper() {                                                                                          \
            CObjectFactory::RegisterClass(#className, className##Helper::CreateObjFunc);                               \
        }                                                                                                              \
        static void* CreateObjFunc() {                                                                                 \
            return new className;                                                                                      \
        }                                                                                                              \
    };                                                                                                                 \
    className##Helper className##helper;

// ===========================================

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

// 简单工厂-扩展-动态创建对象
// 优点：减轻工厂的责任，添加产品时不必修改工厂的逻辑代码，即原有程序基本不用改变。动态地创建任意产品，完全解耦。可实现配置化开发，从配置文件中读取字符串动态创建对象，特别容易维护和扩展。
class AutoFactory {
public:
    static Computer* GetComputer(std::string ComputerName) {
        return static_cast<Computer*>(CObjectFactory::CreateObject(ComputerName));
    }
};

// 目前工厂生产注册产品
REG_CLASS(ComputerA)
REG_CLASS(ComputerB)
REG_CLASS(ComputerC)

//
int main(int argc, char const* argv[]) {
    // 找工厂要ComputerB型号的电脑
    Computer* m = AutoFactory::GetComputer("ComputerB");
    if (m) {
        m->Work();
        delete m;
    }

    return 0;
}
