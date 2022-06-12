#include <iostream>
#include <map>

// ===========================================
// 动态创建类

// 定义函数指针
typedef void* (*Constructor)();

// 工厂类，用于注册、保存和创建需要动态创建的类
class CObjectFactory {
public:
    static void RegisterClass(std::string className, Constructor constructor) {
        Constructors()[className] = constructor;
    }

    static void* CreateObject(std::string className) {
        Constructor constructor = nullptr;

        // 如果查看返回指针指向的不是结束指针为查找到
        if (Constructors().find(className) != Constructors().end()) {
            // 获取 map 的 value 值
            return Constructors().find(className)->second();
        }
        
        // if (constructor != nullptr) {
        //     return (*constructor)();
        // }
        
        return nullptr;
    }

private:
    inline static std::map<std::string, Constructor> &Constructors() {
        static std::map<std::string, Constructor> instance;
        return instance;
    }
};

// 定义宏，用于注册动态创建类
#define REG_CLASS(className)        \
class className##Helper             \
{                                   \
public:                             \
    className##Helper() {           \
        CObjectFactory::RegisterClass(#className, className##Helper::CreateObjFunc); \
    }                               \
    static void* CreateObjFunc() {  \
        return new className;       \
    }                               \
};                                  \
className##Helper className##helper;


// ===========================================


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

// 简单工厂-扩展-动态创建对象
// 优点：减轻工厂的责任，添加产品时不必修改工厂的逻辑代码，即原有程序基本不用改变。动态地创建任意产品，完全解耦。可实现配置化开发，从配置文件中读取字符串动态创建对象，特别容易维护和扩展。
class AutoFactory {
public:
    static Product* MakeProduct(std::string productName) {
        return static_cast<Product*>(CObjectFactory::CreateObject(productName));
    }
};

// 注册产品
REG_CLASS(ProductA)
REG_CLASS(ProductB)

//
int main(int argc, char const *argv[])
{
    Product* p = AutoFactory::MakeProduct("ProductB");
    if (p)
    {
        p->Info();
        delete p;
        p = nullptr;
    }

    return 0;
}
