#include <iostream>

class Reqest {
public:
    Reqest(int level) {
        m_level = level;
    }
    ~Reqest() {}

    int GetLevel() const {
        return m_level;
    }

private:
    int m_level;
};

class Handler {
public:
    Handler(/* args */) {}
    ~Handler() {}

    void SetNextChain(Handler* next) {
        m_next = next;
    }

    void Execute(const Reqest& req) {
        if (CanHandleRequest(req)) {
            ProcessRequest(req);
        } else {
            SendRequestToNextHandler(req);
        }
    }

protected:
    virtual bool CanHandleRequest(const Reqest& req) = 0;
    virtual void ProcessRequest(const Reqest& req)   = 0;

private:
    void SendRequestToNextHandler(const Reqest& req) {
        if (m_next != nullptr) {
            m_next->Execute(req);
        }
    }

private:
    Handler* m_next;
};

// 处理 1级及以下的请求
class Handler1 : public Handler {
    virtual bool CanHandleRequest(const Reqest& req) {
        if (req.GetLevel() <= 1)
            return true;
        return false;
    }

    virtual void ProcessRequest(const Reqest& req) {
        std::cout << "Handler1 处理完成！" << std::endl;
    }
};

// 处理 2级及以下的请求
class Handler2 : public Handler {
    virtual bool CanHandleRequest(const Reqest& req) {
        if (req.GetLevel() <= 2)
            return true;
        return false;
    }
    virtual void ProcessRequest(const Reqest& req) {
        std::cout << "Handler2 处理完成！" << std::endl;
    }
};

int main(int argc, char const* argv[]) {
    Reqest req(2);

    Handler1 h1;
    Handler2 h2;
    h1.SetNextChain(&h2);

    h1.Execute(req);

    return 0;
}