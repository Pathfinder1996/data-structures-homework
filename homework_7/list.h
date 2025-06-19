#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include "node.h"

template <class T> class Node;
using namespace std;
extern int debug;
extern int debug_list;
extern const int width;

// *********List Template Class *********************
template<class T>
class List {	
	friend class Node<T>;
	friend ostream& operator<<(ostream&, List<T>&);
public:
	List() { current = first = last = NULL; num = 0; }; // constructor initializing first to 0
	~List();// destructor to free all allocated memory space, got some trouble
	List(const List& l) { while (l.first) { InsertBack(l.first->GetData()); } };
	void Create2(T, T);
	void Insert(Node<T>*, T);
	Node<T>* Pop();
	void Delete(Node<T>*, Node<T>*);
	void InsertBack(const T&);	
	void InsertBack(Node<T>*);
	void InsertFront(const T&);   // from data
	void InsertFront(Node<T>* e); // from node*
	void InsertInorder(const T&); 
	void InsertInorderB(const T&);
	Node<T>* FirstNode() { return first; };
	void PrintList();
	void free();
	int GetNum() { return num; };
	void operator=(const List<T>& t);
public:
	Node <T>* first, * last, * current;
	int num;   // number of node in the Chain
};

// ================================================================================
// COPY Assignment, it needs to delete available data first, 
// i.e., this->~List() 
// ================================================================================
template<class T>
void List<T>::operator=(const List<T>& t) {
	Node <T>* tcur;// *scur;
	if(this->first)	 // non-empty Listcondition
		this->~List();
	tcur = t.first;
	if(debug && debug_list) cout << "\nList copy assignment..";
	while (tcur) {
		if (debug && debug_list) cout << "\nnew list node (" << tcur->data << ")->";
		InsertBack(tcur->data);
		tcur = tcur->GetLink();
	}
}

// =============================================================
// free memory space by destructor may lead to unexpected semantic error.
// So we design another free() function to deleted allocated mem. space of the linked list nodes
// =============================================================
template<class T>
List<T>::~List() { // Free all nodes in the chain
	if(debug && debug_list) cout << "delete List->";
	if (first) {
		// direct recycle the entire linked list
		last->link = first->avv->first;
		if (first->avv->last == NULL) first->avv->last = last;
		first->avv->first = first;
		first->avv->num += num;
		if (debug && debug_list) cout << "recycle " << num << " nodes -> #AVnodes = " << first->avv->num;
		num = 0;
		first = last = current = NULL;
	}
	
};

/*  Free the memory space allocated for linked list nodes
	See lecture notes linked list I page 51 for details */
template<class T>
void List<T>::free() {
	if (debug && first&&debug_list) cout << "Delete";
	last->link = first->avv->first;
	first->avv->first = first;
	first->avv->num += num;
	first = NULL;
	if (debug && debug_list) cout << "\nrecycle " << num << " nodes->total AV nodes = " << first->avv->num;
};
// ***************************************************************************
template<class T>
void List<T>::Create2(T x1, T x2)
{
	first = new Node<T>(x1); // create & initialize first node
	// create & initialize 2nd node & place its address in first->link   
	last = first->link = new Node<T>(x2);
};

/****************************************************************************
  create a node with data value and insert after the node pointed by x
***************************************************************************  */
template< class T>
void List<T>::Insert(Node<T>* x, T value)
{
	Node<T>* t = new Node<T>(value); // create and initialize new node
	if (!first) // insert into empty Chain
	{
		first = t;
		exit(1); // exit Chain::Insert50
	}
	// insert after x
	t->link = x->link;
	x->link = t;
};


/******************************************************************
  delete the node x, in which the original list is y-->x-->
********************************************************************/
template <class T>
void List<T>::Delete(Node<T>* x, Node<T>* y) {
	if (x == first) first = first->link;
	else y->link = x->link;
	delete x;
};

/******************************************************************
  Pop the first node e from the list->e->x->y...
 ********************************************************************/
