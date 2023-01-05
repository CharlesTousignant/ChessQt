#pragma once

#include "CastlingPiece.h"
namespace model {
    class King : public CastlingPiece {
    public:

        King(Position posInit, Color couleur, bool canCastle = false);
        ~King();
        std::pair<std::vector<Position>, bool> getValidMoves(ChessBoard& chessBoard) const override;
        std::pair<std::vector<Position>, bool> getValidMovesNoCastle(ChessBoard& chessBoard) const;
        inline static unsigned countRoi_ = 0;
    };
}