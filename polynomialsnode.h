#ifndef POLYNOMIALSNODE_H
#define POLYNOMIALSNODE_H

#include "polynomial.h"

class PolynomialsNode
{
public:
    PolynomialsNode* next;

    Polynomial* polynomial;

    PolynomialsNode();

    explicit PolynomialsNode(Polynomial* polynomial);
};

#endif // POLYNOMIALSNODE_H
