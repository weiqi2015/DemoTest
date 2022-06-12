#include <iostream>

// 产品基类
// 产品成产
class Product {
public:
    virtual void Info(void) = 0;
protected:
    Product(){}
};

// A产品
class ProductA : public Product {
public:
    void Info(void) {
        std::cout << "ProjectA!" << std::endl;
    }
};

// B产品
class ProductB : public Product {
public:
    void Info(void) {
        std::cout << "ProjectB!" << std::endl;
    }
};

// 简单工厂
// 根据类型值生产不同的产品
// 优点：将产品封装，后续增加产品，只需要新建一个新的类继承基类，不需要修改原有产品代码；
// 缺点：增加新的产品，需要修改简单工厂类，需要增加判断生产新的产品代码，破坏原有的代码。
// 封闭原则：不符合
class SimpleFactory {
public:
    static Product* MakeProduct(int nType) {
        Product* p = nullptr;

        if (nType == 0)
            p = new ProductA;
        else if (nType == 1)
            p = new ProductB;
        else
            p = new ProductA;
        
        return p;
    }
};

//
int main(int argc, char const *argv[])
{
    Product* p = SimpleFactory::MakeProduct(1);
    if (p)
    {
        p->Info();
        delete p;
        p = nullptr;
    }
    
    p = SimpleFactory::MakeProduct(0);
    if (p)
    {
        p->Info();
        delete p;
    }

    return 0;
}
