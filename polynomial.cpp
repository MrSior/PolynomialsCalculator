#include "polynomial.h"
#include "string"

int Polynomial::Get_length(Node* head){
    int cnt = 0;
    while (head != nullptr){
        cnt++;
        head = head->next;
    }
    return cnt;
}

void Polynomial::Get_mid(Node* head, int n, Node*& mid, Node*& prev){
    Node* tmp = head;
    while (n--){
        prev = tmp;
        tmp = tmp->next;
    }
    mid = tmp;
}

void Polynomial::Merge(Node* head1, Node* head2, Node*& new_head){
    Node* second_list = nullptr;
    Node* first_list = nullptr;
    if (*head1/*->Get_degree_of_base(base)*/ >= *head2/*->Get_degree_of_base(base)*/) {
        new_head = head1;
        first_list = head1;
        second_list = head2;
    } else {
        new_head = head2;
        first_list = head2;
        second_list = head1;
    }
    if(second_list->coefficient == 0){
        delete second_list;
        return;
    }
    while (second_list != nullptr){
        if(first_list == nullptr){
            if(second_list->coefficient == 0) break;
            first_list = second_list;
            break;
        } else if (*first_list == *second_list){
            first_list->coefficient += second_list->coefficient;
            if (second_list->next != nullptr){
                second_list->next->prev = second_list->prev;
            }
            if (second_list->prev != nullptr){
                second_list->prev->next = second_list->next;
            }
            Node* tmp = second_list->next;
            delete second_list;
            second_list = tmp;
        } else if(first_list->coefficient == 0){
            first_list->bases_degrees.clear();
            first_list->bases_degrees.resize(26);
            if(first_list->next != nullptr && first_list->prev != nullptr){
                if(first_list->prev != nullptr){
                    first_list->prev->next = first_list->next;
                }
                if (first_list->next != nullptr){
                    first_list->next->prev = first_list->prev;
                }
                auto tmp = first_list->next;
                delete first_list;
                first_list = tmp;
                continue;
            }
        } else if (first_list->next == nullptr) {
            first_list->next = second_list;
            second_list->prev = first_list;
            break;
        } else if (*first_list->next/*->Get_degree_of_base(base)*/ < *second_list/*->Get_degree_of_base(base)*/){
            Node* tmp = second_list->next;
            second_list->next = first_list->next;
            first_list->next->prev = second_list;
            first_list->next = second_list;
            second_list->prev = first_list;
            second_list = tmp;
            first_list = first_list->next;
        } else {
            first_list = first_list->next;
        }
    }
    if(first_list != nullptr && first_list->coefficient == 0){
        first_list->bases_degrees.clear();
        first_list->bases_degrees.resize(26);
        if(first_list->next != nullptr && first_list->prev != nullptr){
            if(first_list->prev != nullptr){
                first_list->prev->next = first_list->next;
            }
            if (first_list->next != nullptr){
                first_list->next->prev = first_list->prev;
            }
            auto tmp = first_list->next;
            delete first_list;
            first_list = tmp;
        }
    }

    Node* node = new_head;
    while(node != nullptr){
        if(node->coefficient == 0){
            if(node->next == nullptr && node->prev == nullptr) {
                node->bases_degrees.clear();
                node->bases_degrees.resize(26);
                break;
            }
            if (node->next != nullptr){
                node->next->prev = node->prev;
            }
            if (node->prev != nullptr){
                node->prev->next = node->next;
            }
            Node* tmp = node->next;
            delete node;
            node = tmp;
        } else {
            node = node->next;
        }
    }
}

void Polynomial::m_sort(Node*& head, int len){
    if (len < 2) return;
    int l = len / 2;
    Node* mid;
    Node* prev;
    Get_mid(head, len / 2, mid, prev);
    prev->next = nullptr;
    head->prev = nullptr;
    m_sort(head, l);
    mid->prev = nullptr;
    m_sort(mid, len - l);
    Node* new_head = head;
    Merge(head, mid, new_head);
    head = new_head;
}

void Polynomial::Merge_sort(Node*& head){
    m_sort(head, Get_length(head));
}

Polynomial::Polynomial(Polynomial* polynomial){
    Node* itr = polynomial->head;
    while(itr != nullptr){
        Node* node = new Node(itr);
        Insert_head(node);
        itr = itr->next;
    }
    sort();
}

