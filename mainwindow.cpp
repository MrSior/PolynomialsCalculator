#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sumResLabel->setStyleSheet("QLabel {"
                                   "border-style: solid;"
                                   "border-width: 1px;"
                                   "border-color: black; "
                                   "}");
    ui->derivativeResLabel->setStyleSheet("QLabel {"
                                   "border-style: solid;"
                                   "border-width: 1px;"
                                   "border-color: black; "
                                   "}");
    ChangeList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ChangeList(){
    ui->listWidget->clear();
    PolynomialsNode* node = polynomials.head;
    int cnt = 0;
    while (node != nullptr) {
        std::string str = std::to_string(cnt) + ") ";
        str += node->polynomial->GetString();
        ui->listWidget->addItem(QString::fromStdString(str));
        node = node->next;
        cnt++;
    }
    int max = ui->listWidget->count() - 1;
    if (max < 0) max = 0;
    ui->spinBox->setMaximum(max);
    ui->spinBox_2->setMaximum(max);
    ui->derivativePolynomialSpinBox->setMaximum(max);
    ui->derivativeOrderSpinBox->setMinimum(1);
}

void MainWindow::on_AddPolynomialButton_clicked()
{
    try {
        polynomials.CheckString(ui->lineEdit->text().toStdString());
        Polynomial* polynomial = new Polynomial;
        polynomial->Convert(ui->lineEdit->text().toStdString());
        PolynomialsNode* polynomialsNode = new PolynomialsNode(polynomial);
        polynomials.InsertHead(polynomialsNode);
        ui->lineEdit->clear();
        ChangeList();
    }  catch (std::invalid_argument error) {
        QMessageBox::critical(this, "Incorrect input", error.what());
    }
}


void MainWindow::on_findSumButton_clicked()
{
    if(ui->listWidget->count() == 0) return;
    auto i = polynomials.SumPolynomials(polynomials.Get_element(ui->spinBox->value()), polynomials.Get_element(ui->spinBox_2->value()));
    ui->sumResLabel->setText(QString::fromStdString(i->GetString()));
    if(ui->addSumRadioButton->isChecked()){
        PolynomialsNode* node = new PolynomialsNode(i);
        polynomials.InsertHead(node);
        ChangeList();
    }
}


void MainWindow::on_findDerivativeButton_clicked()
{
    if(ui->listWidget->count() == 0) return;
    if(ui->variableLineEdit->text().size() < 1 && ui->variableLineEdit->text().size() > 1) return;
    if(!isLetter(ui->variableLineEdit->text().toStdString()[0])) return;
    char base = ui->variableLineEdit->text().toStdString()[0];
    int order = ui->derivativeOrderSpinBox->value();
    if(order < 1) return;
    auto res = polynomials.FindDerivative(polynomials.Get_element(ui->derivativePolynomialSpinBox->value()), base, order);
    ui->derivativeResLabel->setText(QString::fromStdString(res->GetString()));
    if(ui->addDerivativeRadioButton->isChecked()){
        PolynomialsNode* node = new PolynomialsNode(res);
        polynomials.InsertHead(node);
        ChangeList();
    }
}

