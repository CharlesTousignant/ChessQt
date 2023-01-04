#include "../Headers/King.h"
#include "../Headers/ChessBoard.h"

namespace model {
    using namespace::std;

    King::King(Position posInit, Color couleur) :
        Piece::Piece(posInit, couleur)
    {
        if (countRoi_ < maxKingInGame) {
            ++countRoi_;
        }
        else {
            throw logic_error("Two kings are already in play.");
        }
    }

    King::~King() {
        --countRoi_;
    }

    std::pair<vector<Position>, bool> King::getValidMoves(ChessBoard& chessBoard) const {
        vector<Position> validMoves;
        bool isAttackingKing = false;

        Position posPossible;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == 1 && j == 1)
                    continue;

                posPossible.x = (position_.x - 1) + i;
                posPossible.y = (position_.y - 1) + j;

                if (posPossible.isOnBoard()) {
                    auto piece = chessBoard.getPiece(posPossible).get();

                    if (!piece) {
                        // On ajoute le mouvement au vecteur
                        validMoves.push_back(posPossible);
                        continue;
                    }

                    else if (piece->getColor() == color_)
                        continue;

                    else {
                        // On verifie si la piece enemie est un roi, et on ajoute le mouvement au vecteur
                        isAttackingKing |= isEnemyKing(piece);
                        validMoves.push_back(posPossible);
                    }

                }
            }
        }
        return { validMoves, isAttackingKing };
    }
}