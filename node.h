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
    Node(Node* node);

    int Get_degree_of_base(int base){
        return bases_degrees[base];
    }

    void Add_base_with_degree(char base, int degree);

    bool operator < (Node& b){
        int max_degree1 = 0, max_degree2 = 0;
        for (int i = 0; i < int(bases_degrees.size()); ++i) {
            max_degree1 = std::max(max_degree1, bases_degrees[i]);
            max_degree2 = std::max(max_degree2, b.bases_degrees[i]);
        }
        if (max_degree1 < max_degree2) return true;
        if (max_degree1 > max_degree2) return false;
        for (int i = int(bases_degrees.size()) - 1; i >= 0; --i) {
            if (bases_degrees[i] < b.bases_degrees[i]) {
                return true;
            } else if (bases_degrees[i] > b.bases_degrees[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator >= (Node& b){
        return !(*this < b);
    }

    bool operator == (Node& b) const{
        return bases_degrees == b.bases_degrees;
    }
};

#endif // NODE_H
