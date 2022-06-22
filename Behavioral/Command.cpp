#include <iostream>
#include <list>

// 命令行为接口
class Command {
public:
    virtual void Execute() = 0;
};

// 接收者
class Receiver {
public:
    void Action() {
        std::cout << "开始执行！" << std::endl;
    }
};

// 命令1
class ConcreteCommand : public Command {
public:
    ConcreteCommand(Receiver* receiver) {
        m_receiver = receiver;
    }

    virtual void Execute() {
        std::cout << "请开始你的表演！" << std::endl;
        m_receiver->Action();
    }

private:
    Receiver* m_receiver;
};

// 请求者
class Invoker {
public:
    void AddCommand(Command* c) {
        m_commands.push_back(c);
    }

    void Execute() {
        for (auto it = m_commands.begin(); it != m_commands.end(); it++) {
            (*it)->Execute();
        }
        m_commands.clear();
    }

private:
    std::list<Command*> m_commands;
};

int main(int argc, char const* argv[]) {
    Receiver* rec = new Receiver;
    Command*  com = new ConcreteCommand(rec);
    Invoker*  inv = new Invoker;
    inv->AddCommand(com);
    inv->Execute();

    delete inv;
    delete com;
    delete rec;

    return 0;
}