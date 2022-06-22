#include <iostream>
#include <vector>

// 指针接口
template <typename T>
class Iterator {
public:
    virtual void first()        = 0;
    virtual void next()         = 0;
    virtual bool isDone() const = 0;
    virtual T&   current()      = 0;
};

// 容器接口
template <typename T>
class Collection {
public:
    virtual void         PushData(T item)      = 0;
    virtual Iterator<T>* CreateIterator()      = 0;
    virtual T&           operator[](int index) = 0;
    virtual int          GetSize()             = 0;
};

// 实体指针
template <typename T>
class ConcreteIterator : public Iterator<T> {
public:
    ConcreteIterator(Collection<T>* c) : m_c(c), m_cur(0) {}

    virtual void first() override {
        m_cur = 0;
    }
    virtual void next() override {
        if (m_cur < m_c->GetSize()) {
            m_cur++;
        }
    }
    virtual bool isDone() const override {
        return m_cur >= m_c->GetSize();
    }
    virtual T& current() override {
        if (m_cur >= m_c->GetSize()) {
            m_cur = m_c->GetSize() - 1;
        }

        return (*m_c)[m_cur];
    }

private:
    Collection<T>* m_c;
    int            m_cur;
};

// 实体容器
template <typename T>
class ConcreteCollection : public Collection<T> {
public:
    virtual void PushData(T item) {
        m_data.push_back(item);
    }

    virtual Iterator<T>* CreateIterator() {
        return new ConcreteIterator<T>(this);
    }

    virtual T& operator[](int index) {
        return m_data[index];
    }

    virtual int GetSize() {
        return m_data.size();
    }

protected:
    std::vector<T> m_data;
};

int main(int argc, char const* argv[]) {
    // 创建容器
    Collection<int>* cs = new ConcreteCollection<int>();

    // 填入数据
    cs->PushData(100);
    cs->PushData(60);
    cs->PushData(8);

    // 获取容器迭代器
    Iterator<int>* iter = cs->CreateIterator();

    // 通过迭代器遍历容器
    for (iter->first(); !iter->isDone(); iter->next()) {
        std::cout << iter->current() << std::endl;
    }

    return 0;
}