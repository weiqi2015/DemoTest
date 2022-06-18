#include <iostream>
#include <string>

class House {
public:
    void SetFoundation(std::string str) {}
    void SetContour(std::string str) {}
    void SetInterior(std::string str) {}

private:
    std::string m_foundation;  // 地基
    std::string m_contour;     // 轮廓
    std::string m_interior;    // 内饰
};

class HouseBuilder {
public:
    virtual bool   BuildPart1() = 0;
    virtual bool   BuildPart2() = 0;
    virtual bool   BuildPart3() = 0;
    virtual House* GetResult()  = 0;

protected:
    House* m_product;
};

class StoneHouseSBuilder : public HouseBuilder {
public:
    StoneHouseSBuilder() {
        m_product = new House;
    }
    virtual bool BuildPart1() {
        m_product->SetFoundation("Stone");
        return true;
    }
    virtual bool BuildPart2() {
        m_product->SetContour("Stone");
        return true;
    }
    virtual bool BuildPart3() {
        m_product->SetInterior("Stone");
        return true;
    }
    virtual House* GetResult() {
        return m_product;
    }
};

class WoodenHouseSBuilder : public HouseBuilder {
public:
    WoodenHouseSBuilder() {
        m_product = new House;
    }
    virtual bool BuildPart1() {
        m_product->SetFoundation("Wooden");
        return true;
    }
    virtual bool BuildPart2() {
        m_product->SetContour("Wooden");
        return true;
    }
    virtual bool BuildPart3() {
        m_product->SetInterior("Wooden");
        return true;
    }
    virtual House* GetResult() {
        return m_product;
    }
};

class Director {
public:
    Director(HouseBuilder* builder) {
        m_builder = builder;
    }

    ~Director() {
        delete m_builder;
    }

    // 建造者侧重点，导演指挥建造者生成
    House* Construct() {
        if (m_builder->BuildPart1())          // 有地基才能开始建轮廓
            if (m_builder->BuildPart2())      // 有轮廓才能开始装修
                if (m_builder->BuildPart3())  // 装修完才能提交房子
                {
                    std::cout << "建造成功，提交房子！" << std::endl;
                    return m_builder->GetResult();
                }

        std::cout << "建造失败！" << std::endl;
        return nullptr;
    }

private:
    HouseBuilder* m_builder;
};

int main(int argc, char const* argv[]) {
    Director* d = new Director(new WoodenHouseSBuilder);
    House*    h = d->Construct();

    delete h;
    delete d;

    return 0;
}