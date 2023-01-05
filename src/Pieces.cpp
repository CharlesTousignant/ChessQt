#include <stdio.h>
#include <iostream>
#include <algorithm>

#include "../Headers/Piece.h"
#include "../Headers/King.h"

namespace model {
    using namespace::std;

    bool Position::operator==(Position other) {
        return(x == other.x && y == other.y);
    }

    bool Position::isOnBoard() const {
        if (1 <= x && x <= 8 && 1 <= y && y <= 8)
            return true;
        else
            return false;
    }

    inline Position Position::right() const
    {
        return {x + 1, y};
    }

    inline Position Position::left() const
    {
        return { x - 1, y };
    }

    inline Position Position::up() const
    {
        return { x, y + 1 };
    }

    inline Position Position::down() const
    {
        return { x, y - 1 };
    }

    unsigned posTo1D(const Position& pos) {
        return (pos.x - 1) + ((pos.y - 1) * 8);
    }

    Piece::Piece(Position posInit, Color color) {
        position_ = posInit;
        color_ = color;
    }

    void changeColor(Color& colorToChange) {
        if (colorToChange == white)
            colorToChange = black;
        else
            colorToChange = white;
    }

    Position Piece::getPos() const { return position_; }

    void Piece::setPos(Position newPos) { position_ = newPos; }

    Color Piece::getColor() const {
        return color_;
    }
}
