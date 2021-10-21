
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "node.h"
#include <cmath>
#include <iomanip>
#include <fstream>

template <typename T>
class BinaryTree {
	public:
		BinaryTree();
		void a(T val);
		void rec_a(Node<T> *curr, Node<T> *new_node);
		void d(T val);
		void write(char *arg);
		Node<T> *rec_find_small(Node<T> *curr, Node<T> *parent, bool left);

	private:
		Node<T> *head;
};

template <typename T>
BinaryTree<T>::BinaryTree() {
	head = nullptr;
};

// The base add method
template <typename T>
void BinaryTree<T>::a(T val) {
	Node<T> *new_node = new Node<T>(val);
	if (head == nullptr) {
		head = new_node;
	} else {
		// If head is not null this function just calls the recursive add
		// method
		rec_a(head, new_node);
	}
};

// The recursive add method
template <typename T>
void BinaryTree<T>::rec_a(Node<T> *curr, Node<T> *new_node) {
	if (new_node->get_val() > curr->get_val()) {
		// Break condition when right is null
		if (curr->get_right() == nullptr) {
			curr->set_right(new_node);
			return;
		} else {
			// else recurse
			return rec_a(curr->get_right(), new_node);
		}
	} else if (new_node->get_val() < curr->get_val()) {
		if (curr->get_left() == nullptr) {
			// Break condition when left is null
			curr->set_left(new_node);
			return;
		} else {
			// else recurse
			return rec_a(curr->get_left(), new_node);
		}
	} else {
		delete new_node;
		return;
	}
}

// The delete method
template <typename T>
void BinaryTree<T>::d(T val) {
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
		if (rep_tar->get_left() == nullptr && rep_tar->get_right() != nullptr) {
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

// The write method
template <typename T>
void BinaryTree<T>::write(char *arg) {
	if (head == nullptr) {
		return;
	}
	Node<T> *temp;
	std::ofstream my_file;
	my_file.open(arg);
	if (!my_file.is_open()) {
		throw std::runtime_error("\nThe output file could not be opened");
	}
	while (head != nullptr) {
		temp = rec_find_small(head, nullptr, true);
		my_file << std::fixed << std::setprecision(4)
			<< std::log10(temp->get_val()) << std::endl;
		delete temp;
	}
}

// The find smallest value method
template <typename T>
Node<T> *BinaryTree<T>::rec_find_small(Node<T> *curr, Node<T> *parent,
		bool left) {
	// When the current is a leaf node
	if (curr->get_right() == nullptr && curr->get_left() == nullptr) {
		// Remote the target from parents children
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
	} else {  // else recurse
		if (curr->get_left() == nullptr) {
			return rec_find_small(curr->get_right(), curr, false);
		} else {
			return rec_find_small(curr->get_left(), curr, true);
		}
	}
}

#endif
