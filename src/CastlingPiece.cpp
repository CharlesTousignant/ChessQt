#include "../Headers/CastlingPiece.h"
#include "../Headers/ChessBoard.h"

namespace model {
    using namespace::std;
    void CastlingPiece::setPos(Position newPos)
    {   
        Piece::setPos(newPos);
        hasMoved = true;
    }
    bool CastlingPiece::canCastle() const
    {
        return !hasMoved;
    }
}