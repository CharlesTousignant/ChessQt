#pragma once

#include "Piece.h"

namespace model {
    class ChessBoard : public QObject {
        Q_OBJECT
    public:
        ChessBoard();
        ~ChessBoard() = default;

        void addPiece(std::string type, Color color, Position posPiece);

        unsigned getNbrPiecesEnJeu();
        Color getColorToPlay();

        void reset();
        std::shared_ptr<Piece>& getPiece(Position posPiece);
        //std::vector<Position> getAvailableMoves(King* piece);
        //std::pair<std::vector<Position>, bool> getAvailableMoves(Rook* piece);
        std::vector<Piece*> getVectPieceEnJeu();

        std::vector<std::shared_ptr<Piece>> piecesVect_;
        std::vector<Position> getMovesPiece(Position posPiece);
        void movePiece(Position posInit, Position posVoulue);
        bool moveIsValid(Position posInit, Position posVoulue);

        bool isEnemyKing(Piece* piece) const;
        std::pair<bool, bool> castleWayIsClear(Color color);
        void removePieceFromBoard(Position position);

    signals:
        void boardChanged(std::vector<std::shared_ptr<Piece>> boardState);
        void impossibleMove(std::string message);

    private:
        //void findMovesBlockedByTeam(std::vector<Position>& pos, Color color);
        //std::vector<Position> findPossibleCaptures(std::vector<Position> moves, Color color);

        void shouldUpdate();

        bool kingToPlayIsInCheck();
        bool kingToPlayIsCheckMated();

        Color colorToPlay_;
    };
}