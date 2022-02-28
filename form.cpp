#include "form.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "QDebug"
#include "QMessageBox"

Form::Form(Polynomial* polynomial, std::map<char, double>* _map, bool* _isFilled, QWidget *parent) : QWidget(parent)
{
    map = _map;
    isFilled = _isFilled;
    QFormLayout* formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    polynomial->Count_bases();
    for (int i = 0; i < polynomial->bases.size(); ++i) {
        if(polynomial->bases[i] != 0){
            QLineEdit *edit = new QLineEdit(this);
            std::string str = "a";
            str[0] += i;
            lines.push_back(std::make_pair(str[0], edit));
            formLayout->addRow(QString::fromStdString(str), edit);
        }
    }

    QPushButton* button = new QPushButton;
    button->setText("Set");
    formLayout->addRow(button);
    QObject::connect(button, &QPushButton::clicked, this, &Form::setButtonClicked);

//    QLineEdit *nameEdit = new QLineEdit(this);
//    QLineEdit *addrEdit = new QLineEdit(this);
//    QLineEdit *occpEdit = new QLineEdit(this);

//    formLayout->addRow("Name:", nameEdit);
//    formLayout->addRow("Email:", addrEdit);
//    formLayout->addRow("Age:", occpEdit);

    setLayout(formLayout);
}

void Form::setButtonClicked(){
    try {
        for(auto i : lines){
            double val = std::stod(i.second->text().toStdString());
            map->insert(std::make_pair(i.first, val));
        }
        this->close();
        *isFilled = true;
    }  catch (...) {
        map->clear();
        QMessageBox::critical(this, "Incorrect input", "Incorrect input");
    }
}
