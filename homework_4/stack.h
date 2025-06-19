#ifndef STACK_H_
#define STACK_H_

#include "bag.h"

template <class T>
class Stack : public Bag<T> {
public:
	// constructor 
    Stack(int StackCapacity) : Bag<T>(StackCapacity) {
        strcpy(this->name, "Stack");
    }

	// destructor
    ~Stack() {}

	// pop the top element from stack (algorithms --> cheapter 3 page 15)
    T* Pop(T& x) override {
        if (this->IsEmpty()) {
            this->Empty();
            return nullptr;
        }
        else {
            x = this->array[--this->top];
            // print pop element from stack
            this->message(x);
            return &x;
        }
    };
};

#endif
