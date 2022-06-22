#include <iostream>

class Visitor;

class Element {
public:
    virtual void accept(Visitor& visitor) = 0;  //第一次多态辨析

    virtual ~Element() {}
};

class ElementA : public Element {
public:
    void accept(Visitor& visitor) override {
        visitor.visitElementA(*this);
    }
};

class ElementB : public Element {
public:
    void accept(Visitor& visitor) override {
        visitor.visitElementB(*this);  //第二次多态辨析
    }
};

class Visitor {
public:
    virtual void visitElementA(ElementA& element) = 0;
    virtual void visitElementB(ElementB& element) = 0;

    virtual ~Visitor() {}
};

//==================================

// 访问1
class Visitor1 : public Visitor {
public:
    void visitElementA(ElementA& element) override {
        std::cout << "Visitor1 is processing ElementA" << std::endl;
    }

    void visitElementB(ElementB& element) override {
        std::cout << "Visitor1 is processing ElementB" << std::endl;
    }
};

// 访问2
class Visitor2 : public Visitor {
public:
    void visitElementA(ElementA& element) override {
        std::cout << "Visitor2 is processing ElementA" << std::endl;
    }

    void visitElementB(ElementB& element) override {
        std::cout << "Visitor2 is processing ElementB" << std::endl;
    }
};

int main() {
    // 根据被访问者的数据，做出对应的行为操作
    // 比如被访问者是 纸，访问者-出版社 会 生成书 或者 报纸等
    // 而如果访问者-银行，则会生产 纸币
    Visitor2 visitor;
    ElementB elementB;
    elementB.accept(visitor);  // double dispatch

    ElementA elementA;
    elementA.accept(visitor);

    return 0;
}