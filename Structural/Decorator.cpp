#include <iostream>

// 形状类接口
class Shape {
public:
    virtual void Draw() = 0;
};

// 方形实现
class Rectangle : public Shape {
public:
    virtual void Draw() {
        std::cout << "Shape: Rectangle" << std::endl;
    }
};

// 圆形实现
class Circle : public Shape {
public:
    virtual void Draw() {
        std::cout << "Shape: Circle" << std::endl;
    }
};

// 形状装饰类接口
class ShapeDecorator : public Shape {
public:
    ShapeDecorator() = default;
    ShapeDecorator(Shape* dectoratedShape) {
        this->dectoratedShape = dectoratedShape;
    }
    virtual void Draw() {
        dectoratedShape->Draw();
    }

protected:
    Shape* dectoratedShape;
};

// 红色形状装饰类
class RedShapeDecorator : public ShapeDecorator {
public:
    RedShapeDecorator(Shape* dectoratedShape) {
        this->dectoratedShape = dectoratedShape;
    }

    virtual void Draw() {
        dectoratedShape->Draw();
        SetRedBorder(dectoratedShape);
    }

private:
    void SetRedBorder(Shape* dectoratedshape) {
        std::cout << "Border Color: Red" << std::endl;
    }

protected:
    Shape* dectoratedShape;
};

int main(int argc, char const* argv[]) {
    Shape* circle = new Circle;
    // 给圆形装饰成红色
    Shape* redCircle = new RedShapeDecorator(circle);
    // 红色圆形
    redCircle->Draw();

    delete redCircle;
    delete circle;

    return 0;
}
