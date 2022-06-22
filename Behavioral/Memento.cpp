#include <iostream>
#include <list>
#include <string>

// 备忘录
class Memento {
public:
    Memento(std::string state) : m_state(state) {}
    void SetState(std::string state) {
        m_state = state;
    }

    std::string GetState() {
        return m_state;
    }

private:
    std::string m_state;
};

// 发起人
class Originator {
public:
    Originator(/* args */) {}
    ~Originator() {}
    void SetState(std::string state) {
        m_state = state;
    }

    std::string GetState() {
        return m_state;
    }

    Memento* CreateMemento() {
        return new Memento(m_state);
    }

    void RestoreMemento(Memento* m) {
        SetState(m->GetState());
    }

private:
    std::string m_state;
};

// 管理者
class Caretaker {
public:
    Caretaker(Memento* m = nullptr) : m_memento(m) {}
    ~Caretaker() {
        if (m_memento != nullptr) {
            delete m_memento;
            m_memento = nullptr;
        }
    }

    void SetMemento(Memento* m) {
        if (m_memento != nullptr) {
            delete m_memento;
            m_memento = nullptr;
        }

        m_memento = m;
    }

    Memento* GetMemento() {
        return m_memento;
    }

private:
    Memento* m_memento;
};

int main(int argc, char const* argv[]) {
    Originator* o = new Originator();
    Caretaker*  c = new Caretaker;
    o->SetState("S0");
    std::cout << "初始状态：" << o->GetState() << std::endl;
    // 发起人保存管理者当前状态
    c->SetMemento(o->CreateMemento());
    o->SetState("S1");
    std::cout << "新状态：" << o->GetState() << std::endl;
    // 管理者恢复发起人记录的状态
    o->RestoreMemento(c->GetMemento());
    std::cout << "恢复状态：" << o->GetState() << std::endl;
    return 0;
}