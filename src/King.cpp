#include "../Headers/King.h"
#include "../Headers/ChessBoard.h"
#include "../Headers/Rook.h"

namespace model {
    using namespace::std;

    King::King(Position posInit, Color couleur, bool canCastle) :
        CastlingPiece::CastlingPiece(posInit, couleur)
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
        auto normalMovesInfo = getValidMovesNoCastle(chessBoard);

        vector<Position> validMoves = normalMovesInfo.first;
        bool isAttackingKing = normalMovesInfo.second;

        

        if (canCastle()) {
            std::pair<bool, bool> castleWayInfo = chessBoard.castleWayIsClear(color_);

            Position rookPosition = { position_.x + 3, position_.y };
            auto neighboringRook = dynamic_cast<Rook*>(chessBoard.getPiece(rookPosition).get());
            if (neighboringRook && neighboringRook->getColor() == color_ && neighboringRook->canCastle() && castleWayInfo.first) {
                validMoves.push_back({ rookPosition.x - 1, rookPosition.y });
            }

            rookPosition = { position_.x - 4, position_.y };
            neighboringRook = dynamic_cast<Rook*>(chessBoard.getPiece(rookPosition).get());
            if (neighboringRook && neighboringRook->getColor() == color_ && neighboringRook->canCastle() && castleWayInfo.second) {
                validMoves.push_back({ rookPosition.x + 1, rookPosition.y });
            }
        }
        return { validMoves, isAttackingKing};
    }

    std::pair<std::vector<Position>, bool> King::getValidMovesNoCastle(ChessBoard& chessBoard) const
    {   
        vector<Position> validMoves ;
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
                        isAttackingKing |= chessBoard.isEnemyKing(piece);
                        validMoves.push_back(posPossible);
                    }

                }
            }
        }
        return { validMoves, isAttackingKing };
    }


    
}