template <class T>
Node<T>* List<T>::Pop(){
	Node <T>* t;
	if (first) {
		t = first;
		first = first->link;
		num--;
		if (num == 0) first = last = NULL;
		return t;
	}
	else {
		cout << "Pop from an empty List!!\n";
		return NULL;
	}
};
//=============================================================
// Create a Node to store the 'e' and interset it to the rear of chain
//=============================================================
template <class T>
void List<T>::InsertBack(const T& e)
{
	// if (debug) cout << "\nnew  list node (" << e << ")->";
	if (first) { // non null chain
		last = last->link = new Node<T>(e);
	}
	else first = last = new Node<T>(e);
	last->link = NULL;
	num++;

};

//=============================================================
// Create a Node to store the 'e' and insert it to the front of chain
//=============================================================
template <class T>
void List<T>::InsertFront(const T& e)
{
	if (debug && debug_list) cout << "\nnew  list node (" << e << ")->";
	if (first) { // non null chain
		first = new Node<T>(e,first);
	}
	else first = last = new Node<T>(e, NULL);
	num++;
};

//=============================================================
// Create a Node to store the 'e' and insert it to the front of chain
//=============================================================
template <class T>
void List<T>::InsertFront(Node<T>*e)
{
	if (debug && debug_list) cout << "new list node(" << e->data << ")-> ";
	Node<T>* t = new Node<T>(*e);
	if (first) { // non null chain
		first = t;    // e is Node(e,top) already
	}
	else first = last = t;
	num++;
};

// Insert a node pointed by t after the last node
template <class T>
void List<T>::InsertBack(Node<T>* t)
{
	if (first)  // non null chain
		last = last->link = t;
	else first = last = t;
	last->link = NULL;
	num++;
};
/*******************************************************
 Insert one node into a list in an increasing order
 Insert one node into a list in an increasing order
********************************************************/
template <class T>
void List<T>::InsertInorder(const T& e)
{
	Node<T>* Current, * last, * temp;
	bool Proceed;
	if (debug && debug_list) cout << "\nnew node(" << setw(width) << e.coef << ',' << setw(width) << e.exp << ')';
	temp = new Node<T>(e);

	if (first) {
		if (e.exp < first->data.exp) { temp->link = first; first = temp; Proceed = false; };
		last = first;
		Current = first->link;
		Proceed = true;
		while (Proceed && Current)
			if (e.exp > Current->data.exp) {
				last = Current;
				Current = Current->link;
			}
			else Proceed = false;
		last->link = temp;
		temp->link = Current;
		if (!Current)  last = temp;
	}
	else first = last = Current = temp;
};
//***************************************

/*******************************************************
 Insert one node into a list in an increasing order.
 When nodes are equal in value, add their coefficients into one
********************************************************/
template <class T>
void List<T>::InsertInorderB(const T& e)
{
	Node<T>* Current, * last, * temp;
	bool Proceed;
	if (debug && debug_list) cout << "\nnew node(" << setw(width) << e.coef << ',' << setw(width) << e.exp << ")->";
	temp = new Node<T>(e, 0);
	if (first) {
		if (e.exp > first->data.exp) { temp->link = first; first = temp; Proceed = false; }
		else {
			last = first;
			Current = first->link;
			Proceed = true;
			while (Proceed && Current)
				if (e.exp <= Current->data.exp) {
					last = Current;
					Current = Current->link;
				}
				else Proceed = false;
			if (last->data.exp == e.exp) {
				last->data.coef += e.coef;
				if (debug) cout << "\nrecycle node(" << e.coef << ',' << e.exp << ")->";
				delete temp;
			}
			else {
				last->link = temp;
				temp->link = Current;
			}
			//			if (!Current)  last = temp;
		}
	}
	else first = last = Current = temp;
};
//**********************************************
template<class T>
void List<T>::PrintList()
{
	current = first;
	cout << "t--> ";
	while (current != NULL) {
		cout << current->data << " --> ";
		current = current->link;
	}
	cout << "NULL" << endl;
};

//****************************************
//  Finished in 2022
//****************************************
template<class T>
ostream& operator<<(ostream& out, List<T>& ll) {
	ll.current = ll.first;
	out << endl
		<< "print the linked Listby operator overloading << ll\n" << endl << "ll.Chain-->";
	while (ll.current != NULL)
	{
		out << ll.current->data << "-->";
		ll.current = ll.current->link;
	}
	out << "NULL(end)";
	return out;
};

#endif