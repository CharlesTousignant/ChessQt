#pragma once

#include "ChessBoard.h"
#include "Piece.h"

#include <vector>
#include <set>

#pragma warning(push, 0) // Needed to stop Qt warnings
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <qwidget.h>
#include <qobjectdefs.h>
#include <qgridlayout.h>
#pragma pop()

QT_BEGIN_NAMESPACE
namespace Ui { class ChessWindow; }
QT_END_NAMESPACE

namespace vue {


int getButtonCase(QPushButton* a);

class ChessWindow : public QMainWindow {
    Q_OBJECT

public:
    ChessWindow(QWidget* parent = nullptr);
    ~ChessWindow();

public slots:
void handleButtonsBoard();
void setBoard();

void updateBoard(std::vector<std::shared_ptr<model::Piece>> pieces);
void triedImpossibleMove(std::string message);


signals:
// Emitted when then user has clicked twice
void deplacementPossible(model::Position caseDepart, model::Position caseArrivee);

private:

    Ui::ChessWindow* ui;
    std::unique_ptr<model::ChessBoard> chessBoard_;
    int lastPressedButton_ = -1;
    std::vector<QPushButton*> listCases_;
    void displayPossibleMoves(model::Position startPosition, const std::vector<model::Position>& moves) const;
    void addPossibleMoveCircle(QPushButton* label) const;
    void highlightPiece(QPushButton* label) const;
    // Gives an image to a pushButton
    void setImageCase(QPushButton* label, std::string pathIMG) const;
};

std::string generatePathFromPiece(const model::Piece* piece);

// Get board position from position in 1D
model::Position indexToPos(const unsigned& index);
}