#ifndef CHAIN_NODE_H
#define CHAIN_NODE_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <type_traits>

extern int debug;
using namespace std;
extern void *av;  // pointer to av list ChainNode<T>*
                  // the static pointer avv points to this av.

template<class T> class Chain;
template<class T> class ChainNode;
template<class T> class ChainIterator; // new added from previos LinkedChain program 
class Polynomial;
struct Term;

const int width = 2;
extern int N;

//*****  ChainNode Template Class 
template <class T>
class ChainNode {
	friend class Polynomial;
	friend class Chain <T>;
	friend class ChainIterator <T>; // new added for iterator
	friend istream &operator>>(istream &, Polynomial&);
	template <class T> friend ostream &operator<<(ostream &,  Chain<T>&);
public:
	T GetData() { return data; };
	ChainNode <T>* GetLink() { return link; };
	ChainNode() {
		av_init();
	};
	
	ChainNode(T element, ChainNode<T>* l = 0) :data(element), link(l) {
		if (debug && std::is_same<T, Term>::value) {
			const Term& term = static_cast<const Term&>(element);
			cout << "\nnew node(" << term.coef << ", " << term.exp << ")->total AV nodes = " << avv->num;
		}
	};

	void av_init();
	static Chain<T> *avv;

public:
	T data;
	ChainNode<T> *link;
};

// **********Initialize the avv pointer ********
template <class T> 
Chain<T> * ChainNode<T>::avv = NULL;

// initialize the available list with a coupld of nodes
template<class T>
void ChainNode<T>::av_init() {
// initialized the available list
	if (avv == NULL) {
		avv = new Chain<T>();
	}
}

#endif
