#include "../Headers/ChessBoard.h"
#include "../Headers/Piece.h"
#include "../Headers/Knight.h"
#include "../Headers/King.h"
#include "../Headers/Rook.h"

#include "gtest/gtest.h"



TEST(InitialPlacementsTest, InvalidPlacements) {
    using namespace model;
    ChessBoard chessBoard;
    std::vector<Piece*> piecesEnJeu;

    //Positions valides
    chessBoard.addPiece("king", Color::white, { 1, 2 });
    chessBoard.addPiece("king", Color::white, { 1, 3 });

    //Positions invalides
    chessBoard.addPiece("king", Color::white, { 150, 3 });
    chessBoard.addPiece("king", Color::white, { 7, 90 });

    ASSERT_EQ(chessBoard.getNbrPiecesEnJeu(), 2);

    Position positionTest = { 1, 2 };
    piecesEnJeu = chessBoard.getVectPieceEnJeu();
    ASSERT_TRUE((piecesEnJeu[0]->getPos() == Position{ 1, 2 }));
    ASSERT_TRUE((piecesEnJeu[1]->getPos() == Position{ 1, 3 }));

    ASSERT_EQ(piecesEnJeu[0]->getColor(), Color::white);
}

TEST(InitialPlacementsTest, PlacementsInitialValues) {
    using namespace model;
    ChessBoard echiquier;
    echiquier.addPiece("king", Color::white, { 2, 2 });
    echiquier.addPiece("rook", Color::white, { 5, 6 });
    echiquier.addPiece("knight", Color::white, { 6, 7 });

    std::vector<Piece*> piecesEnJeu;
    piecesEnJeu = echiquier.getVectPieceEnJeu();

    ASSERT_TRUE((piecesEnJeu[0]->getPos() == Position{ 2, 2 }));
    ASSERT_TRUE((piecesEnJeu[1]->getPos() == Position{ 5, 6 }));
    ASSERT_TRUE((piecesEnJeu[2]->getPos() == Position{ 6, 7 }));

    ASSERT_TRUE((dynamic_cast<King*>(piecesEnJeu[0])));
    ASSERT_TRUE((dynamic_cast<Rook*>(piecesEnJeu[1])));
    ASSERT_TRUE((dynamic_cast<Knight*>(piecesEnJeu[2])));

    ASSERT_EQ(int(piecesEnJeu[0]->getColor()), int(Color::white));
    ASSERT_EQ(int(piecesEnJeu[1]->getColor()), int(Color::white));
    ASSERT_EQ(int(piecesEnJeu[2]->getColor()), int(Color::white));
}

TEST(InitialPlacementsTest, KingPlacementException) {
    using namespace model;
    ChessBoard echiquier;

    std::string expected = "Two kings are already in play.";
    std::string received;
    EXPECT_THROW({
        try {
            echiquier.addPiece("king", Color::white, { 1, 1 });
            echiquier.addPiece("king", Color::white, { 1, 2 });

            // This third placement throws an exception
            echiquier.addPiece("king", Color::white, { 1, 3 });
        }

        catch (const std::logic_error& erreur) {
            received = erreur.what();
            ASSERT_EQ(expected, received);
            throw;
        }

    }, std::logic_error);
}

TEST(MovementTest, AlternanceCouleurs) {
    using namespace model;
    ChessBoard echiquier;
    Position posAttendue;
    std::vector<Piece*> piecesEnJeu;

    echiquier.addPiece("knight", Color::white, { 3, 2 });
    echiquier.addPiece("knight", Color::black, { 6, 7 });

    echiquier.movePiece({ 3, 2 }, { 5, 3 });

    // This movement fails because moving pieces of the same color twice is not allowed
    echiquier.movePiece({ 5, 3 }, { 7, 2 });
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    posAttendue = { 5, 3 };
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);

    echiquier.movePiece({ 6, 7 }, { 7, 5 });
    posAttendue = { 7, 5 };

    echiquier.movePiece({ 7, 5 }, { 5, 6 });
    ASSERT_TRUE(piecesEnJeu[1]->getPos() == posAttendue);
}

TEST(MovementTest, CaseVide) {
    using namespace model;
    ChessBoard echiquier;
    Position posAttendue;
    std::vector<Piece*> piecesEnJeu;
    echiquier.addPiece("king", Color::white, { 1, 2 });

    echiquier.movePiece({ 5,6 }, { 7, 8 });
    posAttendue = { 1, 2 };

    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);
}

