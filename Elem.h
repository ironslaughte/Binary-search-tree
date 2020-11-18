#pragma once
#include "Node.h"
class Elem {
public:
    Elem* pnext;
    Node* Num;
    Elem(Node* s, Elem* pNext = nullptr) {
        Num = s;
        pnext = pNext;
    }
};