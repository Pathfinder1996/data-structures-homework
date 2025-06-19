#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

template <class T>
class Bag {
	template <typename U>
	friend ostream& operator<<(ostream&, const Bag<U>&);
public:
	// constructor
	Bag(int BagSize) :MaxSize(BagSize), name("Bag"), top(0) {
		array = new T[MaxSize];
		int i;
		for (i = 0; i < MaxSize; i++) {
			array[i] = -1; // initialize all elements to -1
		}
	};  

	// destructor
	~Bag() {delete[] array; };

	// size of the bag
	virtual int  Size() const {
		return this->top;
	};

	// check if bag is empty
	virtual bool IsEmpty() const {
		if (this->top == 0) {
			return true;
		}
		else {
			return false;
		}
	};

	// check if bag is full
	virtual bool IsFull() const {
		if (this->top == this->MaxSize) {
			return true;
		}
		else {
			return false;
		}
	};

	// push the element into bag(algorithms --> cheapter 3 page 11)
	virtual void Push(const T& x) {
		if (IsFull()) {
			this->Full(x);
			return;
		}
		else {
			this->array[this->top++] = x;
		}
	};

	// Delete the element from bag(algorithms --> cheapter 3 page 11)
	virtual T* Pop(T& x) {
		if (IsEmpty()) {
			this->Empty();
			return nullptr;
		}
		int delete_pos = this->top / 2;          
		x = this->array[delete_pos];

		int index;
		for (index = delete_pos; index < this->top - 1; index++) {
			this->array[index] = this->array[index + 1];
		}
		this->top = top - 1;
		this->message(x);
		return &x;
	};

protected:	
	T *array;	
	int MaxSize;
	int top;   // position of the top element
	char name[20];
	void Empty() { cout << "   " << setw(6) << left << name << " is empty. Cannot Pop()\n"; };
	void Full(const T& x) { cout << "   " << setw(6) << left << name << " is full for " << x << endl; };

	// print message when pop an element
	void message(const T& x) {
		cout << "   pop " << x << " from " << name << endl;
	};
};

// Overload << operator to print the bag
template <class T>
ostream& operator<<(ostream& os, const Bag<T>& b) {
	os << "   All Data in " << right << setw(6) << b.name << "[" << b.MaxSize << "] are: ";
	int i;
	for (i = 0; i < b.MaxSize; i++) {
		if (i < b.top)
			os << "(" << i << ") " << b.array[i] << setw(3) << " ";
		else
			os << "(" << i << ") " << -1 << setw(3) << " ";
	}

	os << "\n   Valid data among them are: ";
	for (i = 0; i < b.top; i++) {
		os << "(" << i << ") " << b.array[i] << setw(3) << " ";
	}
	os << "\n\n";

	return os;
}

#endif
