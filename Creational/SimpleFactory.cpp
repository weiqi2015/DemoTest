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

// 工厂只生成两种电脑
class SimpleFactory {
public:
    computer* GetComputer(int type) {
        computer* m = nullptr;
        if (type == 1) {
            m = new computerA;
        } else if (type == 2) {
            m = new computerB;
        } else {
            std::cout << "There is no such computer!" << std::endl;
        }

        return m;
    }
};

int main(int argc, char const* argv[]) {
    // 联系工厂
    SimpleFactory* f = new SimpleFactory;
    // 找工厂要电脑
    computer* m = f->GetComputer(2);
    if (m) {
        // 工作
        m->Work();

        delete m;
    }

    return 0;
}