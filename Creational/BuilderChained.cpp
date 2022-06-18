#include <iostream>
#include <string>

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

class ComputerBuilder {
public:
    virtual ComputerBuilder* BuildDisplay(std::string)   = 0;
    virtual ComputerBuilder* BuildMainFrame(std::string) = 0;
    virtual ComputerBuilder* BuildKeyboard(std::string)  = 0;
    virtual Computer*        Getcomputer()               = 0;

protected:
    Computer* m_product;
};

class ComputerSBuilder : public ComputerBuilder {
public:
    ComputerSBuilder() {}

    virtual ComputerBuilder* BuildDisplay(std::string display = "A") {
        m_display = display;
        return this;
    }

    virtual ComputerBuilder* BuildMainFrame(std::string mainframe = "A") {
        m_mainframe = mainframe;
        return this;
    }

    virtual ComputerBuilder* BuildKeyboard(std::string keyboard = "A") {
        m_keyboard = keyboard;
        return this;
    }

    virtual Computer* Getcomputer() {
        Computer* c = new Computer;
        c->SetDisplay(m_display);
        c->SetMainFrame(m_mainframe);
        c->SetKeyboard(m_keyboard);

        return c;
    }

private:
    std::string m_display   = "A";  // 显示器
    std::string m_mainframe = "A";  // 主机
    std::string m_keyboard  = "A";  // 键盘
};

int main(int argc, char const* argv[]) {
    ComputerBuilder* builder = new ComputerSBuilder;

    Computer* c = builder->BuildDisplay("A")->BuildMainFrame("B")->BuildKeyboard("C")->Getcomputer();
    c->Work();

    Computer* c1 = builder->BuildDisplay("A1")->BuildMainFrame("B1")->BuildKeyboard("C1")->Getcomputer();
    c1->Work();

    delete c1;
    delete c;

    return 0;
}