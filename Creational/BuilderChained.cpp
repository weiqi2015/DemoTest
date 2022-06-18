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
    virtual HouseBuilder* BuildPart1(std::string str) = 0;
    virtual HouseBuilder* BuildPart2(std::string str) = 0;
    virtual HouseBuilder* BuildPart3(std::string str) = 0;
    virtual House*        GetResult()                 = 0;

protected:
    House* m_product;
};

class HouseSBuilder : public HouseBuilder {
public:
    HouseSBuilder() {}

    virtual HouseBuilder* BuildPart1(std::string str) {
        m_foundation = str;
        return this;
    }

    virtual HouseBuilder* BuildPart2(std::string str) {
        m_contour = str;
        return this;
    }

    virtual HouseBuilder* BuildPart3(std::string str) {
        m_interior = str;
        return this;
    }

    virtual House* GetResult() {
        // 生成过程
        House* h    = nullptr;
        bool   flag = false;

        if (!m_foundation.empty()) {
            h = new House;
            h->SetFoundation(m_foundation);

            if (!m_contour.empty()) {
                h->SetContour(m_contour);

                if (!m_interior.empty()) {
                    h->SetInterior(m_interior);
                    flag = true;

                    std::cout << "建造成功，提交房子！" << std::endl;
                }
            }
        }

        if (!flag) {
            std::cout << "建造失败！" << std::endl;
            if (h) {
                delete h;
                h = nullptr;
            }
        }

        return h;
    }

private:
    std::string m_foundation;  // 地基
    std::string m_contour;     // 轮廓
    std::string m_interior;    // 内饰
};

int main(int argc, char const* argv[]) {
    HouseBuilder* builder = new HouseSBuilder;

    House* c = builder->BuildPart1("A")->BuildPart2("B")->BuildPart3("C")->GetResult();

    if (c) {
        delete c;
    }

    return 0;
}