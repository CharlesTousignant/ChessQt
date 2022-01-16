#include "../Headers/ChessWindow.h"
#include "../Headers/King.h"
#include "../Headers/Rook.h"
#include "../Headers/Knight.h"

#include "qgraphicsview.h"
#include "qbuttongroup.h"

#include "ui_echecswindow.h"

#include <string>
namespace vue {
    using namespace std;

#define casesTot = 64

#define pathWhiteKing "./ressources/whiteKing.png"
#define pathBlackKing "./ressources/blackKing.png"
#define pathWhiteKnight "./ressources/whiteKnight.png"
#define pathBlackKnight "./ressources/blackKnight.png"
#define pathWhiteRook "./ressources/whiteRook.png"
#define pathBlackRook "./ressources/blackRook.png"
#define pathWhitePawn "./ressources/whitePawn.png"
#define pathBlackPawn "./ressources/blackPawn.png"
#define pathWhiteBishop "./ressources/whiteBishop.png"
#define pathBlackBishop "./ressources/blackBishop.png"
#define empty "./ressources/empty.png"

    void EchecsWindow::setImageCase(QPushButton* label, string pathImg = empty) {
        auto image = QPixmap(60, 60);

        // On doit mettre un background transparent pour rendre le bouton transparent
        const auto& qString = QString::fromStdString("QPushButton{background: transparent;\n" 
                                                                 "background-image: url(" + pathImg + ");}"); 
        label->setStyleSheet(qString);
    }

    model::Position indexToPos(const unsigned& index) {
        return { unsigned(index % 8) + 1, (index / 8) + 1 };
    }

    
    int getButtonCase(QPushButton* a) {
        auto nameA = a->objectName().toStdString().substr(11, 13);
        return stoi(nameA); 
    };


    EchecsWindow::EchecsWindow(QWidget* parent) :
          QMainWindow(parent),
          ui(new Ui::EchecsWindow)
    {   

        echiquier_ = make_unique<model::ChessBoard>();
        ui->setupUi(this);

        QList<QPushButton*> listCaseTemp = ui->echiquierWidget->findChildren<QPushButton*>();

        // On mets les boutons pour les cases de l'echiquier en ordre, pour un acces plus facile
        for (unsigned i = 0; i < 64; ++i) {
            for (auto button : listCaseTemp) {
                if (getButtonCase(button) == i)
                    listCases_.push_back(button);
            }
        }

        // On initialise les boutons (sans pieces), et les connectent au slot
        for (unsigned i = 0; i < 64; ++i) {
            setImageCase(listCases_[i], empty);
            connect(listCases_[i], &QPushButton::released, this, &EchecsWindow::handleButtonsBoard);
        }
        
        auto listBoutonsSetBoard = ui->BoutonsSetBoard->findChildren<QPushButton*>();
        for (auto buttonSetBoard : listBoutonsSetBoard) {
            connect(buttonSetBoard, &QPushButton::released, this, &EchecsWindow::setBoard);
        }

        // Connection pour mettre a jour l'echiquier
        connect(echiquier_.get(), &model::ChessBoard::boardChanged, this, &EchecsWindow::updateBoard);

        // Connection pour l'affichage lorsqu'un mouvement est impossible
        connect(echiquier_.get(), &model::ChessBoard::impossibleMove, this, &EchecsWindow::triedImpossibleMove);
    }

    EchecsWindow::~EchecsWindow()
    {
        delete ui;
    }

    void EchecsWindow::handleButtonsBoard() {
        QPushButton* buttonPressed = dynamic_cast<QPushButton*>(QObject::sender());

        int newPressedButton = getButtonCase(buttonPressed);
        if (lastPressedButton_ == -1) {
            
            // Le dernier caractere du nom d'un bouton est son index, de 0 a 63
            lastPressedButton_ = newPressedButton;
        }

        else {
            echiquier_->movePiece(indexToPos(lastPressedButton_), indexToPos(newPressedButton));

            // On remets lastPressedButton a sa valeur de depart
            lastPressedButton_ = -1;
        }
    };

    // Utilisee pour choisir une position de depart avec un des trois boutons
    void EchecsWindow::setBoard() {
        echiquier_->reset();

        // On trouve l'index associe au bouton appuye. *ButtonGroup ne semblait pas fonctionner si on pars d'un ui de QtCreator*
        string buttonName = QObject::sender()->objectName().toStdString().substr(15, 16);
        int choiceBoard = stoi(buttonName);
        using namespace model;

        switch (choiceBoard) {
        case 1:

            echiquier_->addPiece("knight", Color::white, { 1, 1 });
            echiquier_->addPiece("knight", Color::white, { 1, 5 });
            echiquier_->addPiece("king", Color::white, { 1, 6 });

            echiquier_->addPiece("rook", Color::black, { 8, 6 });
            echiquier_->addPiece("king", Color::black, { 8, 8 });
            break;

        case 2:

            echiquier_->addPiece("king", Color::white, { 3, 6 });
            echiquier_->addPiece("knight", Color::white, { 3, 4 });
            echiquier_->addPiece("rook", Color::white, { 1, 6 });

            echiquier_->addPiece("rook", Color::black, { 8, 6 });
            echiquier_->addPiece("king", Color::black, { 6, 8 });
            echiquier_->addPiece("rook", Color::black, { 1, 8 });
            break;

        case 3:

            echiquier_->addPiece("king", Color::white, { 6, 8 });

            echiquier_->addPiece("knight", Color::black, { 2, 1 });
            echiquier_->addPiece("king", Color::black, { 6, 1 });
            echiquier_->addPiece("knight", Color::black, { 7, 1 });
            break;
        }
    }

    string generatePathFromPiece(model::Piece* piece) {
        using namespace model;

        if (!piece)
            return empty;

        else if (piece->getColor() == Color::black) {
            if (dynamic_cast<King*>(piece))
                return pathBlackKing;
            else if (dynamic_cast<Knight*>(piece))
                return pathBlackKnight; 
            else
                return pathBlackRook;
        }

        else {
            if (dynamic_cast<King*>(piece))
                return pathWhiteKing;
            else if (dynamic_cast<Knight*>(piece))
                return pathWhiteKnight;
            else
                return pathWhiteRook;
        }
    }

    void EchecsWindow::updateBoard(vector<shared_ptr<model::Piece>> pieces) {
        ui->plainTextEdit->setPlainText("");
        for (unsigned i = 0; i < pieces.size(); ++i) {
            setImageCase(listCases_[i], generatePathFromPiece(pieces[i].get()));
        }
    }

    void EchecsWindow::triedImpossibleMove(string message) {
        ui->plainTextEdit->setPlainText(QString::fromStdString(message));
    }
}