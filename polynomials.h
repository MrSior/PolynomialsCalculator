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
    Polynomial* FindDerivative(PolynomialsNode* polynomials_node, char base, int order);
    Polynomial* MultiplicationPolynomials(PolynomialsNode* first_polynomials_node, PolynomialsNode* second_polynomials_node);
    void CheckString(std::string str);
    PolynomialsNode* Get_element(int i);
    void Erase_node(int i);
    void Del_elem(PolynomialsNode*& node, int i);
};

#endif // POLYNOMIALS_H
