#include "../Headers/Rook.h"
#include "../Headers/ChessBoard.h"

namespace model {
    using namespace::std;
    pair<vector<Position>, bool> Rook::getValidMoves(ChessBoard& chessBoard) const{
        vector<Position> validMoves;
        bool isAttackingKing = false;
        Position posPossible;

        for (unsigned i = 1; (position_.x - i) >= 1; ++i) {
            posPossible = { (position_.x - i), position_.y };
            auto piece = chessBoard.getPiece(posPossible).get();

            // La tour ne peut pas se deplacer sur une case qui a deja une piece de la meme couleur et sera bloquee pour le reste de la ligne
            if (!piece) {
                // On ajoute le mouvement au vecteur
                validMoves.push_back(posPossible);
                continue;
            }
            else if (piece->getColor() == color_)
                break;
            else {
                // On verifie si la piece enemie est un roi, et on ajoute le mouvement au vecteur
                isAttackingKing |= isEnemyKing(piece);
                validMoves.push_back(posPossible);
                // On arrete cette case, car tout les prochaines position seraient bloquee par la piece trouvee ici
                break;
            }
        }

        for (unsigned i = 1; (position_.x + i) <= 8; ++i) {
            posPossible = { (position_.x + i), position_.y };
            auto piece = chessBoard.getPiece(posPossible).get();

            // La tour ne peut pas se deplacer sur une case qui a deja une piece de la meme couleur et sera bloquee pour le reste de la ligne
            if (!piece) {
                // On ajoute le mouvement au vecteur
                validMoves.push_back(posPossible);
                continue;
            }
            else if (piece->getColor() == color_)
                break;
            else {
                // On verifie si la piece enemie est un roi, et on ajoute le mouvement au vecteur
                isAttackingKing |= isEnemyKing(piece);
                validMoves.push_back(posPossible);
                // On arrete cette case, car tout les prochaines position seraient bloquee par la piece trouvee ici
                break;
            }
        }

        for (unsigned i = 1; (position_.y - i) >= 1; ++i) {
            posPossible = { position_.x, (position_.y - i) };
            auto piece = chessBoard.getPiece(posPossible).get();


            if (!piece) {
                // On ajoute le mouvement au vecteur
                validMoves.push_back(posPossible);
                continue;
            }

            // La tour ne peut pas se deplacer sur une case qui a deja une piece de la meme couleur et sera bloquee pour le reste de la ligne
            else if (piece->getColor() == color_)
                break;
            else {
                // On verifie si la piece enemie est un roi, et on ajoute le mouvement au vecteur
                isAttackingKing |= isEnemyKing(piece);
                validMoves.push_back(posPossible);
                // On arrete cette ligne, car tout les prochaines position seraient bloquee par la piece trouvee ici
                break;
            }
        }

        for (unsigned i = 1; (position_.y + i) <= 8; ++i) {
            posPossible = { position_.x, (position_.y + i) };
            auto piece = chessBoard.getPiece(posPossible).get();


            if (!piece) {
                // On ajoute le mouvement au vecteur
                validMoves.push_back(posPossible);
                continue;
            }

            // La tour ne peut pas se deplacer sur une case qui a deja une piece de la meme couleur et sera bloquee pour le reste de la ligne
            else if (piece->getColor() == color_)
                break;
            else {
                // On verifie si la piece enemie est un roi, et on ajoute le mouvement au vecteur
                isAttackingKing |= isEnemyKing(piece);
                validMoves.push_back(posPossible);
                // On arrete cette ligne, car tout les prochaines position seraient bloquee par la piece trouvee ici
                break;
            }
        }
        return { validMoves, isAttackingKing };
    }
}