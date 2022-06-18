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
    virtual void      BuildDisplay()   = 0;
    virtual void      BuildMainFrame() = 0;
    virtual void      BuildKeyboard()  = 0;
    virtual Computer* Getcomputer()    = 0;

protected:
    Computer* m_product;
};

class ComputerSBuilder : public ComputerBuilder {
public:
    ComputerSBuilder() {
        m_product = new Computer;
    }
    virtual void BuildDisplay() {
        m_product->SetDisplay("sss");
    }
    virtual void BuildMainFrame() {
        m_product->SetMainFrame("sss");
    }
    virtual void BuildKeyboard() {
        m_product->SetKeyboard("sss");
    }
    virtual Computer* Getcomputer() {
        return m_product;
    }
};

class Director {
public:
    Director(ComputerBuilder* builder) {
        m_builder = builder;
    }

    ~Director() {
        delete m_builder;
    }

    Computer* Construct() {
        m_builder->BuildDisplay();
        m_builder->BuildMainFrame();
        m_builder->BuildKeyboard();
        return m_builder->Getcomputer();
    }

private:
    ComputerBuilder* m_builder;
};

int main(int argc, char const* argv[]) {
    Director* d = new Director(new ComputerSBuilder);
    Computer* c = d->Construct();
    c->Work();

    delete c;
    delete d;
    return 0;
}