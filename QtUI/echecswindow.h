#ifndef ECHECSWINDOW_H
#define ECHECSWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class EchecsWindow; }
QT_END_NAMESPACE

class EchecsWindow : public QMainWindow
{
    Q_OBJECT

public:
    EchecsWindow(QWidget *parent = nullptr);
    ~EchecsWindow();

private:
    Ui::EchecsWindow *ui;
};
#endif // ECHECSWINDOW_H
