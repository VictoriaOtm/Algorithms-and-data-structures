#ifndef DZ2_BINARYTREE_H
#define DZ2_BINARYTREE_H

#include <cstddef>
#include <stack>

struct Node {
    int _key = 0;

    Node *_left = nullptr;
    Node *_right = nullptr;
    Node *_parent = nullptr;

    explicit Node(const int key) : _key(key) {
        _left = _right = _parent = nullptr;
    }

    explicit Node(const int key, Node *parent) :
            _key(key), _parent(parent) {}

};

class BinaryTree {
public:
    explicit BinaryTree() : _root(nullptr), _size(0) {}

    void insert(const int key) {
        if (_root == nullptr) {
            _root = new Node(key);
            return;
        }

        Node *temp = _root;
        Node *parent;

        for (;;) {
            parent = temp;
            temp = key < temp->_key ? temp->_left : temp->_right;

            if (temp == nullptr) {
                if (key < parent->_key) {
                    parent->_left = new Node(key, parent);

                } else {
                    parent->_right = new Node(key, parent);
                }
                ++_size;
                return;
            }

        }

    }

    void print_inorder() {
        Node *current = _root;
        std::stack<Node *> stack;

        bool done = false;
        while (!done) {
            if (current != nullptr) {
                stack.push(current);
                current = current->_left;
            } else {
                if (!stack.empty()) {
                    current = stack.top();
                    std::cout << current->_key << " ";
                    stack.pop();
                    current = current->_right;
                } else {
                    done = true;
                }
            }
        }
    }

    ~BinaryTree() {
        if (_root == nullptr) {
            return;
        }

        std::stack<Node **> stack;
        stack.push(&_root);

        while (!stack.empty()) {
            if ((*stack.top())->_left != nullptr) {
                stack.push(&((*stack.top())->_left));

            } else if ((*stack.top())->_right != nullptr) {
                stack.push(&((*stack.top())->_right));

            } else {
                Node *temp = *(stack.top());
                delete temp;
                *(stack.top()) = nullptr;
                stack.pop();
            }
        }
    }


private:
    Node *_root;
    size_t _size;

};

#endif //DZ2_BINARYTREE_H