#pragma once
class Node {
public:
    Node* LeftNode; // дочерний левый узел
    Node* RightNode; // дочерний правый узел
    int value;  // значение узла

    Node(const int& new_value, Node* Left = nullptr, Node* Right = nullptr) {
        value = new_value;
        LeftNode = Left;
        RightNode = Right;
    }

    Node() {
        LeftNode = nullptr;
        RightNode = nullptr;
    }
};