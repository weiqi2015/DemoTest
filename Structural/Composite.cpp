#include <algorithm>
#include <iostream>
#include <list>
#include <string>

class Component {
public:
    virtual void process() = 0;
    virtual ~Component() {}
};

//树节点
class Composite : public Component {
    std::string           name;
    std::list<Component*> elements;

public:
    Composite(const std::string& s) : name(s) {}

    void add(Component* element) {
        elements.push_back(element);
    }
    void remove(Component* element) {
        elements.remove(element);
    }

    void process() {
        std::cout << "树叉：" << name << std::endl;

        for (auto& e : elements)
            e->process();  //多态调用
    }
};

// 叶子节点
class Leaf : public Component {
    std::string name;

public:
    Leaf(std::string s) : name(s) {}

    void process() {
        std::cout << "树叶：" << name << std::endl;
    }
};

//              root
//             /    \
//          leaf1   treenode1
//                  /       \
//                leaf2     leaf3
int main(int argc, char const* argv[]) {
    Composite root("root");
    Composite treeNode1("treeNode1");
    Leaf      leaf1("left1");
    Leaf      leaf2("left2");
    Leaf      leaf3("left3");

    root.add(&leaf1);
    root.add(&treeNode1);

    treeNode1.add(&leaf2);
    treeNode1.add(&leaf3);

    root.process();

    return 0;
}
