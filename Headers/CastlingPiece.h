#pragma once

#include "Piece.h"
namespace model {
    class CastlingPiece : public Piece {
    public:
        using Piece::Piece;
        virtual void setPos(Position newPos) override;
        bool canCastle() const;
    private:
        bool hasMoved = false;
    };
}