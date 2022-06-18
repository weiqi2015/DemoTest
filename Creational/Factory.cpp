#include <iostream>
#include <string>

class computer {
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
            std::cout << "computer cannot work!" << std::endl;
            return;
        }

        std::cout << m_display << "MainFrame is working!" << std::endl;
        std::cout << m_mainframe << "Display is working!" << std::endl;
        std::cout << m_keyboard << "Keyboard is working!" << std::endl;
        std::cout << "computer is working!" << std::endl;
    }

private:
    std::string m_display;    // 显示器
    std::string m_mainframe;  // 主机
    std::string m_keyboard;   // 键盘
};

class computerA : public computer {
public:
    computerA() {
        SetDisplay("A牌");
        SetMainFrame("A牌");
        SetKeyboard("A牌");
    }
};

class computerB : public computer {
public:
    computerB() {
        SetDisplay("B牌");
        SetMainFrame("B牌");
        SetKeyboard("B牌");
    }
};

class computerC : public computer {
public:
    computerC() {
        SetDisplay("C牌");
        SetMainFrame("C牌");
        SetKeyboard("C牌");
    }
};

// 工厂只生成两种电脑
class SimpleFactory {
public:
    virtual computer* GetComputer() = 0;
};

class SimpleFactoryA : public SimpleFactory {
public:
    virtual computer* GetComputer() {
        return new computerA;
    }
};

class SimpleFactoryB : public SimpleFactory {
public:
    virtual computer* GetComputer() {
        return new computerB;
    }
};

class SimpleFactoryC : public SimpleFactory {
public:
    virtual computer* GetComputer() {
        return new computerC;
    }
};

int main(int argc, char const* argv[]) {
    // 联系工厂C
    SimpleFactory* f = new SimpleFactoryC;
    // 新电脑
    computer* m = f->GetComputer();
    if (m) {
        // 工作
        m->Work();
    }

    delete m;

    return 0;
}