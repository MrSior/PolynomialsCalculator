#include "node.h"

Node::Node()
{
    coefficient = 1;
    bases_degrees.resize(26);
    next = nullptr;
    prev = nullptr;
}
