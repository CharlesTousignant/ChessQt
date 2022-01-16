#pragma once

#include "Piece.h"

namespace model {
    class Knight : public Piece {
    public:
        using Piece::Piece;
        std::pair<std::vector<Position>, bool> getValidMoves(ChessBoard& echiquier) override;
    };
}