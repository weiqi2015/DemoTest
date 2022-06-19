#include <iostream>

class Color {
public:
    virtual void Fill() = 0;
};

class RedColor : public Color {
public:
    virtual void Fill() {
        std::cout << "填上红色" << std::endl;
    }
};

class Shape {
    virtual void Draw() = 0;

public:
    Color* m_color;
};

class Circle : public Shape {
public:
    Circle(Color* color) {
        this->m_color = color;
    }
    virtual void Draw() {
        std::cout << "画圆形" << std::endl;
        m_color->Fill();
    }
};

int main(int argc, char const* argv[]) {
    Color*  red    = new RedColor;
    Circle* circle = new Circle(red);
    circle->Draw();

    delete circle;
    delete red;
    return 0;
}