TEST(MovementTest, KingMovement) {
    using namespace model;
    ChessBoard echiquier;
    Position posAttendue;
    std::vector<Piece*> piecesEnJeu;

    echiquier.addPiece("king", Color::white, { 1, 2 });
    echiquier.addPiece("rook", Color::white, { 1, 1 });
    echiquier.addPiece("king", Color::black, { 2, 4 });

    echiquier.movePiece({ 1, 2 }, { 2, 2 });
    posAttendue = { 2, 2 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[1]->getPos() == posAttendue);

    echiquier.reset();
    echiquier.addPiece("king", Color::white, { 1, 2 });
    echiquier.addPiece("king", Color::black, { 2, 2 });
    echiquier.movePiece({ 1, 2 }, { 1, 3 });
    posAttendue = { 1, 2 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);
}

TEST(MovementTest, RookMovement) {
    using namespace model;
    ChessBoard echiquier;
    Position posAttendue;
    std::vector<Piece*> piecesEnJeu;

    echiquier.addPiece("rook", Color::black, { 4, 3 });
    echiquier.addPiece("rook", Color::black, { 4, 5 });
    echiquier.addPiece("rook", Color::black, { 3, 4 });
    echiquier.addPiece("rook", Color::black, { 5, 4 });

    echiquier.addPiece("rook", Color::white, { 4, 4 });
    echiquier.movePiece({ 4, 4 }, { 4, 3 });
    posAttendue = { 4, 3};
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);

    echiquier.reset();
    echiquier.addPiece("rook", Color::white, { 4, 3 });
    echiquier.addPiece("rook", Color::white, { 4, 5 });
    echiquier.addPiece("rook", Color::white, { 3, 4 });
    echiquier.addPiece("rook", Color::white, { 5, 4 });

    echiquier.addPiece("rook", Color::white, { 4, 4 });
    // Rook cannot capture a piece of the same color
    echiquier.movePiece({ 4, 4 }, { 4, 5 });
    posAttendue = { 4, 4 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[2]->getPos() == posAttendue);

    echiquier.reset();
    echiquier.addPiece("rook", Color::white, { 1, 1 });
    // Rook cannot move diagonally
    echiquier.movePiece({ 1, 1 }, { 8, 8 });
    posAttendue = { 1, 1 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);
}


TEST(MovementTest, KnightMovement) {
    using namespace model;
    ChessBoard echiquier;
    Position posAttendue;
    std::vector<Piece*> piecesEnJeu;

    echiquier.addPiece("knight", Color::white, { 1, 2 });
    echiquier.movePiece({ 1, 2 }, { 2, 4 });
    posAttendue = { 2, 4 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);

    echiquier.reset();
    echiquier.addPiece("knight", Color::white, { 5, 6 });
    echiquier.movePiece({ 5, 6 }, { 3, 5 });
    posAttendue = { 3, 5 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);

    echiquier.reset();
    echiquier.addPiece("knight", Color::white, { 1, 8 });
    echiquier.movePiece({ 1, 8 }, { 7, 5 });
    posAttendue = { 1, 8 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);
}

TEST(MovementTest, PieceCapture) {
    using namespace model;
    ChessBoard echiquier;
    Position posAttendue;
    std::vector<Piece*> piecesEnJeu;

    echiquier.addPiece("rook", Color::white, { 7, 4 });
    echiquier.addPiece("rook", Color::black, { 3, 4 });


    echiquier.movePiece({ 7, 4 }, { 3, 4 });
    posAttendue = { 3, 4 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();

    ASSERT_EQ(piecesEnJeu.size(), 1);
    ASSERT_TRUE(piecesEnJeu[0]->getPos() == posAttendue);
}

TEST(TestEchecs, EmpechementDeMouvementEnEchec) {
    using namespace model;
    ChessBoard echiquier;
    Position posAttendue;
    std::vector<Piece*> piecesEnJeu;

    echiquier.addPiece("king", Color::white, { 4, 5 });
    echiquier.addPiece("king", Color::black, { 7, 8 });

    echiquier.addPiece("rook", Color::black, { 7, 5 });
    echiquier.addPiece("knight", Color::black, { 3, 3 });
    echiquier.addPiece("knight", Color::white, { 7, 4 });

    // movement not allowed since king would be in check
    echiquier.movePiece({ 7, 4 }, { 6, 6 });
    
    posAttendue = { 7, 4 };
    piecesEnJeu = echiquier.getVectPieceEnJeu();

    ASSERT_TRUE(piecesEnJeu[1]->getPos() == posAttendue);
    ASSERT_EQ(echiquier.getColorToPlay(), Color::white);

}