Polynomial::Polynomial()
{
    head = nullptr;
    bases.resize(26);
}

void Polynomial::Convert(std::string str){
    int i = 0;
    while (i != int(str.length())){
        std::string substr;
        substr +=  str[i];
        i++;
        while (i != int(str.length()) && str[i] != '+' && str[i] != '-'){
            if(str[i] != ' '){
                substr += str[i];
            }
            i++;
        }

        Node* new_node = new Node;
        int j = 0;
        std::string coefficient_str;
        int coefficient = 1;
        while (j < int(substr.size())){
            if (substr[j] == '*') {
                j++;
                if(!coefficient_str.empty()){
                    coefficient *= std::stoi(coefficient_str);
                    coefficient_str.clear();
                }
                continue;
            }
            if (isLetter(substr[j])){
                if (!coefficient_str.empty()) {
                    if (coefficient_str == "+" || coefficient_str == "-") {
                        coefficient_str += '1';
                    }
                    coefficient *= std::stoi(coefficient_str);
                    coefficient_str.clear();
                }
                char base = substr[j];
                j++;
                if (substr[j] != '^'){
                    bases[base - 97] = 1;
                    new_node->Add_base_with_degree(base, 1);
                } else {
                    j++;
                    int d = 1;
                    std::string degree;
                    while (j != int(substr.size()) && !isLetter(substr[j]) && substr[j] != '*'){
                        if(str[j] == '^'){
                            d *= std::stoi(degree);
                            degree.clear();
                            j++;
                            continue;
                        }
                        degree += substr[j];
                        j++;
                    }
//                    new_node->Add_base_with_degree(base, std::stoi(degree));
                    d *= std::stoi(degree);
                    new_node->Add_base_with_degree(base, d);
                }
            } else {
                coefficient_str += substr[j];
                j++;
            }
        }
        if (!coefficient_str.empty()) {
            coefficient *= std::stoi(coefficient_str);
        }
        new_node->coefficient *= coefficient;
        Insert_head(new_node);
    }
    sort();
}

void Polynomial::Insert_head(Node* node){
    node->next = head;
    node->prev = nullptr;
    if (head != nullptr) head->prev = node;
    head = node;
}

void Polynomial::sort(){
    Merge_sort(head);
}

void Polynomial::Shorten(){
    Node* node = head;
    while (node != nullptr){
        Node* node1 = node->next;
        while (node1 != nullptr){
            Node* next1 = node1->next;
            if (node->bases_degrees == node1->bases_degrees){
                node->coefficient += node1->coefficient;
                EraseNode(node1);
            }
            node1 = next1;
        }
        Node* next = node->next;
        if (node->coefficient == 0) {
            EraseNode(node);
        }
        node = next;
    }
}

void Polynomial::EraseNode(Node* node){
    if (node->next == nullptr) {
        if (node->prev == nullptr){
            delete node;
            head = nullptr;
        } else {
            node->prev->next = nullptr;
            delete node;
        }
    } else {
        if (node->prev == nullptr) {
            node->next->prev = nullptr;
            head = node->next;
            delete node;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
        }
    }
}

std::string Polynomial::GetString(){
    std::string res;
    if (head == nullptr){
        res = "0";
        return res;
    }
    Node* node = head;
    while (node != nullptr){
        double k = node->coefficient;
        std::vector<std::pair<char, int>> node_bases;
        for (int i = 0; i < int(node->bases_degrees.size()); ++i) {
            if (node->bases_degrees[i]){
                node_bases.emplace_back(char (97 + i), node->bases_degrees[i]);
            }
        }
        if(node_bases.empty()){
            if(k > 0 && node != head){
                res += '+';
            }
            if(k == int(k)) {
                res += std::to_string(int(k));
            } else {
                res += std::to_string(k);
            }
            node = node->next;
            continue;
        }
        if (k > 0 && node != head){
            res += '+';
            if (k > 1) {
                if(k == int(k)) {
                    res += std::to_string(int(k));
                } else {
                    res += std::to_string(k);
                }
            }
        } else if (k == -1) {
            res += '-';
        } else if (k != 1){
            if(k == int(k)) {
                res += std::to_string(int(k));
            } else {
                res += std::to_string(k);
            }
        }
        for (auto i : node_bases) {
            res += i.first;
            if (i.second > 1) {
                res += '^';
                res += std::to_string(i.second);
            }
        }
        node = node->next;
    }
    return res;
}
