#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "polynomials.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ChangeList();
    Polynomials polynomials;

private slots:
    void on_AddPolynomialButton_clicked();

    void on_findSumButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
