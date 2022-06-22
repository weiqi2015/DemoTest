#include <iostream>
#include <list>
#include <string>

// 观察者
class Observer {
public:
    virtual void Update() = 0;
};

// 观察者1
class ConcreteObserver1 : public Observer {
public:
    virtual void Update() {
        std::cout << "具体观察者 1号 做出反应！" << std::endl;
    }
};

// 观察者2
class ConcreteObserver2 : public Observer {
public:
    virtual void Update() {
        std::cout << "具体观察者 2号 做出反应！" << std::endl;
    }
};

// 抽象目标
class Subject {
public:
    virtual void registerObserver(Observer* pObj) {
        m_observers.push_back(pObj);
    }

    virtual void removeObserver(Observer* pObj) {
        m_observers.remove(pObj);
    }

    virtual void noitfyObserver() {
        //逐个遍历调用Observer的update方法
        for (auto iter = m_observers.begin(); iter != m_observers.end(); iter++) {
            (*iter)->Update();
        }
    }

protected:
    std::list<Observer*> m_observers;
};

// 具体目标
class ConcreteSubject : public Subject {
public:
    void Change() {
        // 具体目标发送变化
        std::cout << "目标发生变化" << std::endl;

        noitfyObserver();
    }
};

int main(int argc, char const* argv[]) {
    ConcreteSubject*   sub  = new ConcreteSubject;
    ConcreteObserver1* obj1 = new ConcreteObserver1;
    ConcreteObserver2* obj2 = new ConcreteObserver2;

    sub->registerObserver(obj1);
    sub->registerObserver(obj2);

    // 目标发生变化，观察者会收到通知做出响应
    sub->Change();

    delete obj2;
    delete obj1;
    delete sub;

    return 0;
}