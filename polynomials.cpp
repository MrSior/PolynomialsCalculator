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

Polynomial* Polynomials::FindDerivative(PolynomialsNode* polynomials_node, char base, int order){
    Polynomial* polynomial = new Polynomial(polynomials_node->polynomial);
    while(order--){
        Node* node = polynomial->head;
        while(node != nullptr){
            if(node->Get_degree_of_base(base - 97) == 0){
                if(!(node->prev == nullptr && node->next == nullptr)) {
                    if(node->next != nullptr){
                        node->next->prev = node->prev;
                    }
                    if(node->prev != nullptr){
                        node->prev->next = node->next;
                    }
                    Node* tmp = node->next;
                    delete node;
                    node = tmp;
                } else {
                    node->bases_degrees.clear();
                    node->bases_degrees.resize(26);
                    node->coefficient = 0;
                }
            } else {
                node->coefficient *= node->Get_degree_of_base(base - 97);
                node->bases_degrees[base - 97]--;
            }
            node = node->next;
        }
    }
    return polynomial;
}

void Polynomials::CheckString(std::string str){
    for(auto i : str){
        if (!isSign(i) && !isLetter(i) && !isNumber(i) && i != ' '){
            throw std::invalid_argument("inncorect symbols");
        }
    }
    std::pair<int, int> spaces;
    spaces.first = -1;
    spaces.second = -1;
    for(int i = 0; i < str.size(); ++i){
        if(i + 1 < str.size() && str[i] == '^' && !isNumber(str[i + 1])){
            throw std::invalid_argument("missed degree");
        }
        if(i - 1 >= 0){
            if((str[i] == '-' && str[i-1] == '-') || (str[i] == '+' && str[i-1] == '+')){
                throw std::invalid_argument("missed summand");
            }
            if(str[i] == '*' && str[i - 1] == '*'){
                throw std::invalid_argument("missed factor");
            }
            if(isSign(str[i]) && isSign(str[i-1])){
                throw std::invalid_argument("two signes near");
            }
        }
        if(str[i] == ' '){
            if(spaces.first == -1){
                spaces.first = i - 1;
                spaces.second = i + 1;
            } else {
                spaces.second = i + 1;
            }
        } else {
            if(spaces.first == -1 || spaces.second == -1) continue;
            if(spaces.first >= 0 && spaces.second < str.size()){
                if(str[spaces.first] == ' '){
                    if(str[spaces.second] == '*' || str[spaces.second] == '^'){
                        throw std::invalid_argument("incorrect sign");
                    }
                } else {
                    if(str[spaces.first] == '*' && str[spaces.second] == '*'){
                        throw std::invalid_argument("missed factor");
                    }
                    if((str[spaces.first] == '-' && str[spaces.second] == '-') ||
                       (str[spaces.first] == '+' && str[spaces.second] == '+')){
                        throw std::invalid_argument("missed summand");
                    }
                    if(!isSign(str[spaces.first]) && !isSign(str[spaces.second])){
                        throw std::invalid_argument("missed sign");
                    } else if(isSign(str[spaces.first]) && isSign(str[spaces.second])){
                        throw std::invalid_argument("two signes near");
                    }
                }
            }
            //str.erase(spaces.first + 1, spaces.second - spaces.first - 2);
            spaces.first = -1;
            spaces.second = -1;
        }
    }
    if(spaces.first != -1){
        if(!isNumber(str[spaces.first]) && !isLetter(str[spaces.first])) {
            if(str[spaces.first] == ' '){
                throw std::invalid_argument("empty input");
            }
            throw std::invalid_argument("extra sign");
        }
    }
    if (str.empty()){
        throw std::invalid_argument("no polynomial");
    }
    if(str[0] == '*' || str[0] == '^'){
        throw std::invalid_argument("incorrect sign");
    }
    if(isSign(str[str.size() - 1])){
        throw std::invalid_argument("incorrect sign");
    }

//    bool flag = false;
//    while (!flag){
//        flag = true;
//        for (int i = 0; i < str.size(); ++i) {
//            if (i == 0 || i == int(str.size()) - 1){
//                if (str[i] == ' '){
//                    str.erase(str.begin() + i);
//                    i--;
//                    flag = false;
//                } else if (str[i] == '*'){
//                    //throw "missed factor";
//                    throw std::invalid_argument("missed factor");
//                } else if (i == int(str.size()) - 1){
//                    if (str[i] == '+' || str[i] == '-'){
//                        //throw "missed summand";
//                        throw std::invalid_argument("missed summand");
//                    }
//                }
//            } else {
//                if (str[i] == ' '){
//                    if (str[i - 1] == ' ' || str[i + 1] == ' '){
//                        str.erase(str.begin() + i);
//                        i--;
//                        flag = false;
//                    } else if ((isNumber(str[i - 1]) || isLetter(str[i - 1])) &&
//                               (isNumber(str[i - 1]) || isLetter(str[i - 1]))) {
//                        //throw "missed sign";
//                        throw std::invalid_argument("missed sign");
//                    } else if (isSign(str[i - 1]) && isSign(str[i + 1])) {
//                        //throw "missed summand or degree or factor";
//                        throw std::invalid_argument("missed summand or degree or factor");
//                    }
//                } else if (str[i] == '^') {
//                    if (str[i - 1] == '^' || str[i + 1] == '^'){
//                        throw std::invalid_argument("missed degree");
//                    }
//                } else if (str[i] == '*') {
//                    if (str[i - 1] == '*' || str[i + 1] == '^'){
////                        throw "missed factor";
//                        throw std::invalid_argument("missed factor");
//                    }
//                } else if (str[i] == '+') {
//                    if (str[i - 1] == '+' || str[i + 1] == '^'){
////                        throw "missed summand";
//                        throw std::invalid_argument("missed summand");
//                    }
//                }
//            }
//        }
//    }
//    if (str.empty()){
//        throw std::invalid_argument("no polynomial");
//    }
}

PolynomialsNode* Polynomials::Get_element(int i){
    PolynomialsNode* node = head;
    while(i--){
        node = node->next;
    }
    return node;
}
