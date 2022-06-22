#include <iostream>

class State {
public:
    virtual void Action() = 0;
};

class HappyState : public State {
public:
    virtual void Action() {
        std::cout << "嘴角往上翘，很开心。" << std::endl;
    }
};

class SadState : public State {
public:
    virtual void Action() {
        std::cout << "嘴角往下翘，流眼泪。" << std::endl;
    }
};

class Context {
public:
    Context() : m_state(nullptr) {}
    ~Context() {
        if (m_state != nullptr) {
            delete m_state;
            m_state = nullptr;
        }
    }

    void SetState(State* state) {
        m_state = state;
    }
    State* GetState(State* state) {
        return m_state;
    }
    void Score(int score) {
        if (m_state != nullptr) {
            delete m_state;
            m_state = nullptr;
        }

        if (score >= 60) {
            SetState(new HappyState);
        } else {
            SetState(new SadState);
        }

        m_state->Action();
    }

private:
    State* m_state;
};
int main(int argc, char const* argv[]) {
    Context con;
    std::cout << "语文：100" << std::endl;
    con.Score(100);
    std::cout << "数学：59" << std::endl;
    con.Score(59);

    return 0;
}