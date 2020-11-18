#pragma once
class Node {
public:
    Node* LeftNode; // �������� ����� ����
    Node* RightNode; // �������� ������ ����
    int value;  // �������� ����

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