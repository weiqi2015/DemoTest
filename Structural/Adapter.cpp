#include <iostream>
#include <string>

// 目标接口（新接口）
class Target {
public:
    void newfunc() {
        std::cout << "目标接口调用" << std::endl;
    }
};

// 遗留接口（老接口）
class Adaptee {
public:
    void oldfunc() {
        std::cout << "遗留接口调用" << std::endl;
    }
};

//对象适配器
class Adapter : public Target {  //继承

public:
    Adapter(Adaptee* pAdaptee) {
        this->pAdaptee = pAdaptee;
    }

    void newfunc() {
        std::cout << "适配器 新接口调用" << std::endl;
        pAdaptee->oldfunc();
    }

protected:
    Adaptee* pAdaptee;  //组合
};

int main(int argc, char const* argv[]) {
    Adaptee* old     = new Adaptee;
    Adapter* adapter = new Adapter(old);
    adapter->newfunc();

    delete adapter;
    delete old;

    return 0;
}
