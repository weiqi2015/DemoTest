#include <iostream>
#include <string>

class AbstractServer {
public:
    virtual void Request() = 0;
};

// 真正的服务器
class RealServer : public AbstractServer {
public:
    void Request() {
        std::cout << "服务器启动" << std::endl;
    }
};

class ProxyServer : public AbstractServer {
public:
    ProxyServer() {
        // 保留服务器对象
        m_pServer = new RealServer;
    }

    void Request() {
        // 检测过程，比如检测通讯内容，IP地址等等
        std::cout << "检验通过" << std::endl;
        // 跟服务器请求
        m_pServer->Request();
    }

private:
    AbstractServer* m_pServer;
};

int main(void) {
    AbstractServer* pProxy = new ProxyServer();
    pProxy->Request();
    return 0;
}