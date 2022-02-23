#include "polynomialsnode.h"

PolynomialsNode::PolynomialsNode(){
    next = nullptr;
    polynomial = nullptr;
}

PolynomialsNode::PolynomialsNode(Polynomial* polynomial){
    next = nullptr;
    this->polynomial = polynomial;
}
