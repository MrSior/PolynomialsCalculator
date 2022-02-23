#ifndef POLYNOMIALS_H
#define POLYNOMIALS_H

#include "polynomialsnode.h"
#include "string"
#include "CharFunctions.h"

class Polynomials
{
public:
    PolynomialsNode* head;

    Polynomials();

    void InsertHead(PolynomialsNode* polynomials_node);

    Polynomial* SumPolynomials(PolynomialsNode* first_polynomials_node, PolynomialsNode* second_polynomials_node);
    void CheckString(std::string str);
    PolynomialsNode* Get_element(int i);
};

#endif // POLYNOMIALS_H
