#include <iostream>
#include <string>

class computer {
public:
    void SetMemory(int size) {
        m_memory = size;
    };

    void SetDisk(int size) {
        m_disk = size;
    }

    // 如果类很复杂有指针的情况下，需要在接口中实现深拷贝
    computer* Clone() {
        return new computer;
    }

private:
    int         m_memory = 16;       // 内存
    int         m_disk   = 500;      // 硬盘
    std::string m_other  = "other";  // 其它配件
};

int main(int argc, char const* argv[]) {
    // 联系工厂C
    computer* c = new computer;

    // 标配
    computer* standard = c->Clone();

    // 低配
    computer* low = c->Clone();
    low->SetMemory(8);
    low->SetDisk(250);

    // 高配
    computer* high = c->Clone();
    high->SetMemory(32);
    low->SetDisk(1000);

    delete high;
    delete low;
    delete standard;
    delete c;

    return 0;
}