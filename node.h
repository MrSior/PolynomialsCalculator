#ifndef NODE_H
#define NODE_H

#include "vector"

class Node
{
public:
    double coefficient;
    std::vector<int> bases_degrees;

    Node* next;
    Node* prev;

    Node();

    int Get_degree_of_base(int base){
        return bases_degrees[base];
    }

    void Add_base_with_degree(char base, int degree){
        bases_degrees[base - 97] += degree;
    }
};

#endif // NODE_H
