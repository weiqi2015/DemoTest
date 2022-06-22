#include <iostream>

// 事件模板，准备、开始、结束
class Template {
public:
    virtual void Init()  = 0;
    virtual void Start() = 0;
    virtual void End()   = 0;
    virtual void Execute() {
        Init();
        Start();
        End();
    }
};

class Cook : public Template {
public:
    virtual void Init() {
        std::cout << "准备食材和工具!" << std::endl;
    }

    virtual void Start() {
        std::cout << "开始煮菜！！" << std::endl;
    }

    virtual void End() {
        std::cout << "煮菜完成！！" << std::endl;
    }
};

class Sweep : public Template {
public:
    virtual void Init() {
        std::cout << "准备清理工具!" << std::endl;
    }

    virtual void Start() {
        std::cout << "开始打扫！！" << std::endl;
    }

    virtual void End() {
        std::cout << "打扫完成！！" << std::endl;
    }
};

int main(int argc, char const* argv[]) {
    Template* c = new Cook;
    c->Execute();

    Template* s = new Sweep;
    s->Execute();

    delete s;
    delete c;

    return 0;
}