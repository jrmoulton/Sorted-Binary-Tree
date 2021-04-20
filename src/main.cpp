#include <fstream>
#include <iostream>

template <typename T>
class Node {
   public:
    Node(T val) {
        left = nullptr;
        right = nullptr;
        m_val = val;
    }
    T m_val;
    Node *left;
    Node *right;
};

template <typename T>
class BinaryTree {
   public:
    BinaryTree(){
        head = nullptr;
    };
    void push(int val) {
        if (head == nullptr) {
            head = new Node(val);
        } else {
            curr = head;
            
        }
    }
    Node *next(Node *curr, T val) {
        
    }
    Node *head;
};

int main() {
    std::ifstream is("a.txt");
    BinaryTree<int> tree;
    int a;
    while (is >> a) {
        tree.push(a);
    }
}