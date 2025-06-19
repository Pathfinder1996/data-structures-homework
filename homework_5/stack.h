#ifndef STACK_H_
#define STACK_H_
   
#include <cmath>
#include <iostream>
#include <iomanip>
#include <ostream>
using namespace std;
#define DefaultSize 100

void StackEmpty();
void StackFull();
template<typename T>
class Stack{
public:
	// Constructor
	// Create an empty Stack whose maximum size is MaxStackSize
	Stack(int MaxStackSize = DefaultSize) : MaxSize(MaxStackSize), top(-1) {
		stack = new T[MaxSize];
	};

	// Destructor
	~Stack() {
		delete[] stack;
	};

	// if number of elements in the Stack is equal to the maximum size of
	// the Stack, return TRUE(1); otherwise, return FALSE(0)
	bool IsFull() {
		if (top == MaxSize - 1) {
			return true;
		}
		else {
			return false;
		}
	};

	// if IsFull(), then StackFull(); else insert item at rear of the Stack
	void Push(const T& x) {
		if (IsFull()) {
			StackFull();
		}
		else {
			stack[++top] = x;
		}
	};

	// if number of elements in the Stack is equal to 0, return true
	// else return false
	bool IsEmpty() {
		if (top == -1) {
			return true;
		}
		else {
			return false;
		}
	};

	// if IsEmpty(), then StackEmpty() and return 0;
	// else remove the item at the front of the Stack and return a pointer to it
	T* Delete(T& x) {
		if (IsEmpty()) {
			StackEmpty();
			return 0;
		}
		else {
			x = stack[top--];
			return &x;
		}
	};

	// if IsEmpty(), then StackEmpty() and return 0;
	// else remove the item at the front of the Stack and return a pointer to it
	T* Top(T& x) {
		if (IsEmpty()) {
			StackEmpty();
			return 0;
		}
		else {
			x = stack[top];
			return &x;
		}
	};

friend	ostream& operator<<(ostream& os, const Stack <T>& s) {
	// Print the stack
	os << "[Stack:";
	int i;
	for (i = 0; i <= s.top; ++i) {
		os << ' ' <<  s.stack[i];
	}
	os << ']';

	return os;
};

private:
	int top;     //top: index of the topmost element to be retrieved   	
	T *stack;    // T array pointer
	int MaxSize;
};

#endif
