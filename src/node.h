
#ifndef NODE_H
#define NODE_H

/* Class to hold the node type
Node constructor
getter and setter functions
*/
template <typename T>
class Node {
   public:
    // Node constructor
    Node(T val) {
        m_left = nullptr;
        m_right = nullptr;
        m_val = val;
    }

    // getter and setter functions
    T get_val() const;
    void set_val(T val);
    Node *get_left() const;
    void set_left(Node *left);
    Node *get_right() const;
    void set_right(Node *right);

   private:
    T m_val;
    Node *m_left;
    Node *m_right;
};

template <typename T>
T Node<T>::get_val() const {
    return m_val;
}

template <typename T>
void Node<T>::set_val(T val) {
    m_val = val;
}

template <typename T>
Node<T> *Node<T>::get_left() const {
    return m_left;
}

template <typename T>
void Node<T>::set_left(Node *left) {
    m_left = left;
}

template <typename T>
Node<T> *Node<T>::get_right() const {
    return m_right;
}

template <typename T>
void Node<T>::set_right(Node *right) {
    m_right = right;
}

#endif
