#include <initializer_list>
#include <iostream>

struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

Node* create_list(std::initializer_list<int> l) {
    Node* begin = nullptr;
    Node* now = nullptr;
    Node* newNode = nullptr;
    for (auto it = l.begin(); it != l.end(); ++it) {
        newNode = new Node(*it);
        if (now == nullptr) {
            begin = now = newNode;
        } else {
            now->next = newNode;
            now = newNode;
        }
    }
    return begin;
}

void print_list(Node* begin) {
    Node* temp = begin;
    while (temp != nullptr) {
        std::cout << temp->val << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

Node* reserve(Node* begin) {
    Node* temp = begin;
    Node* last = nullptr;
    Node* next = nullptr;
    while (temp != nullptr) {
        next = temp->next;
        temp->next = last;
        last = temp;
        temp = next;
    }
    return last;
}

int main() {
    Node* begin = create_list({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::cout << "before : ";
    print_list(begin);
    begin = reserve(begin);
    std::cout << "after : ";
    print_list(begin);
    return 0;
}
