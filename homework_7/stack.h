#ifndef STACK_H_
#define STACK_H_

// minimal singly linked stack
template <typename T>
class Stack {
    struct Node { T data; Node* next; };
    Node* topPtr{ nullptr };

public:
    ~Stack() { while (topPtr) pop(); }
    bool empty() const { return topPtr == nullptr; }
    void push(const T& x) { topPtr = new Node{ x, topPtr }; }
    T& top() { return topPtr->data; }
    T pop() {
        Node* p = topPtr;
        T val = p->data;
        topPtr = p->next;
        delete p;
        return val;
    }
};

#endif
