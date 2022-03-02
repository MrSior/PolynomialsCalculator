#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QListWidget"
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

    std::map<char, double> map;
    int chosenPolunomial;
    bool isValueSet;

    void ChangeList();
    Polynomials* polynomials;

private slots:
    void on_AddPolynomialButton_clicked();

    void on_findSumButton_clicked();

    void on_findDerivativeButton_clicked();

    void on_findMultiplicationButton_clicked();

    void on_pushButton_clicked();

    void on_countValuePushButton_clicked();

    void on_erasePushButton_clicked();

    void on_solutionPushButton_clicked();

    void on_savePushButton_clicked();

    void on_loadPushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
