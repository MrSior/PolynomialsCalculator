#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDebug"
#include "QHBoxLayout"
#include "form.h"
#include "map"

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
    ui->multiplicationResLabel->setStyleSheet("QLabel {"
                                              "border-style: solid;"
                                              "border-width: 1px;"
                                              "border-color: black; "
                                              "}");
    ui->countValueLabel->setStyleSheet("QLabel {"
                                       "border-style: solid;"
                                       "border-width: 1px;"
                                       "border-color: black; "
                                       "}");
    ui->solutionResLabel->setStyleSheet("QLabel {"
                                        "border-style: solid;"
                                        "border-width: 1px;"
                                        "border-color: black; "
                                        "}");
    ChangeList();
    isValueSet = false;
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
    ui->multiplicationSpinBox1->setMaximum(max);
    ui->multiplicationSpinBox2->setMaximum(max);
    ui->countValueSpinBox->setMaximum(max);
    ui->eraseSpinBox->setMaximum(max);
    ui->solutionSpinBox->setMaximum(max);
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
    if(ui->variableLineEdit->text().toStdString().size() < 1 && ui->variableLineEdit->text().toStdString().size() > 1) return;
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


void MainWindow::on_findMultiplicationButton_clicked()
{
    if(ui->listWidget->count() == 0) return;
    auto i = polynomials.MultiplicationPolynomials(polynomials.Get_element(ui->multiplicationSpinBox1->value()),
                                                   polynomials.Get_element(ui->multiplicationSpinBox2->value()));
    ui->multiplicationResLabel->setText(QString::fromStdString(i->GetString()));
    if(ui->multiplicationRadioButton->isChecked()){
        PolynomialsNode* node = new PolynomialsNode(i);
        polynomials.InsertHead(node);
        ChangeList();
    }
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->listWidget->count() == 0) return;
    isValueSet = false;
    chosenPolunomial = ui->countValueSpinBox->value();
    map.clear();
    Form* form = new Form(polynomials.Get_element(chosenPolunomial)->polynomial, &map, &isValueSet);
    form->setWindowTitle("form");
    form->show();
}


void MainWindow::on_countValuePushButton_clicked()
{
    if(ui->listWidget->count() == 0) return;
    if(!isValueSet) return;
    Node* node = polynomials.Get_element(chosenPolunomial)->polynomial->head;
    double sum = 0;
    while(node != nullptr){
        double value = 1;
        for(int i = 0; i < node->bases_degrees.size(); ++i){
            if(node->bases_degrees[i] != 0){
                value *= std::pow(map['a' + i], node->bases_degrees[i]);
            }
        }
        value *= node->coefficient;
        sum += value;
        node = node->next;
    }

    ui->countValueLabel->setText(QString::fromStdString(std::to_string(sum)));
}


void MainWindow::on_erasePushButton_clicked()
{
    if(ui->listWidget->count() == 0) return;
    int ind = ui->eraseSpinBox->value();
    polynomials.Erase_node(ind);
    ChangeList();
}


void MainWindow::on_solutionPushButton_clicked()
{
    ui->solutionResLabel->clear();
    if(ui->listWidget->count() == 0) return;
    auto i = polynomials.Get_element(ui->solutionSpinBox->value())->polynomial;
    int offset = 0;
    int coefficent;
    try {
        coefficent = i->Get_free_node(offset);
    }  catch (std::invalid_argument error) {
        QMessageBox::critical(this, "Incorrect input", error.what());
        return;
    }
    std::vector<int> solutions;
    if(offset != 0){
        solutions.push_back(0);
    }
    for(int divider = -std::abs(coefficent); divider <= std::abs(coefficent); ++divider){
        if (divider != 0 && coefficent % divider == 0){
            if(i->Count_value(divider, offset) == 0){
                solutions.push_back(divider);
            }
        }
    }
    std::string str = "{";
    for(auto solution : solutions){
        str += " " + std::to_string(solution) + ";";
    }
    if(str.size() > 1){
        str.pop_back();
    }
    str += " }";
    ui->solutionResLabel->setText(QString::fromStdString(str));
}

