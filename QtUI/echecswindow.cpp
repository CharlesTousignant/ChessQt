#include "echecswindow.h"
#include "ui_echecswindow.h"

EchecsWindow::EchecsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EchecsWindow)
{
    ui->setupUi(this);
}

EchecsWindow::~EchecsWindow()
{
    delete ui;
}

