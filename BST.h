#pragma once
#include "queue.h"
#include "stack.h"
#include "iterator.h"


class bft_iterator : public Iterator {
private:
    Node* current;
    Queue NodeQueue;
public:
    bft_iterator(Node* start) {
        current = start;
        if (current != nullptr) {
            NodeQueue.Enqueue(current);
        }
        else {
            throw std::out_of_range("this tree is empty\n");
        }
    }

    int next() override {
        if (NodeQueue.GetSize() > 0) {
            current = NodeQueue.Dequeue();
            if (current->LeftNode != nullptr) {
                NodeQueue.Enqueue(current->LeftNode);
            }
            if (current->RightNode != nullptr) {
                NodeQueue.Enqueue(current->RightNode);
            }
            return current->value;
        }
        else {
            current = nullptr;
            throw std::out_of_range("No more elements\n");
        }
    }

    bool has_next() override {
        return current == nullptr;
    }
};

class dft_iterator : public Iterator {
private:
    Node* current;
    Stack NodeStack;
    uint8_t flag = 1;
public:
    dft_iterator(Node* start) {
        current = start;
        if (current != nullptr) {
            NodeStack.Push(current);
        }
        else {
            throw std::out_of_range("this tree is empty\n");
        }
    }

    int next() override {
            if (flag) {
                flag = 0;
                return NodeStack.Pop()->value;
            }
            if (current->RightNode != nullptr) {
                NodeStack.Push(current->RightNode);
            }
            if (current->LeftNode != nullptr) {
                current = current->LeftNode;
            }
            else if (NodeStack.IsEmpty()) {
                current = NodeStack.Pop();
            }
            else {
                current = nullptr;
                throw std::out_of_range("No more elements\n");
            }
            return current->value;
    }

    bool has_next() override {
        return current == nullptr;
    }

};


class BST {
private:
    Node* root;
public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        clear_tree(root);
    }

    void insert(const int& value);
    bool contains(const int& value);
    void remove(const int& value);
    void clear_tree(Node* cur);
    
    Iterator* create_bft_iterator();
    Iterator* create_dft_iterator();
    
};

Iterator* BST::create_bft_iterator() {
    return new bft_iterator(root);
}

Iterator* BST::create_dft_iterator() {
    return new dft_iterator(root);
}

void BST::clear_tree(Node* cur) {
    if (cur != nullptr) {
        clear_tree(cur->LeftNode);
        clear_tree(cur->RightNode);
        delete cur;
    }
}

void BST::insert(const int& value) {
    if (root == nullptr) {
        root = new Node(value);
    }
    else {
        Node* cur = root;
        while (true) {
            if (value <= cur->value) {
                if (cur->LeftNode != nullptr) {
                    cur = cur->LeftNode;
                }
                else {
                    cur->LeftNode = new Node(value);
                    break;
                }
            }
            else {
                if (cur->RightNode != nullptr) {
                    cur = cur->RightNode;
                }
                else {
                    cur->RightNode = new Node(value);
                    break;
                }
            }

        }
    }
}

bool BST::contains(const int& value) {
    if (root == nullptr) {
        throw std::out_of_range("this tree is empty");
    }
    Node* cur = root;
    while (value != cur->value) {
        if (value < cur->value) {
            if (cur->LeftNode != nullptr) {
                cur = cur->LeftNode;
            }
            else {
                return false;
            }
        }
        else {
            if (cur->RightNode != nullptr) {
                cur = cur->RightNode;
            }
            else {
                return false;
            }
        }
    } return true;
}

void BST::remove(const int& value) {
    if (!contains(value)) {
        throw std::invalid_argument("the element to delete is not in the tree\n");
    }
    else {
        Node* cur = root;
        Node* prev = nullptr;
        while (value != cur->value) {
            if (value < cur->value) {
                prev = cur;
                cur = cur->LeftNode;
            }
            else {
                prev = cur;
                cur = cur->RightNode;
            }
        }

        if (cur->LeftNode == nullptr && cur->RightNode == nullptr) {
            if (prev->LeftNode->value = cur->value) {
                prev->LeftNode = nullptr;              
            }
            else {
                prev->RightNode = nullptr;
            }

            delete cur;
        }
        else if (cur->LeftNode != nullptr && cur->RightNode != nullptr) {
            Node* tmp;
            if (cur->RightNode->LeftNode != nullptr) {
                tmp = cur->RightNode->LeftNode;
                cur->value = tmp->value;
                cur->RightNode->LeftNode = nullptr;
            }
            else {
                tmp = cur->RightNode;
                cur->value = tmp->value;
                Node* new_Node = new Node(tmp->RightNode->value, tmp->RightNode->LeftNode, tmp->RightNode->RightNode);
                cur->RightNode = new_Node;
            }
            delete tmp;
        }
        else {
            if (cur->LeftNode != nullptr) {
                cur->value = cur->LeftNode->value;
                delete cur->LeftNode;
                cur->LeftNode = nullptr;
            }
            else {
                cur->value = cur->RightNode->value;
                delete cur->RightNode;
                cur->RightNode = nullptr;
            }
        }

    }
}