#pragma once
#include "chain_iterator.h"
#include "chain.h"
#include <fstream>
#include <math.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

extern int debug;
using namespace std;

struct Term {  // all members of Term are public by default
	int coef;	//coefficient
	int exp;	// exponential lorder

	Term Set(int c, int e) { 
		coef = c; exp = e;  return *this; 
	};

	Term Set(ChainNode <Term> temp) {	
		Term data = temp.GetData();  
		coef = data.coef; exp = data.exp; 
		return *this;
	};
};
class Polynomial {
	friend ostream &operator<<(ostream &, Polynomial &);
	friend istream &operator>>(istream &, Polynomial &);
	friend Polynomial operator+(const Polynomial&, const Polynomial&);

public:	
	// Polynomial(Chain <Term>ll) :poly(ll) { label = '0' + counter++;  };
	Polynomial(){ label = 'A' + counter;  num = counter++; message(); };
	Polynomial(char c) { label = c;  num = counter++;  message(); };
	Polynomial(const Polynomial&); // copy constructor 
	~Polynomial();
	void operator=(const Polynomial&);
	Polynomial operator*(const Polynomial&) const;

public:
	Chain <Term> poly;
	void free();
	char label;

private:
	void message();
	static int counter;
	int num;
};

// ======================================
//   COPY CONSTRUCTOR of polynomial
// ======================================
Polynomial::Polynomial(const Polynomial &p){
	ChainNode <Term> *current = p.poly.first;
	this->num = counter++;
	this->label = '?';

	while (current) {
		poly.InsertBack(current->data);
		current = current->link;
	}
	message();
};

//====================================== 
// print out poly object message 
//======================================
void Polynomial::message() {
	if(debug) cout << "\nConstruct Poly(num=" << this->num << ", op=" << this->label << ")";
};

int Polynomial::counter = 0; // initialize static variables 
//====================================== 
// COPY 'ASSIGNMENT' of Polynomial 
//======================================
void Polynomial::operator= (const Polynomial& p)  {
	// Clear existing polynomial
	poly.free();

	// Copy nodes from p to this polynomial
	ChainNode<Term>* current = p.poly.first;
	while (current) {
		poly.InsertBack(current->data);
		current = current->link;
	}
};

// Destructor: executed automatically after the corresponding '}"
Polynomial::~Polynomial() {
	// The ~Chain() will be triggered to clear the linked list poly
	if(debug) cout << "\nDestruct Poly(num="<< this->num <<", op=" << setw(2) << (char)this->label << "): ";
};

// The destructor automatically delete a linkted list data but 
// it conflicts with an operator overloading function p3 = p1 + p2;
void Polynomial::free() { // Free all nodes in the chain
	cout << "Free Polynomial " << setw(4) << (char)this->label << endl;
	poly.free();
};

// polynomial multiplication function - implements polynomial multiplication 
Polynomial Polynomial::operator*(const Polynomial& b) const {
	Polynomial c('*');
	c.poly.free(); // Clear any initial content

	if (!poly.first || !b.poly.first) return c; // Empty polynomial

	// For each term in first polynomial
	for (ChainNode<Term>* aPtr = poly.first; aPtr; aPtr = aPtr->link) {
		// For each term in second polynomial
		for (ChainNode<Term>* bPtr = b.poly.first; bPtr; bPtr = bPtr->link) {
			// Create new term with product
			Term newTerm;
			newTerm.coef = aPtr->data.coef * bPtr->data.coef;
			newTerm.exp = aPtr->data.exp + bPtr->data.exp;

			// Check if we already have a term with this exponent
			bool found = false;
			ChainNode<Term>* current = c.poly.first;

			while (current && !found) {
				if (current->data.exp == newTerm.exp) {
					// Add coefficients for same exponent
					current->data.coef += newTerm.coef;
					found = true;
				}
				current = current->link;
			}

			// If no existing term with same exponent, add the new term
			if (!found && newTerm.coef != 0) {
				c.poly.InsertInorder(newTerm);
			}
		}
	}

	return c;
};

Polynomial operator+(const Polynomial& a, const Polynomial& b) {   
	Polynomial c('+');
	c.poly.free(); // Clear any initial content

	// Handle empty polynomials
	if (!a.poly.first) {
		return b;
	}

	if (!b.poly.first) {
		return a;
	}

	ChainNode<Term>* pA = a.poly.first;
	ChainNode<Term>* pB = b.poly.first;

	// Process terms until at least one polynomial is completely traversed
	while (pA && pB) {
		if (pA->data.exp == pB->data.exp) {
			// Same exponent - add coefficients
			Term sum;
			sum.coef = pA->data.coef + pB->data.coef;
			sum.exp = pA->data.exp;

			// Only add if coefficient is not zero
			if (sum.coef != 0) {
				c.poly.InsertBack(sum);
			}

			pA = pA->link;
			pB = pB->link;
		}
		else if (pA->data.exp > pB->data.exp) {
			// A's exponent is higher - add A's term
			c.poly.InsertBack(pA->data);
			pA = pA->link;
		}
		else {
			// B's exponent is higher - add B's term
			c.poly.InsertBack(pB->data);
			pB = pB->link;
		}
	}

	// Add any remaining terms from polynomial A
	while (pA) {
		c.poly.InsertBack(pA->data);
		pA = pA->link;
	}

	// Add any remaining terms from polynomial B
	while (pB) {
		c.poly.InsertBack(pB->data);
		pB = pB->link;
	}

	return c;
};

ostream & operator<<(ostream &out, Polynomial &p) {
	ChainNode<Term>* current = p.poly.first;

	if (!current) {
		out << "(0)";
		return out;
	}

	out << "(";
	bool first = true;

	while (current) {
		char sign = current->data.coef > 0 ? '+' : '-';

		if (first) {
			if (sign == '+') {
				// First term and positive: don't show the sign
				out << abs(current->data.coef) << "x^" << current->data.exp;
			}
			else {
				// First term and negative: show the sign
				out << sign << " " << abs(current->data.coef) << "x^" << current->data.exp;
			}
			first = false;
		}
		else {
			// Not the first term: always show the sign
			out << " " << sign << " " << abs(current->data.coef) << "x^" << current->data.exp;
		}

		current = current->link;
	}
	out << ")";

	return out;
};

istream& operator>>(istream& is, Polynomial& p) {
// read in a polynomial  and set up its linked representation.
	int nterm;
	Term term;

	is >> nterm;
	is.clear();
	is.ignore(100, '\n');

	// Clear existing polynomial
	p.poly.free();

	// Read each term and add to the polynomial
	for (int i = 0; i < nterm; i++) {
		is >> term.coef >> term.exp;
		is.clear();
		is.ignore(100, '\n');

		// Add term to polynomial
		p.poly.InsertBack(term);
	}

	return is;
};

void LOGO() {
	cout << "===============================================================\n"
		<< "       Linked Polynomial Lecture 4 Part I: p44-p47 \n"
		<< "      Designed and verified by Jiann-Jone Chen 2025\n"
		<< "================================================================\n\n";
}
