#include "../Headers/King.h"
#include "../Headers/Rook.h"
#include "../Headers/Knight.h"
#include "../Headers/ChessBoard.h"
#include "../Headers/Bishop.h"
#include "../Headers/Pawn.h"
#include "../Headers/Queen.h"

namespace model {
    using namespace::std;

    ChessBoard::ChessBoard() {
        piecesVect_.resize(64);
        colorToPlay_ = Color::white;
        posPawnToPromote_ = {0, 0};
    }

    void ChessBoard::addPiece(std::string type, Color color, Position posPiece) {
        if (posPiece.isOnBoard()) {
            unsigned indexPos = posTo1D(posPiece);
            if (type == "king") {
                piecesVect_[indexPos] = make_shared<King>(posPiece, color);
            }

            else if (type == "rook") {
                piecesVect_[indexPos] = make_shared<Rook>(posPiece, color);
            }

            else if (type == "knight") {
                piecesVect_[indexPos] = make_shared<Knight>(posPiece, color);
            }

            else if (type == "bishop") {
                piecesVect_[indexPos] = make_shared<Bishop>(posPiece, color);
            }

            else if (type == "pawn") {
                piecesVect_[indexPos] = make_shared<Pawn>(posPiece, color);
            }

            else if (type == "queen") {
                piecesVect_[indexPos] = make_shared<Queen>(posPiece, color);
            }

            ChessBoard::shouldUpdate();
        }
        else
            cout << "Placing a piece outside the chessboard is impossible." << endl;
    }

    void ChessBoard::addPiecePawnPromotion(std::string type) {
        addPiece(type, (colorToPlay_ == Color::white) ? Color::black : Color::white, posPawnToPromote_);
    }

    shared_ptr<Piece>& ChessBoard::getPiece(Position posPiece) {
        unsigned indexPos = posTo1D(posPiece);
        return piecesVect_[indexPos];
    }

    bool ChessBoard::kingToPlayIsInCheck() {
        for (auto& piece : piecesVect_) {
            // On verifie si on a trouvee une piece. Ensuite on regarde si elle peut attacker le roi enemi
            if (piece && piece->getColor() != colorToPlay_ && piece->getValidMoves(*this).second) {
                return true;
            }
        }

        return false;
    }

    std::pair<bool, bool> ChessBoard::castleWayIsClear(Color color)
    {
        bool rightIsClear, leftIsClear = true;
        Position posKingToPlay = (color == Color::white) ? Position(5, 1) : Position(5, 8);
        rightIsClear = !(getPiece({ posKingToPlay.x + 1, posKingToPlay.y }).get() || getPiece({ posKingToPlay.x + 2, posKingToPlay.y }).get());
        leftIsClear = !(getPiece({ posKingToPlay.x - 1, posKingToPlay.y }).get() || getPiece({ posKingToPlay.x - 2, posKingToPlay.y }).get() || getPiece({ posKingToPlay.x - 3, posKingToPlay.y }).get());

        if (!(rightIsClear || leftIsClear)) {
            return { leftIsClear, rightIsClear };
        }

        std::vector<Position> enemyAttackMoves;
        for (auto& piece : piecesVect_) {
            if (!piece || piece->getColor() == color)
                continue;

            std::vector<Position> currEnemyMoves;
            auto pawnCast = dynamic_cast<Pawn*>(piece.get());
            if (pawnCast)
                currEnemyMoves = pawnCast->getAttackingMoves(*this);
            else {
                auto kingCast = dynamic_cast<King*>(piece.get());
                if (kingCast)
                    currEnemyMoves = kingCast->getValidMovesNoCastle(*this).first;
                else
                    currEnemyMoves = piece->getValidMoves(*this).first;
            }
            enemyAttackMoves.insert(enemyAttackMoves.begin(), currEnemyMoves.begin(), currEnemyMoves.end());
        }

        Position enemyMoveToCheck;
        Position rightMovesToCheck[3] = {
            {posKingToPlay.x + 1, posKingToPlay.y},
            {posKingToPlay.x + 2, posKingToPlay.y},
            {posKingToPlay.x + 3, posKingToPlay.y},
        };

        Position leftMovesToCheck[4] = {
            {posKingToPlay.x - 1, posKingToPlay.y},
            {posKingToPlay.x - 2, posKingToPlay.y},
            {posKingToPlay.x - 3, posKingToPlay.y},
            {posKingToPlay.x - 4, posKingToPlay.y}
        };
        do {
            enemyMoveToCheck = enemyAttackMoves.back();
            enemyAttackMoves.pop_back();
            if (enemyMoveToCheck == posKingToPlay) {
                return { false, false };
            }
            if (rightIsClear) {
                for (const auto& move : rightMovesToCheck) {
                    if (enemyMoveToCheck == move) {
                        rightIsClear = false;
                        break;
                    }
                }
            }
            if (leftIsClear) {
                for (const auto& move : leftMovesToCheck) {
                    if (enemyMoveToCheck == move) {
                        leftIsClear = false;
                        break;
                    }
                }
            }
        } while ((rightIsClear || leftIsClear) && !enemyAttackMoves.empty());

        return { rightIsClear, leftIsClear };
    }

    std::vector<Position> ChessBoard::getMovesPiece(Position posPiece)
    {
        if (!posPiece.isOnBoard()) {
            return std::vector<Position>();
        }

        Piece* piece = getPiece(posPiece).get();
        if (piece) {
            return piece->getValidMoves(*this).first;
        }
    }

