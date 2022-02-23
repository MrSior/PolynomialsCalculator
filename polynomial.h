#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "node.h"
#include "CharFunctions.h"

class Polynomial
{
public:
    Node* head;
    std::vector<int> bases;

    Polynomial();

    void Convert(std::string str);
    void Insert_head(Node* node);
    void sort();
    void Shorten();
    void EraseNode(Node* node);
    void Merge_sort(Node*& head);
    void m_sort(Node*& head, int len);
    void Merge(Node* head1, Node* head2, Node*& new_head);
    void Get_mid(Node* head, int n, Node*& mid, Node*& prev);
    int Get_length(Node* head);
    std::string  GetString();
};

#endif // POLYNOMIAL_H