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
    bool operator<(const Node &other) const {
        if (m_val < other->m_val) {
            return true;
        } else {
            return false;
        }
    }
    bool operator>(const Node &other) const {
        if (m_val > other->m_val) {
            return true;
        } else {
            return false;
        }
    }
    T m_val;
    Node *left;
    Node *right;
};

template <typename T>
class BinaryTree {
   public:
    BinaryTree() { head = nullptr; };
    void a(int val) {
        Node<T> *new_node = new Node<T>(val);
        if (head == nullptr) {
            head = new_node;
        } else {
            rec_a(head, new_node);
        }
    };
    void rec_a(Node<T> *curr, Node<T> *new_node) {
        if (new_node->m_val > curr->m_val) {
            if (curr->right == nullptr) {
                curr->right = new_node;
                return;
            } else {
                return rec_a(curr->right, new_node);
            }
        } else if (new_node->m_val < curr->m_val) {
            if (curr->left == nullptr) {
                curr->left = new_node;
                return;
            } else {
                return rec_a(curr->left, new_node);
            }
        } else {
            delete new_node;
            return;
        }
    }
    void d(int val) {
        if (val == head->m_val) {
            Node<T> *left = head->left;

            head = head->right;
            if (head->left == nullptr) {
                
            }

        }
    }
    Node<T> *head;
};

int main() {
    std::ifstream is("input.txt");
    BinaryTree<int> tree;
    int val;
    char instruction;
    while (is >> instruction >> val) {
        if (instruction == 'a') {
            tree.a(val);
        }
    }
}