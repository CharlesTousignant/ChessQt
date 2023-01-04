#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()

#include <utility>
#include <vector>

#include <iostream>

#define maxKingInGame 2

namespace model {
    
    struct Position {
        unsigned x;
        unsigned y;

        bool operator==(Position other);

        bool isOnBoard() const;
    };

    unsigned posTo1D(const Position& pos);

    enum Color { white, black };
    void changeColor(Color& colorToChange);

    class ChessBoard;

    class Piece {
    public:
        Piece() = default;
        Piece(Position posInit, Color couleur);
        Piece& operator=(Piece& piece) = default;
        virtual ~Piece() = default;

        Position getPos() const;
        virtual void setPos(Position newPos);

        Color getColor() const;

        virtual std::pair<std::vector<Position>, bool> getValidMoves(ChessBoard& chessBoard) const = 0;

        
    protected:
        Position position_;
        Color color_;
    };
}