#include "../Headers/Pawn.h"
#include "../Headers/ChessBoard.h"

namespace model {
    using namespace::std;
    pair<vector<Position>, bool> Pawn::getValidMoves(ChessBoard& chessBoard) const {
        vector<Position> validMoves;
        bool isAttackingKing = false;
        Position posPossible;

        // Move forward
        posPossible = { position_.x, position_.y + (color_ == white ? 1 : -1) };
        auto piece = chessBoard.getPiece(posPossible).get();
        if (!piece) {
            // On ajoute le mouvement au vecteur
            validMoves.push_back(posPossible);
            if (canMoveTwo) {
                posPossible = { position_.x, position_.y + (color_ == white ? 2 : -2) };
                piece = chessBoard.getPiece(posPossible).get();
                if (!piece) {
                    validMoves.push_back(posPossible);
                }
            }
        }

        // Attack sideways
        posPossible = { position_.x + 1, position_.y + (color_ == white ? 1 : -1) };
        piece = chessBoard.getPiece(posPossible).get();
        if (piece && piece->getColor() != color_ || ) {
            // On ajoute le mouvement au vecteur
            validMoves.push_back(posPossible);
        }
        posPossible = { position_.x - 1, position_.y + (color_ == white ? 1 : -1) };
        piece = chessBoard.getPiece(posPossible).get();
        if (piece && piece->getColor() != color_) {
            // On ajoute le mouvement au vecteur
            validMoves.push_back(posPossible);
        }

        return { validMoves, isAttackingKing };
    }
    void Pawn::setPos(Position newPos)
    {
        auto yChange = newPos.y - position_.y;
        if (yChange == 2 || yChange == -2) {
            movedTwoLastMove = true;
            canMoveTwo = false;
        }
        position_ = newPos;
    }
    bool Pawn::hasMovedTwoLastMove() const
    {
        return movedTwoLastMove;
    }
    bool Pawn::canDoEnPassant(const Position& positionPossible, ChessBoard& chessBoard) const
    {
        Position posCheckEnemyPawn = { positionPossible.x, positionPossible.y + (color_ == white ? -1 : +1) };
        auto piece = chessBoard.getPiece(posCheckEnemyPawn).get();
        auto pawn = dynamic_cast<Pawn*>(piece);
        return (pawn && piece->getColor() != color_ && pawn->hasMovedTwoLastMove());
    }
}