#pragma once
#include "Elem.h"
class Stack {
public:
    Stack();
    Node* Top();
    Node* Pop();
    void Pop_Front();
    void Clear();
    void Push(Node* number);
    size_t GetSize();
    bool IsEmpty();
    int& operator[] (size_t index);

private:
    size_t Size;
    Elem* head;
};



Stack::Stack() {
    Size = 0;
    head = nullptr;
}

Node* Stack::Top() {
    return head->Num;
}

Node* Stack::Pop() {
    Node* data = head->Num;
    Pop_Front();
    return data;
}
void Stack::Pop_Front()
{    
    Elem* tmp = head;
    head = head->pnext;
    delete tmp;
    Size--;
}

void Stack::Push(Node* number) {
    head = new Elem(number, head);
    Size++;
}
void Stack::Clear()
{
    while (Size > 0) {
        Pop_Front();
    }
}



size_t Stack::GetSize()
{
    return Size;
}


int& Stack::operator[](size_t index)
{
    int count = 0;
    Elem* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->Num->value;
        } cur = cur->pnext;
        count++;
    }
}


bool Stack::IsEmpty() {

    return Size > 0;
}
