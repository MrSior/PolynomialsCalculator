#include "polynomials.h"

Polynomials::Polynomials()
{
    head = nullptr;
}

void Polynomials::InsertHead(PolynomialsNode* polynomials_node){
    polynomials_node->next = head;
    head = polynomials_node;
}

Polynomial* Polynomials::SumPolynomials(PolynomialsNode* first_polynomials_node, PolynomialsNode* second_polynomials_node){
    //auto* polynomials_node = new PolynomialsNode;
    Polynomial* first_polynomial = new Polynomial(first_polynomials_node->polynomial);
    Polynomial* second_polynomial = new Polynomial(second_polynomials_node->polynomial);
    auto* res_polynomial = new Polynomial();
    res_polynomial->Merge(first_polynomial->head, second_polynomial->head, res_polynomial->head);
    return res_polynomial;
}

void Polynomials::CheckString(std::string str){
    for(auto i : str){
        if (!isSign(i) && !isLetter(i) && !isNumber(i)){
            throw std::invalid_argument("inncorect symbols");
        }
    }
    bool flag = false;
    while (!flag){
        flag = true;
        for (int i = 0; i < str.size(); ++i) {
            if (i == 0 || i == int(str.size()) - 1){
                if (str[i] == ' '){
                    str.erase(str.begin() + i);
                    i--;
                    flag = false;
                } else if (str[i] == '*'){
                    //throw "missed factor";
                    throw std::invalid_argument("missed factor");
                } else if (i == int(str.size()) - 1){
                    if (str[i] == '+' || str[i] == '-'){
                        //throw "missed summand";
                        throw std::invalid_argument("missed summand");
                    }
                }
            } else {
                if (str[i] == ' '){
                    if (str[i - 1] == ' ' || str[i + 1] == ' '){
                        str.erase(str.begin() + i);
                        i--;
                        flag = false;
                    } else if ((isNumber(str[i - 1]) || isLetter(str[i - 1])) &&
                               (isNumber(str[i - 1]) || isLetter(str[i - 1]))) {
                        //throw "missed sign";
                        throw std::invalid_argument("missed sign");
                    } else if (isSign(str[i - 1]) && isSign(str[i + 1])) {
                        //throw "missed summand or degree or factor";
                        throw std::invalid_argument("missed summand or degree or factor");
                    }
                } else if (str[i] == '^') {
                    if (str[i - 1] == '^' || str[i + 1] == '^'){
                        throw std::invalid_argument("missed degree");
                    }
                } else if (str[i] == '*') {
                    if (str[i - 1] == '*' || str[i + 1] == '^'){
//                        throw "missed factor";
                        throw std::invalid_argument("missed factor");
                    }
                } else if (str[i] == '+') {
                    if (str[i - 1] == '+' || str[i + 1] == '^'){
//                        throw "missed summand";
                        throw std::invalid_argument("missed summand");
                    }
                }
            }
        }
    }
    if (str.empty()){
        throw std::invalid_argument("no polynomial");
    }
}

PolynomialsNode* Polynomials::Get_element(int i){
    PolynomialsNode* node = head;
    while(i--){
        node = node->next;
    }
    return node;
}
