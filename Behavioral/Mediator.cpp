#include <algorithm>
#include <iostream>
#include <list>

class Colleague;

class Mediator {
public:
    virtual void Register(Colleague* col) = 0;
    virtual void Relay(Colleague* col)    = 0;
};

class Colleague {
public:
    virtual void Receive() = 0;
    virtual void Send()    = 0;

    void SetMedium(Mediator* mediator) {
        m_mediator = mediator;
    }

protected:
    Mediator* m_mediator;
};

class ConcreteColleague1 : public Colleague {
public:
    virtual void Receive() {
        std::cout << "同事1收到请求" << std::endl;
    }
    virtual void Send() {
        std::cout << "同事1发出请求" << std::endl;
        m_mediator->Relay(this);
    }
};

class ConcreteColleague2 : public Colleague {
public:
    virtual void Receive() {
        std::cout << "同事2收到请求" << std::endl;
    }
    virtual void Send() {
        std::cout << "同事2发出请求" << std::endl;
        m_mediator->Relay(this);
    }
};

class ConcreteMediator : public Mediator {
public:
    virtual void Register(Colleague* col) {
        auto it = find(m_cols.begin(), m_cols.end(), col);
        if (it == m_cols.end()) {
            m_cols.push_back(col);
            col->SetMedium(this);
        }
    }
    virtual void Relay(Colleague* col) {
        std::cout << "中介收到，开始转发。" << std::endl;
        for (auto&& i : m_cols) {
            if (i != col)
                i->Receive();
        }
    }

private:
    std::list<Colleague*> m_cols;
};

int main(int argc, char const* argv[]) {
    Mediator* m = new ConcreteMediator;

    Colleague* c1 = new ConcreteColleague1;
    Colleague* c2 = new ConcreteColleague2;

    m->Register(c1);
    m->Register(c2);

    c1->Send();

    c2->Send();

    return 0;
}