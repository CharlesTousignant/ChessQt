#pragma once

#include "CastlingPiece.h"
namespace model {
    class Rook : public CastlingPiece {
    public:
        using CastlingPiece::CastlingPiece;
        std::pair<std::vector<Position>, bool> getValidMoves(ChessBoard& echiquier) const override;
    };
}