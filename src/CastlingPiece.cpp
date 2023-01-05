#include "../Headers/CastlingPiece.h"
#include "../Headers/ChessBoard.h"

namespace model {
    using namespace::std;
    void CastlingPiece::setPos(Position newPos)
    {
        hasMoved = false;
        position_ = newPos;
    }
    bool CastlingPiece::canCastle() const
    {
        return hasMoved;
    }
}