    bool ChessBoard::kingToPlayIsCheckMated() {
        for (auto& piece : piecesVect_) {
            if (!piece || piece->getColor() != colorToPlay_) {
                continue;
            }
            auto possibleMoves = piece->getValidMoves(*this).first;
            if (!possibleMoves.empty()) {
                for (const auto& move : possibleMoves) {
                    if (moveIsValid(piece->getPos(), move)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void ChessBoard::removePieceFromBoard(Position position)
    {
        auto piece = getPiece(position);
        if (piece) {
            piecesVect_[posTo1D(position)] = shared_ptr<Piece>(nullptr);
        }
    }

    void ChessBoard::movePiece(Position posInit, Position posVoulue) {
        if (posInit.isOnBoard() && posVoulue.isOnBoard()) {
            auto copiePieces = piecesVect_;

            auto pieceADeplacer = getPiece(posInit).get();

            // On verifie qu'il y as une piece sur la case
            if (pieceADeplacer) {

                // On verifie si la piece est de la bonne couleure
                if (pieceADeplacer->getColor() == colorToPlay_) {
                    for (auto positionPossible : pieceADeplacer->getValidMoves(*this).first) {
                        if (posVoulue == positionPossible) {

                            piecesVect_[posTo1D(posVoulue)] = move(getPiece(posInit));
                            if (kingToPlayIsInCheck()) {
                                emit(impossibleMove("King in check, movement canceled"));
                                piecesVect_ = copiePieces;
                            }
                            else {
                                piecesVect_[posTo1D(posVoulue)]->setPos(posVoulue);
                                changeColor(colorToPlay_);

                                // check if the move is a castle
                                auto king = dynamic_cast<King*>(pieceADeplacer);
                                if (king) {
                                    if (posVoulue.x - posInit.x == 2) {
                                        piecesVect_[posTo1D({ posVoulue.x + 1, posVoulue.y })]->setPos({ posVoulue.x - 1, posVoulue.y });
                                        piecesVect_[posTo1D({ posVoulue.x - 1, posVoulue.y })] = move(getPiece({ posVoulue.x + 1, posVoulue.y }));
                                    }
                                    else if (posVoulue.x - posInit.x == -3) {
                                        piecesVect_[posTo1D({ posVoulue.x - 1, posVoulue.y })]->setPos({ posVoulue.x + 1, posVoulue.y });
                                        piecesVect_[posTo1D({ posVoulue.x + 1, posVoulue.y })] = move(getPiece({ posVoulue.x - 1, posVoulue.y }));
                                    }
                                }
                                else {
                                    auto pawn = dynamic_cast<Pawn*>(pieceADeplacer);
                                    if (pawn && (posInit.x - posVoulue.x) != 0) {
                                        removePieceFromBoard({ posVoulue.x, posVoulue.y + (colorToPlay_ ? -1 : 1)});
                                    }
                                    if (pawn && (posVoulue.y == 1 || posVoulue.y == 8)) {
                                        posPawnToPromote_ = posVoulue;
                                        emit(promotePawn(colorToPlay_ == Color::white ? Color::black : Color::white));
                                    }
                                }
                                if (kingToPlayIsCheckMated()) {
                                    char checkMateMessage[30];
                                    printf("Check Mate, %s side wins.", colorToPlay_ ? "White" : "Black");
                                    emit(impossibleMove(checkMateMessage));
                                }

                                

                                ChessBoard::shouldUpdate();
                            }
                        }
                    }
                    // Si on se rend ici, le mouvement voulu est impossible
                    emit(impossibleMove("The piece cannot move there"));
                }

                else {
                    emit(impossibleMove("The piece is not the right color"));
                    return;
                }

            }
            else {
                emit(impossibleMove("Click on a piece to move it"));
            }
        }
    }

    bool ChessBoard::moveIsValid(Position posInit, Position posVoulue)
    {
        if (posInit.isOnBoard() && posVoulue.isOnBoard()) {
            auto copiePieces = piecesVect_;

            auto& pieceADeplacer = getPiece(posInit);

            // On verifie qu'il y as une piece sur la case
            if (pieceADeplacer) {

                // On verifie si la piece est de la bonne couleure
                if (pieceADeplacer->getColor() == colorToPlay_) {
                    for (auto positionPossible : pieceADeplacer->getValidMoves(*this).first) {
                        if (posVoulue == positionPossible) {

                            piecesVect_[posTo1D(posVoulue)] = move(getPiece(posInit));
                            if (kingToPlayIsInCheck()) {
                                piecesVect_ = copiePieces;
                                return false;
                            }
                            piecesVect_ = copiePieces;
                            return true;
                        }
                    }
                    // Si on se rend ici, le mouvement voulu est impossible
                    return false;
                }

                else {
                    return false;
                }

            }
            else {
                return false;
            }
        }
        return false;
    }

    bool ChessBoard::isEnemyKing(Piece* piece) const
    {
        return dynamic_cast<King*>(piece);
    }

    unsigned ChessBoard::getNbrPiecesEnJeu() {
        unsigned count = 0;
        for (auto& piece : piecesVect_) {
            if (piece)
                ++count;
        }
        return count;
    }

    Color ChessBoard::getColorToPlay() {
        return colorToPlay_;
    }

    vector<Piece*> ChessBoard::getVectPieceEnJeu() {
        vector<Piece*> vectorPieceEnJeu;
        for (auto& piece : piecesVect_) {
            if (piece)
                vectorPieceEnJeu.push_back(piece.get());
        }
        return vectorPieceEnJeu;
    }

    void ChessBoard::reset() {
        for (auto& piece : piecesVect_) {
            piece = nullptr;
        }

        colorToPlay_ = Color::white;
    }

    void ChessBoard::shouldUpdate() {
        emit(boardChanged(piecesVect_));
    }
}