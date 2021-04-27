#include <cmath>
#include <fstream>
#include <iostream>

template <typename T>
class Node {
   public:
    Node(T val) {
        m_left = nullptr;
        m_right = nullptr;
        m_val = val;
    }
    inline T get_val() const { return m_val; }
    inline void set_val(T val) { m_val = val; }
    inline Node *get_left() const { return m_left; }
    inline void set_left(Node *left) { m_left = left; }
    inline Node *get_right() const { return m_right; }
    inline void set_right(Node *right) { m_right = right; }

   private:
    T m_val;
    Node *m_left;
    Node *m_right;
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
        if (new_node->get_val() > curr->get_val()) {
            if (curr->get_right() == nullptr) {
                curr->set_right(new_node);
                return;
            } else {
                return rec_a(curr->get_right(), new_node);
            }
        } else if (new_node->get_val() < curr->get_val()) {
            if (curr->get_left() == nullptr) {
                curr->set_left(new_node);
                return;
            } else {
                return rec_a(curr->get_left(), new_node);
            }
        } else {
            delete new_node;
            return;
        }
    }
    void d(T val) {
        // case that the tree is empty
        if (head == nullptr) {
            return;
        }

        Node<T> *temp;
        Node<T> *del_tar = head;
        Node<T> *del_parent = nullptr;
        bool left;  // left will track whether we need to replace the left or
                    // right child

        // find the node to delete and its parent
        while (del_tar->get_val() != val) {
            if (val < del_tar->get_val()) {
                left = true;
                del_parent = del_tar;
                del_tar = del_tar->get_left();
            } else {
                left = false;
                del_parent = del_tar;
                del_tar = del_parent->get_right();
            }
            if (del_tar == nullptr) {
                // if the deletion target is never found, then return
                return;
            }
        }

        // rep parent is not null here
        // rep target can be null here
        Node<T> *rep_parent = del_tar;  // trail pointer for replacement parent
        Node<T> *rep_tar = rep_parent->get_right();  // pointer for replacement

        // if there is no right path (right child of del target is null) just
        // set the del parent's left child to targets left child. Then delete
        // the target and return (cut the middle man)
        // del_tar is not null here
        if (del_tar->get_right() == nullptr) {
            if (del_tar != head) {
                del_parent->set_left(del_tar->get_left());
                delete del_tar;
                return;
            } else {
                // we are deleting the root node when it has no right child
                temp = head;
                head = head->get_left();
                delete temp;
                return;
            }
        }

        // find the node at the bottom of left node search to replace (after
        // going one to the right). Down the left hand will find a node that is
        // smaller than all nodes of the deletion target's right children but it
        // also down 1 right path so it is greater that all of the deletion
        // target's left children
        // Rep target will not be null
        while (rep_tar->get_left() != nullptr ||
               rep_tar->get_right() != nullptr) {  // while not a leaf node
            if (rep_tar->get_left() == nullptr &&
                rep_tar->get_right() != nullptr) {
                rep_parent = rep_tar;
                rep_tar = rep_tar->get_right();
                if (rep_tar->get_left() == nullptr &&
                    rep_tar->get_right() == nullptr) {
                    rep_parent->set_right(nullptr);
                }
            } else {
                rep_parent = rep_tar;
                rep_tar = rep_tar->get_left();
                if (rep_tar->get_left() == nullptr &&
                    rep_tar->get_right() == nullptr) {
                    rep_parent->set_left(nullptr);
                }
            }
        }

        // Link deletion parent to rep target:
        // case that the deletion parent is not null (we are not deleting the
        // root node)
        if (del_parent != nullptr) {
            if (left) {  // if need to replace the left child
                del_parent->set_left(rep_tar);
            } else {  // if need to replace the right child
                del_parent->set_right(rep_tar);
            }
        } else {  // if deleting the root node
                  // set the appropriate children
            if (head->get_right() != rep_tar) {
                rep_tar->set_right(head->get_right());
                rep_parent->set_left(nullptr);
            }
            if (head->get_left() != rep_tar) {
                rep_tar->set_left(head->get_left());
                rep_parent->set_left(nullptr);
            }
            // swap out head, delete target and return
            temp = head;
            head = rep_tar;
            delete temp;
            return;
        }

        // Give the rep_tar the appropriate children
        if (del_tar->get_right() != rep_tar) {
            rep_tar->set_right(del_tar->get_right());
        }
        if (del_tar->get_left() != rep_tar) {
            rep_tar->set_left(del_tar->get_left());
        }
        delete del_tar;
        return;
    }
    void write() {

        Node<T> *temp;
        if (head == nullptr) {
            return;
        }
        while (head != nullptr) {
            temp = rec_find_small(head, nullptr, true);
            std::cout << std::log10(temp->get_val()) << std::endl;
            delete temp;
        }
    }
    Node<T> *rec_find_small(Node<T> *curr, Node<T> *parent, bool left) {
        if (curr->get_right() == nullptr && curr->get_left() == nullptr) {
            if (parent != nullptr) {
                if (left) {
                    parent->set_left(nullptr);
                } else {
                    parent->set_right(nullptr);
                }
            } else {
                head = nullptr;
            }
            return curr;
        } else {
            if (curr->get_left() == nullptr) {
                return rec_find_small(curr->get_right(), curr, false);
            } else {
                return rec_find_small(curr->get_left(), curr, true);
            }
        }
    }

   private:
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
        } else if (instruction == 'd') {
            tree.d(val);
        }
    }
    tree.write();
}
