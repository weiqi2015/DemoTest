#include <iostream>
#include <string>
#include <vector>
using namespace std;

//棋子的颜色
enum PieceColor { BLACK, WHITE };
//棋子的位置
struct PiecePos {
    int m_x;
    int m_y;
    PiecePos(int a, int b) : m_x(a), m_y(b) {}
};

class Piece {
public:
    Piece(PieceColor color) : m_color(color) {}
    ~Piece() {}
    virtual void draw() {}

protected:
    PieceColor m_color;
};

class BlackPiece : public Piece {
public:
    BlackPiece(PieceColor color) : Piece(color) {}
    ~BlackPiece() {}
    void draw() {
        cout << "绘制一个黑棋 " << endl;
    }
};
class WhitePiece : public Piece {
public:
    WhitePiece(PieceColor color) : Piece(color) {}
    ~WhitePiece() {}
    void draw() {
        cout << "绘制一个白棋 " << endl;
    }
};

class PieceBoard {
public:
    PieceBoard(string black, string white) : m_blackName(black), m_WhiteName(white) {
        m_pBlackPiece = nullptr;
        m_pWhitePiece = nullptr;
    }

    ~PieceBoard() {
        clear();
    }

    void setPiece(PieceColor color, PiecePos pos) {
        if (color == BLACK) {
            if (m_pBlackPiece == nullptr)
                m_pBlackPiece = new BlackPiece(color);

            cout << m_blackName << "在" << pos.m_x << "," << pos.m_y << "下了一步" << endl;

            m_pBlackPiece->draw();
        } else {
            if (m_pWhitePiece == nullptr)
                m_pWhitePiece = new WhitePiece(color);

            cout << m_WhiteName << "在" << pos.m_x << "," << pos.m_y << "下了一步" << endl;

            m_pWhitePiece->draw();
        }

        m_vecPiece.push_back(pos);
    }

    void clear() {
        if (m_pBlackPiece)
            delete m_pBlackPiece;
        if (m_pWhitePiece)
            delete m_pWhitePiece;
    }

private:
    vector<PiecePos> m_vecPiece;  // 棋盘上的棋子
    string           m_blackName;
    string           m_WhiteName;
    Piece*           m_pBlackPiece;
    Piece*           m_pWhitePiece;
};

int main(void) {
    PieceBoard pieceBoard("black", "white");
    pieceBoard.setPiece(BLACK, PiecePos(1, 1));
    pieceBoard.setPiece(WHITE, PiecePos(2, 2));

    return 0;
}