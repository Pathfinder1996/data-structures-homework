#pragma once
#include "chain_iterator.h"
#include "chain_node.h"

// *********Chain Template Class *********************
template<class T>
class Chain {
	template <class U> friend ostream& operator<<(ostream&, Chain<U>&);
	friend class ChainIterator<T>; // New Added for Iterator
	friend class Polynomial;
	friend class ChainNode<T>;
	friend istream& operator >> (istream&, Polynomial&);   // for reading in a matrix	
public:
	Chain() { current = first = last = NULL; num = 0; }; // constructor initializing first to 0
	~Chain();// destructor to free all allocated memory space, got some trouble
	void Create2(T, T);
	void Insert(ChainNode<T>*, T);
	ChainNode<T>* Pop();
	void Delete(ChainNode<T>*, ChainNode<T>*);
	void InsertBack(const T& e);
	void InsertBack(ChainNode<T>*);
	void InsertInorder(const T& e);
	ChainNode<T>* FirstNode() { return first; };
	void free();
	void operator=(const Chain<T>& t);

public:
	ChainNode <T>* first, * last;
	ChainNode <T>* current;
	int num;
};

// ================================================================================
// COPY Assignment, it needs to delete available data first, 
// i.e., this->~Chain() 
// ================================================================================
template<class T>
void Chain<T>::operator=(const Chain<T>& t) {
	// Clear existing chain first
	this->free();

	// Copy nodes from t to this chain
	ChainNode<T>* current = t.first;
	while (current) {
		this->InsertBack(current->data);
		current = current->link;
	}
}

// =============================================================
// free memory space by destructor may lead to unexpected semantic error.
// So we design another free() function to deleted allocated mem. space of the linked list nodes
// =============================================================
template<class T>
Chain<T>::~Chain() { // Free all nodes in the chain
	ChainNode<T>* next;
	int count = 0;

	for (ChainNode<T>* current = first; current; current = next) {
		next = current->link;
		delete current;
		count = count + 1;
	}

	first = NULL;
	last = NULL;
	current = NULL;
	num = 0;

	//first = NULL; first->avv->num = 10;
	//	num = 10;
	if (debug) {
		cout << "\nrecycle " << num << " nodes->total AV nodes = " << first->avv->num << endl;
	}
};

/*  Free the memory space allocated for linked list nodes
	See lecture notes linked list I page 51 for details  */
template<class T>
void Chain<T>::free() {
	ChainNode<T>* next;
	int count = 0;

	for (ChainNode<T>* curr = first; curr; curr = next) {
		next = curr->link;
		if (debug) {
			if (std::is_same<T, Term>::value) {
				cout << "Term(" << curr->data.coef << ',' << curr->data.exp << ") being freed\n";
			}
		}
		delete curr;
		count = count + 1;
	}

	first = NULL;
	last = NULL;
	current = NULL;
	num = 0;
};

template<class T>
void Chain<T>::Create2(T x1, T x2)
{
	first = new ChainNode<T>(x1); // create & initialize first node
	// create & initialize 2nd node & place its address in first->link   
	last = first->link = new ChainNode<T>(x2);
	num = 2; // set the number of nodes in the chain
};

// create a node with data value and insert after the node pointed by x
template< class T>
void Chain<T>::Insert(ChainNode<T>* x, T value) {
	ChainNode<T>* t = new ChainNode<T>(value); // create and initialize new node

	if (!first) { // insert into empty list
		first = t;
		last = t;
		num = 1;
		return;
	}

	// insert after x
	t->link = x->link;
	x->link = t;

	// Update last if needed
	if (x == last) {
		last = t;
	}

	num = num + 1;
}

// delete the node x, in which the original list is y-->x-->
template <class T>
void Chain<T>::Delete(ChainNode<T>* x, ChainNode<T>* y) {  
	if (!first || !x) {
		return;
	}

	if (x == first) {
		// Case: deleting the first node
		first = x->link;
		if (first == NULL) {
			last = NULL;
		}
	}
	else {
		// Case: deleting a node in the middle or at the end
		y->link = x->link;
		if (x == last) {
			last = y;
		}
	}

	delete x;
	num = num - 1;
}


// delete the node x, in which the original list is y-->x-->
template <class T>
ChainNode<T>* Chain<T>::Pop() {
	if (!first) {
		return NULL;
	}

	ChainNode<T>* temp = first;
	first = first->link;

	if (!first) {
		last = NULL;
	}

	temp->link = NULL;
	num = num - 1;

	return temp;
}

// Insert the template term 'e' to the rear of the chain
template <class T>
void Chain<T>::InsertBack(const T& e) {
	// Create a new node containing e
	ChainNode<T>* node = new ChainNode<T>(e);

	if (!first) {
		// Empty list: first and last both point to the new node
		first = last = node;
	}
	else {
		// Append to end and update last pointer
		last->link = node;
		last = node;
	}
	++num;  // Increase node count
}

// Insert a node pointed by t after the last node
template <class T>
void Chain<T>::InsertBack(ChainNode<T>* t) {
	if (!t) {
		return;
	}

	if (!first) {
		// Empty list
		first = last = t;
		t->link = NULL;
	}
	else {
		// Append to the end
		last->link = t;
		t->link = NULL;
		last = t;
	}

	num = num + 1;
}

// Insert one node into a list in an increasing order
template <class T>
void Chain<T>::InsertInorder(const T& e) {
	ChainNode<T>* newNode = new ChainNode<T>(e);

	// Case: empty list or insert at beginning (when e.exp is greater)
	if (!first || first->data.exp < e.exp) {
		newNode->link = first;
		first = newNode;
		if (!last) {
			last = newNode;
		}
		num = num + 1;
		
		return;
	}

	// Find the position to insert (in descending order of exponents)
	ChainNode<T>* current = first;

	while (current->link && current->link->data.exp >= e.exp) {
		current = current->link;
	}

	// Insert after current
	newNode->link = current->link;
	current->link = newNode;

	// Update last if inserting at the end
	if (!newNode->link) {
		last = newNode;
	}

	num = num + 1;
}

// Print chain contents
template<class T>
ostream& operator<<(ostream& out, Chain<T>& chain) {
	ChainNode<T>* current = chain.first;

	while (current) {
		if (std::is_same<T, Term>::value) {
			out << "(" << current->data.coef << ", " << current->data.exp << ") ";
		}
		current = current->link;
	}

	return out;
}
