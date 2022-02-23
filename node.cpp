#include "node.h"

Node::Node()
{
    coefficient = 1;
    bases_degrees.resize(26);
    next = nullptr;
    prev = nullptr;
}

void Node::Add_base_with_degree(char base, int degree) {
    bases_degrees[base - 97] += degree;
}
