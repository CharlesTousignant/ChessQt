#include "../Headers/Knight.h"
#include "../Headers/ChessBoard.h"

namespace model{
    using namespace::std;

    pair<vector<Position>, bool> Knight::getValidMoves(ChessBoard& chessBoard) const {
        vector<Position> validMoves;
        bool isAttackingKing = false;

        Position posPossible;  // position that will be added to the vector 

        int deplacementsPossiblesX[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
        int deplacementsPossiblesY[] = { 1, -1, 1, -1, 2, -2, 2, -2 };


        for (unsigned i = 0; i < 8; ++i) {
            posPossible = { position_.x + deplacementsPossiblesX[i],
                           position_.y + deplacementsPossiblesY[i] };
            if (posPossible.isOnBoard()) {

                auto piece = chessBoard.getPiece(posPossible).get();
                if (piece) {
                    if (piece->getColor() == color_)
                        continue;
                    isAttackingKing |= isEnemyKing(piece);
                    validMoves.push_back(posPossible);
                }

                else {
                    validMoves.push_back(posPossible);
                }
            }
        }

        return { validMoves, isAttackingKing };
    }
}