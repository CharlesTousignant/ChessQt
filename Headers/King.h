#pragma once

#include "CastlingPiece.h"
namespace model {
    class King : public CastlingPiece {
    public:

        King(Position posInit, Color couleur);
        ~King();
        std::pair<std::vector<Position>, bool> getValidMoves(ChessBoard& echiquier) const override;

        inline static unsigned countRoi_ = 0;
    };
}