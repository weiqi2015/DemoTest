#include <iostream>

// 布景
class System1 {
public:
    void Active() {
        std::cout << "布景完成" << std::endl;
    }
};

// 灯光效果
class System2 {
public:
    void Active() {
        std::cout << "灯光效果设置完成" << std::endl;
    }
};

// 构图
class System3 {
public:
    void Active() {
        std::cout << "构图完成" << std::endl;
    }
};

// 图片
class System4 {
public:
    void Active() {
        std::cout << "图片生成" << std::endl;
    }
};

class Facade {
public:
    bool Work() {
        // 外观接口实现具体复杂操作步骤，给调用者提供简单的接口
        // 调用者不需要知道细节
        System1* system1 = new System1;
        system1->Active();

        System2* system2 = new System2;
        system2->Active();

        System3* system3 = new System3;
        system3->Active();

        System4* system4 = new System4;
        system4->Active();

        std::cout << "拍照完成" << std::endl;

        delete system1;
        delete system2;
        delete system3;
        delete system4;

        // 返回结果
        return true;
    }
};

int main(int argc, char const* argv[]) {
    // 去找摄影团队拍照
    Facade facade;
    bool   bRet = facade.Work();
    if (bRet) {
        std::cout << "拿到照片" << std::endl;
    }

    return 0;
}