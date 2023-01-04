#pragma once

#include "Piece.h"
namespace model {
    class Pawn : public Piece {
    public:
        using Piece::Piece;
        std::pair<std::vector<Position>, bool> getValidMoves(ChessBoard& echiquier) const override;
        virtual void setPos(Position newPos) override;
        bool hasMovedTwoLastMove() const;
    private:
        bool canMoveTwo = true;
        bool movedTwoLastMove = false;
        bool canDoEnPassant(const Position& positionPossible, ChessBoard& chessBoard) const;
    };
}