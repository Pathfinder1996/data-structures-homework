#ifndef CHAIN_ITERATOR_H
#define CHAIN_ITERATOR_H
#include "ChainNode.h"
#include <iostream>
#include <ostream>
using namespace std;

enum Boolean { FALSE, TRUE };
template<class T> class Chain;
template<class T> class ChainNode;
template<class T> class ChainIterator; // new added from previos LinkedLIst program 

template<class T>
class ChainIterator {
public:
	ChainIterator(const Chain <T> &l):list(l),current(l.first){};
	T &operator*() const { return current->data; };
	T *operator->() const { return &current->data; };
	  // increment
	ChainIterator &operator++() // forward increment
	     { current = current->link; return *this; };
	ChainIterator operator++(int) // backward increment
       { ChainIterator old = *this; current = current->link; return old; };
	  // equivalent test
	bool operator != (const ChainIterator right) const { return (current != right.current); };
	bool operator == (const ChainIterator right) const { return (current == right.current); };
	bool NotNull();
	bool NextNotNull();
	T *First();
	T *Next();
// private:
	const Chain <T> & list;  // refers to an existing list
	ChainNode <T> *current; // points to a node in list
};

template<class T> // check that the current element in List is non-null
bool ChainIterator<T>::NotNull(){
	if(current) return true; 
	else return false; 
};
template<class T> // check that the next element in List is non-null
bool  ChainIterator<T>::NextNotNull() {
	if(current&&current->link) return true;  else return false;
};
template<class T> // return a pointer to the first element of List
T *ChainIterator<T>::First() {
	if(list.first) return(&list.first->data); 
	else return 0;
};

template<class T> // return a pointer to the next element of List
T * ChainIterator<T>::Next() {
	if(current) {
		ChainNode<T>* t = current;
		current = current->link;
		delete t;
		if(current) return (&current->data);
		else return 0;
	}
	return 0;
 };


// *** sum all data up by iterator
template<class T>
T sum(const Chain <T> &input_Chain) {
	ChainIterator <T>  l(input_Chain); // l is associated with Chain input_Chain
	if (!l.NotNull()) return 0; 	// return 0 if the Chain is empty    
	T ret_value = *l.First();	// get the first element¡¦s pointer
	while (l.NextNotNull()) {    // iteratively sum up every element¡¦s value
		ret_value += *l.Next(); 	// get it, add it to the current total
	}
	return (ret_value);
};
// *********print all data by iterator ***************
template<class T>
void IterPrint(const Chain <T> &input_list) {
	ChainIterator <T>  l(input_list); // l is associated with Chain input_Chain
	cout << endl << "Print the Chain by iterator" << endl << "t--> ";
	if (!l.NotNull()) exit(1); 	// return 0 if the Chain is empty    
	cout << *l.First() << "--> ";
	while (l.NextNotNull()) cout << *l.Next() << "--> ";
	cout << "NULL" << endl;
};

#endif