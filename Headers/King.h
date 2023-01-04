#pragma once

#include "Piece.h"
namespace model {
    class King : public Piece {
    public:

        King(Position posInit, Color couleur);
        ~King();
        std::pair<std::vector<Position>, bool> getValidMoves(ChessBoard& echiquier) const override;

        inline static unsigned countRoi_ = 0;
    };
}