#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QApplication>
#include "polynomial.h"
#include "QFormLayout"
#include "QLineEdit"
#include "vector"
#include "map"

class Form  : public QWidget
{
public:
    std::map<char, double>* map = nullptr;
    std::vector<std::pair<char, QLineEdit*>> lines;

    Form(Polynomial* polynomial, std::map<char, double>* _map, QWidget *parent = 0);
    ~Form() {};
private slots:
    void setButtonClicked();
};

#endif // FORM_H
