#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AddPolynomialButton_clicked()
{
    try {
        polynomials.CheckString(ui->lineEdit->text().toStdString());
        Polynomial* polynomial = new Polynomial;
        polynomial->Convert(ui->lineEdit->text().toStdString());
        polynomial->sort();
        PolynomialsNode* polynomialsNode = new PolynomialsNode(polynomial);
        polynomials.InsertHead(polynomialsNode);
        ui->listWidget->addItem(QString::fromStdString(polynomial->GetString()));
        ui->lineEdit->clear();
    }  catch (std::invalid_argument& error) {
        QMessageBox::critical(this, "Incorrect input", error.what());
    }
}

