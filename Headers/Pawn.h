#pragma once

#include "Piece.h"
namespace model {
    class Pawn : public Piece {
    public:
        using Piece::Piece;
        std::pair<std::vector<Position>, bool> getValidMoves(ChessBoard& chessBoard) const override;
        std::vector<Position> getAttackingMoves(ChessBoard& echiquier) const;
        virtual void setPos(Position newPos) override;
        bool hasMovedTwoLastMove() const;
    private:
        bool canMoveTwo = true;
        bool movedTwoLastMove = false;
        bool canDoEnPassant(const Position& positionPossible, ChessBoard& chessBoard) const;
    };
}